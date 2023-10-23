#ifndef __HTTP_CLIENT_H__
#define __HTTP_CLIENT_H__

class HttpClientListener {
public:
    virtual void onHttpResponse(const char *data, int data_lenth, void *arg) = 0;
    virtual void onHttpStatus(const char *data, int data_lenth, void *arg) = 0;
};


class HttpClient {
public:
    HttpClient(int connect_timeout);
    ~HttpClient();

public:
    // todo 代码注释风格
    void setListener(HttpClientListener *listener);
    int appendHeader(const char *key, const char *value); 
    int addGetRequest(const char *url, void *arg);
    int addPostRequest(const char *url, const char* param, void *arg);
    int addBlockGetRequest(const char *url, void *arg);
    int addBlockPostRequest(const char *url, const char *param, void *arg);

public:
    void *m_imp;
};

#endif
