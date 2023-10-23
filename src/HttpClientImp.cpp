#include "HttpClientImp.h"
#include <malloc.h>
#include <string.h>
#include <time.h>
#include <curl/curl.h>

HttpClientImp::HttpClientImp(int connect_timeout) {
    m_connectTimeout = connect_timeout;
    m_front = 0;
    m_rear = 0;
    m_taskMutex = PTHREAD_MUTEX_INITIALIZER;
    m_taskCond = PTHREAD_COND_INITIALIZER;
    m_task = new HttpTask[MAX_TASK_NUM];
    
    m_responseData = NULL;
    m_responseLen = 0;
    m_responseOffset = 0;
    m_requestData = NULL;
    m_requestLen = 0;
    m_sendLen = 0;
    m_isRunning = true;
    
    m_threadId = 0;
}

HttpClientImp::~HttpClientImp() {
    if (m_responseData) {
        free(m_responseData);
    }
    m_responseLen = 0;

    if (m_requestData) {
        free(m_requestData);
    }
    m_requestLen = 0;

    if (m_threadId) {
        pthread_mutex_lock(&m_taskMutex);
        m_isRunning = false;
        pthread_cond_signal(&m_taskCond); 
        pthread_mutex_unlock(&m_taskMutex);
        pthread_join(m_threadId, NULL);
    }
}

void HttpClientImp::setListener(HttpClientListener *listener) {
    m_listener = listener;
}

int HttpClientImp::appendHeader(const char *key, const char *value) {
    char header[1024] = {0};
    snprintf(header, 1024, "%s: %s", key, value); 
    m_headers = curl_slist_append(m_headers, header);
    return 0;
}

int HttpClientImp::addGetRequest(const char *url, void *arg) {
    return addTask("GET", false, url, "", arg);    
}

int HttpClientImp::addPostRequest(const char *url, const char* param, void *arg) {
    return addTask("POST", false, url, param, arg);    
}

int HttpClientImp::addBlockGetRequest(const char *url, void *arg) {
    return addTask("GET", true, url, "", arg);    
}

int HttpClientImp::addBlockPostRequest(const char *url, const char *param, void *arg) {
    return addTask("POST", true, url, param, arg);    
}

static int reallocMemSpace(char *&data, int &data_size, int expect_size) {
    if (data_size > expect_size) {
        printf("no need add mem");
        return 0;
    }
    char *mem = (char *)realloc(data, expect_size + 1024);
    if (mem == NULL) {
        printf("realloc failed\n");
        return -1;
    }
    data = mem;
    data_size = expect_size + 1024;
    return 0;
}

static long long tm_to_ns(struct timespec tm)
{
	return tm.tv_sec * 1000000000 + tm.tv_nsec;
}
 
static struct timespec ns_to_tm(long long ns)
{
	struct timespec tm;
	tm.tv_sec = ns / 1000000000;
	tm.tv_nsec = ns - (tm.tv_sec * 1000000000);
	return tm;
}

int HttpClientImp::addTask(const char *method, bool block, const char *url, const char *param, void *arg) {
    if (block) {
        pthread_mutex_lock(&m_taskMutex);
        HttpTask task;
        task.setTask(method, url, param, arg);
        int ret = httpRequest(task.getMethod().c_str(), task.getUrl().c_str(), task.getParam().c_str(), task.getArg());
        if (ret == 0) {
            // 正常响应
            m_listener->onHttpResponse(m_responseData, m_responseOffset, task.getArg());
        } 
        pthread_mutex_unlock(&m_taskMutex);

        return 0;
    } 

    if (m_threadId == 0) {
        printf("ready create thread\n");    
        pthread_create(&m_threadId, NULL, httpLoop, this);
    }

    if (m_rear + 1 == m_front) {
        printf("the queue is full");
        return -1;
    }

    pthread_mutex_lock(&m_taskMutex);
    HttpTask *task = m_task + m_rear;
    task->setTask(method, url, param, arg);
    m_rear = (++m_rear) % MAX_TASK_NUM;
    pthread_cond_signal(&m_taskCond);
    pthread_mutex_unlock(&m_taskMutex);

    return 0;
}

void *HttpClientImp::httpLoop(void *arg){
    HttpClientImp *imp = (HttpClientImp *) arg;
    imp->run();
}

void HttpClientImp::run() {
    HttpTask *task = NULL;
    while (m_isRunning) {
        pthread_mutex_lock(&m_taskMutex);
        if (m_front == m_rear) {
            struct timespec start_tm;
            struct timespec end_tm;
            int timeout_ms = 2000;
	        clock_gettime(CLOCK_REALTIME, &start_tm);   
            end_tm = ns_to_tm(tm_to_ns(start_tm) + timeout_ms * 1000 * 1000);
            int ret = pthread_cond_timedwait(&m_taskCond, &m_taskMutex, &end_tm);

            if (!m_isRunning) {
                pthread_mutex_unlock(&m_taskMutex);
                break;
            }
        }
        if (m_front != m_rear) {
            task = m_task + m_front;
            printf("task front:%d, task rear:%d\n", m_front, m_rear);
            m_front = (++m_front) % MAX_TASK_NUM;
        } else {
            pthread_mutex_unlock(&m_taskMutex);
            continue;
        }

        pthread_mutex_unlock(&m_taskMutex);
        int ret = httpRequest(task->getMethod().c_str(), task->getUrl().c_str(), task->getParam().c_str(), task->getArg());
        if (ret == 0) {
            // 正常回复
            m_listener->onHttpResponse(m_responseData, m_responseOffset, task->getArg());
        }
    
    } 

}

size_t HttpClientImp::readFunc(void *dest, size_t size, size_t nmemb, void *user_data) {
    HttpClientImp *imp = (HttpClientImp *)user_data;
    char *data = imp->m_requestData;
    size_t expect_len = size * nmemb;
    int read_len = 0;
    int remain_len = imp->m_requestLen - imp->m_sendLen;
    if (remain_len > 0) {
        if (expect_len < remain_len) {
            read_len = expect_len;
        } else {
            read_len = remain_len;
        }
        memcpy(dest, data + imp->m_sendLen, read_len);
        imp->m_sendLen += read_len;
        return read_len;
    } else {
        return 0;
    }
}


size_t HttpClientImp::writeFunc(void *dest, size_t size, size_t nmemb, void *user_data) {
    HttpClientImp *imp = (HttpClientImp *)user_data;
    size_t receive_len = size * nmemb;
    if (receive_len + imp->m_responseOffset > imp->m_responseLen) {
        size_t expect_size = imp->m_responseOffset + receive_len + 1024;
        int ret = reallocMemSpace(imp->m_responseData, imp->m_responseLen, expect_size); 
        if (ret < 0) {
            printf("realloc response data failed\n");
            return -1;
        }
    }
    memcpy(imp->m_responseData + imp->m_responseOffset, dest, receive_len);
    imp->m_responseOffset += receive_len;
    return receive_len;
}

int HttpClientImp::httpRequest(const char *method, const char *url, const char *param, void *arg) {
    CURL *handle = curl_easy_init(); 
    CURLcode code = curl_easy_setopt(handle, CURLOPT_ERRORBUFFER, m_errorBuf);
    // debuggin info
    curl_easy_setopt(handle, CURLOPT_VERBOSE, 0L);
    curl_easy_setopt(handle, CURLOPT_HEADER, 0L);
    curl_easy_setopt(handle, CURLOPT_CONNECTTIMEOUT, m_connectTimeout);
    curl_easy_setopt(handle, CURLOPT_TIMEOUT, m_connectTimeout);
    curl_easy_setopt(handle, CURLOPT_READFUNCTION, HttpClientImp::readFunc);
    curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, HttpClientImp::writeFunc);
    curl_easy_setopt(handle, CURLOPT_WRITEDATA, (void *)this);
    curl_easy_setopt(handle, CURLOPT_READDATA, (void *)this);
    curl_easy_setopt(handle, CURLOPT_NOSIGNAL, 1L);

    m_headers = curl_slist_append(m_headers, "Connection: keep-alive");
    m_headers = curl_slist_append(m_headers, "Content-Type: application/json");
    m_headers = curl_slist_append(m_headers, "Accept-Encoding: UTF-8");
    m_headers = curl_slist_append(m_headers, "Cache-Control: max-age=0");
    m_headers = curl_slist_append(m_headers, "User-Agent: Macos/16.7");

    int param_len = strlen(param);
    curl_easy_setopt(handle, CURLOPT_HTTPHEADER, m_headers);
    curl_easy_setopt(handle, CURLOPT_URL, url);
    if (m_requestData == NULL || m_requestLen < param_len) {
        int ret = reallocMemSpace(m_requestData, m_requestLen, param_len);
        if (ret == -1) {
            m_errorStatus = HTTP_ERROR_NOMEMORY;
            const char *msg = "no enoug memory";
            m_listener->onHttpStatus(msg, strlen(msg) + 1, arg);
            return -1;
        }
    }
    memset(m_responseData, 0, m_responseLen);
    memset(m_requestData, 0, m_requestLen);
    memcpy(m_requestData, param, param_len);
    m_responseOffset = 0;
    m_sendLen = 0;

    if (strcmp(method,  "POST") == 0) {
        code = curl_easy_setopt(handle, CURLOPT_POST, 1L);
        code = curl_easy_setopt(handle, CURLOPT_POSTFIELDSIZE, param_len);
        //code = curl_easy_setopt(handle, CURLOPT_POSTFIELDS, param);
        m_requestLen = param_len;
    } else {
        code = curl_easy_setopt(handle, CURLOPT_HTTPGET, 1L);
    } 

    code = curl_easy_perform(handle);
    if (m_headers) {
        curl_slist_free_all(m_headers);
        m_headers = NULL;
    }
    if (code != CURLE_OK) {
        // 错误提示
        m_errorStatus = HTTP_ERROR_CURLFAILED;
        //const char *msg = curl_easy_strerror(code);
        //m_listener->onHttpStatus(msg, strlen(msg) + 1, arg);
        m_listener->onHttpStatus(m_errorBuf, strlen(m_errorBuf) + 1, arg);
        return -1;
    } 
    // 正确响应

    m_errorStatus = HTTP_ERROR_SUCCESS;
    return 0;
}




