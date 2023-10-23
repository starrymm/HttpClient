SET(SOURCE HttpClientTest.cpp)
ADD_EXECUTABLE(HttpClientTest ${SOURCE})
TARGET_LINK_LIBRARIES(HttpClientTest MyHttp)
TARGET_LINK_LIBRARIES(HttpClientTest curl)
