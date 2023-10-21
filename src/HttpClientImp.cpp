#include "HttpClientImp.h"
#include <malloc.h>

HttpClientImp::HttpClientImp(int connect_timeout, HttpClientListener *listener) {
    m_connectTimeout = connect_timeout;
    m_listener = listener;

    m_task = NULL;
    m_front = 0;
    m_rear = 0;
    m_taskMutex = PTHREAD_MUTEX_INITIALIZER;
    m_taskCond = PTHREAD_COND_INITIALIZER;
    
    m_responseData = NULL;
    m_responseLen = 0;
    m_requestData = NULL;
    m_requestLen = 0;
    
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
        m_isRunning = false;
        pthread_cond_signal(&m_taskCond); 
    }
}

int HttpClientImp::appendHeader(const char *key, const char *value) {
    return 0;
}

int HttpClientImp::addGetRequest(const char *url, void *arg) {
    return addTask(REQUEST_GET, false, url, NULL, arg);    
}

int HttpClientImp::addPostRequest(const char *url, const char* param, void *arg) {
    return addTask(REQUEST_POST, false, url, param, arg);    
}

int HttpClientImp::addBlockGetRequest(const char *url, void *arg) {
    return addTask(REQUEST_GET, true, url, NULL, arg);    
}

int HttpClientImp::addBlockPostRequest(const char *url, const char *param, void *arg) {
    return addTask(REQUEST_POST, true, url, param, arg);    
}

int HttpClientImp::addTask(REQUEST_TYPE type, bool block, const char *url, const char *param, void *arg) {
    return 0;
}
