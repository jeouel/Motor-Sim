cmake_minimum_required(VERSION 3.16)
project(EngineSimulation)

set(CMAKE_CXX_STANDARD 17)

find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)
find_package(GLEW REQUIRED)

if(NOT CMAKE_BUILD_TYPE)
        set(CMAKE_BUILD_TYPE Debug)
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -DDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")

add_executable(engine_sim
        src/main.cpp
        src/renderer.cpp
        src/shader.cpp
        src/mesh.cpp
        src/material.cpp
        src/color.cpp
)

target_link_libraries(engine_sim
        glfw
        GLEW::GLEW
        GL
)

file(COPY ${CMAKE_SOURCE_DIR}/src/shaders
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
