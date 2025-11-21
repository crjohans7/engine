cmake_minimum_required(VERSION 4.0.0)
project(render_engine)

set(CMAKE_CXX_STANDARD           11)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS        OFF)


find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

add_executable(${PROJECT_NAME} 
    src/config.h 
    src/main.cpp 
    src/glad.c
    src/shader.h
    src/shader.cpp
    src/texture.h
    src/texture.cpp
    src/camera.h
    src/camera.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE dependencies)

target_link_libraries(${PROJECT_NAME} glfw OpenGL::GL)
