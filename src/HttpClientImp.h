#ifndef __HTTP_CLIENT_IMP_H__
#define __HTTP_CLIENT_IMP_H__
#include <pthread.h>
#include <memory.h>
#include "HttpClient.h"
#include "HttpTask.h"

enum REQUEST_TYPE {
    REQUEST_GET = 1,
    REQUEST_POST 
};

#define MAX_TASK_NUM 200

class HttpClientImp {
public:
    HttpClientImp(int connect_timeout, HttpClientListener *listener);
    ~HttpClientImp();

public:
    int appendHeader(const char *key, const char *value); 
    int addGetRequest(const char *url, void *arg);
    int addPostRequest(const char *url, const char* param, void *arg);
    int addBlockGetRequest(const char *url, void *arg);
    int addBlockPostRequest(const char *url, const char *param, void *arg);

private:
    int addTask(REQUEST_TYPE type, bool block, const char *url, const char *param, void *arg);

private:
    int m_connectTimeout;
    HttpClientListener *m_listener;

    HttpTask *m_task;
    int m_front;
    int m_rear;
    pthread_mutex_t m_taskMutex;
    pthread_cond_t m_taskCond;

    char *m_responseData;
    int m_responseLen;
    char *m_requestData;
    int m_requestLen;

    bool m_isRunning;
    pthread_t m_threadId;    
}; 

#endif
