#include "HttpTask.h"

HttpTask::HttpTask() {

}

HttpTask::~HttpTask() {

}

void HttpTask::setTask(const std::string &method, const std::string &url, const std::string &param, void *arg) {   
    m_url = url;
    m_param = param;
    m_method = method;
    m_arg = arg;
}

std::string HttpTask::getUrl() {
    return m_url;    
}

std::string HttpTask::getParam() {
    return m_param;
}

std::string HttpTask::getMethod() {
    return m_method;
}

void *HttpTask::getArg() {
    return m_arg;
}
