#pragma once
#include <GL/glew.h>
#include <vector>

class Mesh {
        public:
                Mesh(const std::vector<float>& vertices);
                ~Mesh();

                void render();
        private:
                std::vector<float> vertices;
                unsigned int VAO, VBO;
                int vertexCount;

                void setupMesh();
};
