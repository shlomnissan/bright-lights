# Copyright 2024 Betamark Pty Ltd. All rights reserved.
# Author: Shlomi Nissan (shlomi@betamark.com)

cmake_minimum_required(VERSION 3.22.1)

project(bright-lights)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

message(${CMAKE_SOURCE_DIR}/cmake)

include(cmake/ShaderString.cmake)
ShaderString()

find_package(fmt REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)

set(SHARED_SOURCES
    libs/glad/glad.c
    src/core/camera.cpp
    src/core/camera.h
    src/core/mesh.cpp
    src/core/mesh.h
    src/core/shader.cpp
    src/core/shader.h
    src/core/window.cpp
    src/core/window.h
    src/shared/grid.cpp
    src/shared/grid.h
)

set(PROGRAMS
    01_simple_light
)

add_executable(01_simple_light ${SHARED_SOURCES} src/01_simple_light/main.cpp)

foreach(THIS IN LISTS PROGRAMS)
    target_sources(${THIS} PRIVATE ${SHARED_SOURCES})
    target_include_directories(${THIS} PRIVATE
        ${CMAKE_SOURCE_DIR}/src
        ${CMAKE_SOURCE_DIR}/libs
    )
    target_link_libraries(${THIS} PRIVATE fmt::fmt glfw glm::glm OpenGL::GL)
endforeach()



