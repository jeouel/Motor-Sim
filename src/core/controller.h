#pragma once

#include <GLFW/glfw3.h>

#include "../graphics/camera.h"

class Controller {
public:
        Controller(GLFWwindow* window, Camera* camera);
        ~Controller();

        void processInput(float deltaTime);
        void handleMouse(double xpos, double ypos);

        static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
private:
        GLFWwindow* window;
        Camera* camera;

        bool firstMouse = true;
        float lastX = 0.0;
        float lastY = 0.0;
};
