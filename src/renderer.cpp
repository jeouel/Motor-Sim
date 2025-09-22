#include "renderer.h"
#include <iostream>

Renderer::Renderer() : window(nullptr), shader(nullptr), VAO(0), VBO(0) {}

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
    
        // Setup plane geometry
        setupPlane();
    
        // Setup matrices
        view = glm::lookAt(glm::vec3(0.0f, 5.0f, 10.0f),
                glm::vec3(0.0f, 0.0f, 0.0f),
                glm::vec3(0.0f, 1.0f, 0.0f));
    
        projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);
    
        return true;
}

void Renderer::setupPlane() {
        // Plane vertices (10x10 units, centered at origin)
        float vertices[] = {
                // positions
                -5.0f,  0.0f, -5.0f,
                5.0f,  0.0f, -5.0f,
                5.0f,  0.0f,  5.0f,
        
                -5.0f,  0.0f, -5.0f,
                 5.0f,  0.0f,  5.0f,
                -5.0f,  0.0f,  5.0f
        };
    
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
    
        glBindVertexArray(VAO);
    
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
    
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
}

void Renderer::render() {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
        shader->use();
    
        glm::mat4 model = glm::mat4(1.0f);
        shader->setMat4("model", model);
        shader->setMat4("view", view);
        shader->setMat4("projection", projection);
    
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);
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
        if (VAO) glDeleteVertexArrays(1, &VAO);
        if (VBO) glDeleteBuffers(1, &VBO);
        delete shader;
    
        if (window) {
                glfwDestroyWindow(window);
                glfwTerminate();
        }
}

void Renderer::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
        glViewport(0, 0, width, height);
}
