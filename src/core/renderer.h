#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <memory>
#include "../graphics/shader.h"
#include "../shapes/shape2D.h"
#include "camera.h"


class Renderer {
public:
        Renderer();
        ~Renderer();
    
        bool initialize(int width, int height);
        void render();
        bool shouldClose();
        void swapBuffers();
        void pollEvents();
        void processInput(float deltaTime);
        void cleanup();
        void addShape(Shape2D* shape);

private:
        GLFWwindow* window;
        Shader* shader;
        Camera* camera;
        
        std::vector<std::unique_ptr<Shape2D>> shapes;

        glm::mat4 view;
        glm::mat4 projection;

        bool firstMouse = true;
        float lastX = 400, lastY = 300;

        static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
        static void mouse_callback(GLFWwindow* window, double xpos, double ypos);

        void handleMouse(double xpos, double ypos);
};
