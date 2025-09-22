#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "shader.h"

class Renderer {
public:
        Renderer();
        ~Renderer();
    
        bool initialize(int width, int height);
        void render();
        bool shouldClose();
        void swapBuffers();
        void pollEvents();
        void cleanup();

private:
        GLFWwindow* window;
        Shader* shader;
        unsigned int VAO, VBO;
    
        glm::mat4 view;
        glm::mat4 projection;
    
        void setupPlane();
        static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
};
