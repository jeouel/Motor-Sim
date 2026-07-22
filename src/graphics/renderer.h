#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>
#include <memory>
#include "shader.h"
#include "camera.h"
#include "../scene/scene.h"


class Renderer {
public:
        Renderer();
        ~Renderer();
    
        bool initialize(int width, int height);
        void render(Camera* camera, Scene* scene);
        bool shouldClose();
        void swapBuffers();
        void pollEvents();
        GLFWwindow* getWindow();
        void cleanup();

private:
        GLFWwindow* window;
        Shader* shader;
        
        glm::mat4 view;
        glm::mat4 projection;

        static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
};
