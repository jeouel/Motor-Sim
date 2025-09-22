cmake_minimum_required(VERSION 3.16)
project(EngineSimulation)

set(CMAKE_CXX_STANDARD 17)

find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)
find_package(GLEW REQUIRED)

add_executable(engine_sim
        src/main.cpp
        src/renderer.cpp
        src/shader.cpp
)

target_link_libraries(engine_sim
        glfw
        GLEW::GLEW
        GL
)

# Copy shaders to build directory
file(COPY ${CMAKE_SOURCE_DIR}/src/shaders
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
