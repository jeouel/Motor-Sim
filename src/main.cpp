#include "renderer.h"
#include <iostream>

int main() {
        Renderer renderer;
    
        if (!renderer.initialize(800, 600)) {
                std::cerr << "Failed to initialize renderer" << std::endl;
                return -1;
        }
    
        // Main render loop
        while (!renderer.shouldClose()) {
                renderer.pollEvents();
                renderer.render();
                renderer.swapBuffers();
        }
    
        return 0;
}
