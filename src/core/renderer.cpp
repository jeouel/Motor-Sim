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

void Renderer::addShape(Shape2D* shape) {
        shapes.push_back(std::unique_ptr<Shape2D>(shape));
}

void Renderer::render() {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
        shader->use();
        shader->setMat4("view", view);
        shader->setMat4("projection", projection );

        for (const auto& shape : shapes) {
                shader->setMat4("model", shape->getTransformMatrix());

                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); 
                glLineWidth(3.0f); 
                shape->getMesh()->getMaterialPtr()->applyTempColor(shader, Color::Black());
                shape->getMesh()->render();

                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                glEnable(GL_POLYGON_OFFSET_FILL);
                glPolygonOffset(-1.0f, -1.0f); 

                shape->render(shader); 
                glDisable(GL_POLYGON_OFFSET_FILL);
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
        shapes.clear();
        delete shader;
    
        if (window) {
                glfwDestroyWindow(window);
                glfwTerminate();
        }
}

void Renderer::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
        glViewport(0, 0, width, height);
}
