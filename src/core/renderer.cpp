#include "renderer.h"
#include <iostream>


Renderer::Renderer() : window(nullptr), shader(nullptr), camera(nullptr) {}

Renderer::~Renderer() {
        if (camera) {
                delete camera;
        }
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

        // Set user pointer and mouse callback
        // glfwSetWindowUserPointer(window, this);
        // glfwSetCursorPosCallback(window, mouse_callback);
        // glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    
        // Initialize GLEW
        if (glewInit() != GLEW_OK) {
                std::cerr << "Failed to initialize GLEW" << std::endl;
                return false;
        }
    
        // Enable depth testing
        glEnable(GL_DEPTH_TEST);
    
        // Load shaders
        shader = new Shader("shaders/vertex.glsl", "shaders/fragment.glsl");
    
        // Setup camera
        camera = new Camera(glm::vec3(0.0f, 5.0f, 10.0f));
        projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);
    
        return true;
}

void Renderer::addShape(Shape2D* shape) {
        shapes.push_back(std::unique_ptr<Shape2D>(shape));
}

void Renderer::render() {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
        glm::mat4 view = camera->getViewMatrix();
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
                glPolygonOffset(1.0f, 1.0f); 

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

void Renderer::processInput(float deltaTime) {
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
                camera->processKeyboard(FORWARD, deltaTime);
        }
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
                camera->processKeyboard(BACKWARD, deltaTime);
        }
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
                camera->processKeyboard(LEFT, deltaTime);
        }
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
                camera->processKeyboard(RIGHT, deltaTime);
        }
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
                camera->processKeyboard(UP, deltaTime);
        }
        if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
                camera->processKeyboard(DOWN, deltaTime);
        }

        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
                camera->processArrows(UP, deltaTime);
        }
        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
                camera->processArrows(DOWN, deltaTime);
        }
        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
                camera->processArrows(LEFT, deltaTime);
        }
        if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
                camera->processArrows(RIGHT, deltaTime);
        }

        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
                glfwSetWindowShouldClose(window, true  );
        }
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

// void Renderer::mouse_callback(GLFWwindow* window, double xpos, double ypos) {
//     Renderer* renderer = static_cast<Renderer*>(glfwGetWindowUserPointer(window));
//     if (renderer) {
//         renderer->handleMouse(xpos, ypos);
//     }
// }

// void Renderer::handleMouse(double xpos, double ypos) {
//     if (firstMouse) {
//         lastX = xpos;
//         lastY = ypos;
//         firstMouse = false;
//     }

//     float xoffset = xpos - lastX;
//     float yoffset = lastY - ypos; // Reversed since y-coordinates go from bottom to top
//     lastX = xpos;
//     lastY = ypos;

//     camera->processMouseMovement(xoffset, yoffset);
// }
