cmake_minimum_required(VERSION 3.20)
project(Client)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS -pthread)

include_directories(Source_Files)

add_executable(Client
        Source_Files/ball.cpp
        Source_Files/ball.hpp
        Source_Files/breakout.cpp
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
        Source_Files/SocketClient.cpp
        Source_Files/SocketClient.h
        Source_Files/wall.cpp
        Source_Files/wall.hpp)

find_package(OpenGL REQUIRED COMPONENTS OpenGL)
find_package(GLUT REQUIRED)

add_dependencies(Client OpenGL::OpenGL)
include_directories(${GLUT_INCLUDE_DIRS} )

target_link_libraries(Client OpenGL::OpenGL ${GLUT_LIBRARY} )