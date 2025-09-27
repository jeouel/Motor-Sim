#include "renderer.h"
#include "material.h"
#include "color.h"
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

        Color blue = Color::Blue();
        Color red = Color::Red();
        auto material1 = std::make_shared<Material>( blue, 0.0f, "materiel1");
        auto material2 = std::make_shared<Material>( red, 0.0f, "materiel2");
        renderer.addMesh(std::make_unique<Mesh>(planeVertices, material1));
        renderer.addMesh(std::make_unique<Mesh>(triangleVertices, material2));

        // Main render loop
        while (!renderer.shouldClose()) {
                renderer.pollEvents();
                renderer.render();
                renderer.swapBuffers();
        }
    
        return 0;
}
