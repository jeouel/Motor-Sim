#include "renderer.h"
#include <iostream>

Renderer::Renderer() : window(nullptr), shader(nullptr) {}

Renderer::~Renderer() {
        cleanup();
}

bool Renderer::initialize(int width, int height) {
        // Initialize GLFW
        if (!glfwInit()) {
                std::cerr << "Failed to initialize GLFW" << std::endl;
                return false;
        }
    
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
        window = glfwCreateWindow(width, height, "Engine Simulation", NULL, NULL);
        if (!window) {
                std::cerr << "Failed to create GLFW window" << std::endl;
                glfwTerminate();
                return false;
        }
    
        glfwMakeContextCurrent(window);
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    
        // Initialize GLEW
        if (glewInit() != GLEW_OK) {
                std::cerr << "Failed to initialize GLEW" << std::endl;
                return false;
        }
    
        // Enable depth testing
        glEnable(GL_DEPTH_TEST);
    
        // Load shaders
        shader = new Shader("shaders/vertex.glsl", "shaders/fragment.glsl");
    
        // Setup matrices
        view = glm::lookAt(glm::vec3(0.0f, 5.0f, 10.0f),
                glm::vec3(0.0f, 0.0f, 0.0f),
                glm::vec3(0.0f, 1.0f, 0.0f));
    
        projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);
    
        return true;
}

void Renderer::addMesh(std::unique_ptr<Mesh> mesh) {
        meshes.push_back(std::move(mesh));
}

void Renderer::render() {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
        shader->use();
        shader->setVec4("setColor", glm::vec4(0.4, 0.6, 0.2, 1.0));
        shader->setMat4("view", view);
        shader->setMat4("projection", projection );

        for (const auto& mesh : meshes) {
                glm::mat4 model = glm::mat4(1.0f);
                shader->setMat4("model", model);
                mesh->render();
        }
}

bool Renderer::shouldClose() {
        return glfwWindowShouldClose(window);
}

void Renderer::swapBuffers() {
        glfwSwapBuffers(window);
}

void Renderer::pollEvents() {
        glfwPollEvents();
}

void Renderer::cleanup() {
        meshes.clear();
        delete shader;
    
        if (window) {
                glfwDestroyWindow(window);
                glfwTerminate();
        }
}

void Renderer::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
        glViewport(0, 0, width, height);
}
