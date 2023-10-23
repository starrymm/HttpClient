#ifndef __HTTP_TASK_H__
#define __HTTP_TASK_H__
#include <string>

class HttpTask {
public:
    HttpTask();
    ~HttpTask();
    void setTask(const std::string &method, const std::string &url, const std::string &param, void *arg);
    std::string getUrl();
    std::string getParam();
    std::string getMethod();
    void *getArg();
private:
    std::string m_url;
    std::string m_param;
    std::string m_method;
    void *m_arg;
};

#endif