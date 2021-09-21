cmake_minimum_required(VERSION 3.20)
project(Server)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS -pthread)

include_directories(Source_Files)

add_executable(Server
        Source_Files/ball.cpp
        Source_Files/ball.hpp
        Source_Files/brick.cpp
        Source_Files/brick.hpp
        Source_Files/force.cpp
        Source_Files/force.hpp
        Source_Files/game.cpp
        Source_Files/game.hpp
        Source_Files/main.cpp
        Source_Files/painter.cpp
        Source_Files/painter.hpp
        Source_Files/pedal.cpp
        Source_Files/pedal.hpp
        Source_Files/SocketServer.cpp
        Source_Files/SocketServer.h
        Source_Files/wall.cpp
        Source_Files/wall.hpp)
