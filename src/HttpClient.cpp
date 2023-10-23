#include <stdio.h>

#include "HttpClient.h"
#include "HttpClientImp.h"


HttpClient::HttpClient(int connect_timeout) {
    m_imp = new HttpClientImp(connect_timeout);
}

HttpClient::~HttpClient() {
    if (m_imp) {
        HttpClientImp *imp = (HttpClientImp *) m_imp; 
        delete imp;
        imp = NULL;
    }
}

int HttpClient::appendHeader(const char *key, const char *value) {
    HttpClientImp *imp = (HttpClientImp *) m_imp;
    imp->appendHeader(key, value);
    return 0;
}

int HttpClient::addGetRequest(const char *url, void *arg) {
    HttpClientImp *imp = (HttpClientImp *) m_imp;
    return imp->addGetRequest(url, arg);
}

int HttpClient::addBlockGetRequest(const char *url, void *arg) {
    HttpClientImp *imp = (HttpClientImp *) m_imp;
    return imp->addBlockGetRequest(url, arg);
}

int HttpClient::addPostRequest(const char *url, const char *param, void *arg) {
    HttpClientImp *imp = (HttpClientImp *) m_imp;
    return imp->addPostRequest(url, param, arg);
}

int HttpClient::addBlockPostRequest(const char*url, const char *param, void *arg){
    HttpClientImp *imp = (HttpClientImp *) m_imp;
    return imp->addBlockPostRequest(url, param, arg);
}

void HttpClient::setListener(HttpClientListener *listener) {
    HttpClientImp *imp = (HttpClientImp *) m_imp;
    imp->setListener(listener); 
    return ;
}