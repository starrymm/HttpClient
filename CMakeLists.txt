CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(SOCKET)
SET(VERSION 1.0)
SET(CMAKE_BUILD_TYPE Debug)


SET(BUILD_PATH "${CMAKE_BINARY_DIR}")
SET(ROOT "${CMAKE_SOURCE_DIR}")

SET(CXXFLAGS "-fPIC -finline-functions -Wall -Winline -pipe -ffast-math -std=c++0x -ldl -g")
SET(CFLAGS "-fPIC -finline-functions -Wall -Winline -pipe -ffast-math -lstdc++ -ldl -g")

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/include)
ADD_SUBDIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/src)
ADD_SUBDIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/bin)
#ADD_EXECUTABLE(ServerApp Server.cpp test_server.cpp)
#TARGET_LINK_LIBRARIES(ServerApp pthread)
