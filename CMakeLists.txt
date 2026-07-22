cmake_minimum_required(VERSION 3.16)
project(EngineSimulation VERSION 0.4)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)

if(NOT CMAKE_BUILD_TYPE)
        set(CMAKE_BUILD_TYPE Debug)
endif()

set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -DDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")

add_executable(engine_sim
        src/main.cpp
        src/core/controller.cpp 
        src/graphics/renderer.cpp
        src/graphics/camera.cpp
        src/graphics/shader.cpp
        src/graphics/mesh.cpp
        src/graphics/material.cpp
        src/graphics/color.cpp
        src/shapes/shape.cpp
	src/scene/scene.cpp
        # 2. Added GLAD source file
        external/lib/glad.c
)


target_include_directories(engine_sim PRIVATE external/lib/include)

target_link_libraries(engine_sim
        glfw
        OpenGL::GL
)

file(COPY ${CMAKE_SOURCE_DIR}/shaders
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
