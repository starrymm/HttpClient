#include "HttpClient.h"
#include <string.h>
#include <stdio.h>
#include <unistd.h>



class HttpReq : public HttpClientListener {

public:
    HttpReq(int connect_timeout) {
        m_client = new HttpClient(connect_timeout);
    }
    ~HttpReq() {
        if (m_client) {
            delete m_client;
            m_client = NULL;
        }
    }


public: virtual void onHttpResponse(const char *data, int data_lenth, void *arg) {
        printf("HttpResponse:%s\n", data);
        printf("data_length:%d\n", data_lenth);
    }

    virtual void onHttpStatus(const char *data, int data_lenth, void *arg) {
        printf("HttpStatus:%s\n", data);
        printf("data_length:%d\n", data_lenth);
    }

    int init() {
        if (m_client) {
            m_client->setListener(this);
        }
        return 0;
    }

    int appendHeader(const char *key, const char *value) {
        return 0;
        // if (m_client) {

        // }
    } 
    int addGetRequest(const char *url, void *arg) {
        if (m_client) {
            m_client->addGetRequest(url, arg);
        }
    }

    int addPostRequest(const char *url, const char* param, void *arg) {
        if (m_client) {
            m_client->addPostRequest(url, param, arg);
        }
    }

    int addBlockGetRequest(const char *url, void *arg) {
        if (m_client) {
            m_client->addBlockGetRequest(url, arg);
        }
    }

    int addBlockPostRequest(const char *url, const char *param, void *arg) {
        if (m_client) {
            m_client->addBlockPostRequest(url, param, arg);
        }
    }

private:
    HttpClient *m_client;
    
};


int main(int argc, char *argv[]) {
    HttpReq  *req = new HttpReq(5);
    req->init();    
    //req->addGetRequest("https://demo-api.apipost.cn/api/demo/news_list?mobile=18289454846&theme_news=国际新闻&page=1&pageSize=20", NULL);
    //req->addBlockGetRequest("https://demo-api.apipost.cn/api/demo/news_list?mobile=18289454846&theme_news=国际新闻&page=1&pageSize=20", NULL);

    char param[256] = "{\"query\":\"pop\"}";
    req->addPostRequest("https://console-mock.apipost.cn/mock/5ae3fd82-40c7-40b7-9f62-8c8f09f99e1a/getmyfaviratorsong?apipost_id=bb34d9", param, NULL);
    req->addBlockGetRequest("https://demo-api.apipost.cn/api/demo/news_list?mobile=18289454846&theme_news=国际新闻&page=1&pageSize=20", NULL);
    req->addBlockPostRequest("https://console-mock.apipost.cn/mock/5ae3fd82-40c7-40b7-9f62-8c8f09f99e1a/getmyfaviratorsong?apipost_id=bb34d9", param, NULL);
    req->addGetRequest("https://demo-api.apipost.cn/api/demo/news_list?mobile=18289454846&theme_news=国际新闻&page=1&pageSize=20", NULL);

    while(1) {
        sleep(100000);
    }
    return 0;
}
