cmake_minimum_required(VERSION 3.20)
project(Server)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS -pthread)

include_directories(Source_Files)

add_executable(Server
        Source_Files/main.cpp

        Source_Files/SocketServer.cpp
        Source_Files/SocketServer.h
        )

