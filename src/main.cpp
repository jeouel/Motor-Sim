#include "renderer.h"
#include <iostream>

int main() {
        Renderer renderer;
    
        if (!renderer.initialize(800, 600)) {
                std::cerr << "Failed to initialize renderer" << std::endl;
                return -1;
        }
        
        std::vector<float> planeVertices = {
                -5.0f, 0.0f, -5.0f,
                5.0f, 0.0f, -5.0f,
                5.0f, 0.0f, 5.0f,

                -5.0f, 0.0f, -5.0f,
                5.0f, 0.0f, 5.0f,
                -5.0f, 0.0f, 5.0f
        };

        std::vector<float> triangleVertices = {
                0.0f, 2.0f, 0.0f,
                -1.0f, 1.0f, 0.0f,
                1.0f, 1.0f, 0.0f
        };

        renderer.addMesh(std::make_unique<Mesh>(planeVertices));
        renderer.addMesh(std::make_unique<Mesh>(triangleVertices));

        // Main render loop
        while (!renderer.shouldClose()) {
                renderer.pollEvents();
                renderer.render();
                renderer.swapBuffers();
        }
    
        return 0;
}
