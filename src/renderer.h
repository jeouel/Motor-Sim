#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <memory>
#include "shader.h"
#include "mesh.h"

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
        void addMesh(std::unique_ptr<Mesh> mesh);

private:
        GLFWwindow* window;
        Shader* shader;
        
        std::vector<std::unique_ptr<Mesh>> meshes;

        glm::mat4 view;
        glm::mat4 projection;

        static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
};
