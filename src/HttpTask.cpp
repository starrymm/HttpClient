#include "HttpTask.h"

HttpTask::HttpTask() {

}

HttpTask::~HttpTask() {

}

void HttpTask::setTask(const std::string &url, const std::string &param, void *arg) {   
    m_url = url;
    m_param = param;
    m_arg = arg;
}

std::string HttpTask::getUrl() {
    return m_url;    
}

std::string HttpTask::getParam() {
    return m_param;
}

void *HttpTask::getArg() {
    return m_arg;
}