cmake_minimum_required(VERSION 4.0.0)
project(openGl_game)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

add_executable(openGl_game 
    src/config.h 
    src/main.cpp 
    src/glad.c
    src/shader.h
    src/shader.cpp
    src/texture.h
    src/texture.cpp
    src/camera.h
    src/camera.cpp)

target_include_directories(openGl_game PRIVATE dependencies)

target_link_libraries(openGl_game glfw OpenGL::GL)

set(CMAKE_CXX_FLAGS "-std=c++11")
