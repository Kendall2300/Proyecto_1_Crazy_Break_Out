cmake_minimum_required(VERSION 3.20)
project(Server)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS -pthread)

include_directories(.)
include_directories(Source_Files)

add_executable(Server
        Source_Files/Ball.cpp
        Source_Files/Ball.h
        Source_Files/Game.cpp
        Source_Files/Game.h
        Source_Files/main.cpp
        Source_Files/SocketServer.cpp
        Source_Files/SocketServer.h
        Source_Files/State.h
        Source_Files/State_Credits.cpp
        Source_Files/State_Credits.h
        Source_Files/State_Game.cpp
        Source_Files/State_Game.h
        Source_Files/State_Menu.cpp
        Source_Files/State_Menu.h)
