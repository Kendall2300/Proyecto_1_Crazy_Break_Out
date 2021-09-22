cmake_minimum_required(VERSION 3.20)
project(Client)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS -pthread)

include_directories(Source_Files)

add_executable(Client
        Source_Files/main.cpp
        Source_Files/SocketClient.cpp
        Source_Files/SocketClient.h
        )

