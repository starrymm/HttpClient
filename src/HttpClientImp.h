#ifndef __HTTP_CLIENT_IMP_H__
#define __HTTP_CLIENT_IMP_H__
#include <pthread.h>
#include <memory.h>
#include <curl/curl.h>
#include "HttpClient.h"
#include "HttpTask.h"

#define MAX_TASK_NUM 200

typedef enum {
    HTTP_ERROR_SUCCESS = 0,
    HTTP_ERROR_NOMEMORY = 1,
    HTTP_ERROR_CURLFAILED = 2
}HTTP_ERROR_STATUS;

class HttpClientImp {
public:
    HttpClientImp(int connect_timeout);
    ~HttpClientImp();

public:
    void setListener(HttpClientListener *listener);
    int appendHeader(const char *key, const char *value); 
    int addGetRequest(const char *url, void *arg);
    int addPostRequest(const char *url, const char* param, void *arg);
    int addBlockGetRequest(const char *url, void *arg);
    int addBlockPostRequest(const char *url, const char *param, void *arg);

private:
    int addTask(const char *method, bool block, const char *url, const char *param, void *arg);
    int httpRequest(const char *method, const char *url, const char *param, void *arg);
    static void *httpLoop(void *arg);
    static size_t readFunc(void *dest, size_t size, size_t nmemb, void *user_data);
    static size_t writeFunc(void *buffer, size_t size, size_t nmemb, void *user_data); 
    //int reallocMemSpace(char *&data, int &data_size, int expect_size);
    void run();

private:
    int m_connectTimeout;
    HttpClientListener *m_listener;

    HttpTask *m_task;
    int m_front;
    int m_rear;
    pthread_mutex_t m_taskMutex;
    pthread_cond_t m_taskCond;
    char m_errorBuf[256];

    char *m_responseData;
    int m_responseOffset;
    int m_responseLen;
    char *m_requestData;
    int m_requestLen;
    int m_sendLen;
    int m_remainLen;
    HTTP_ERROR_STATUS m_errorStatus; 
    struct curl_slist *m_headers;

    bool m_isRunning;
    pthread_t m_threadId;    
}; 

#endif
