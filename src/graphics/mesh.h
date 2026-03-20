#pragma once
#include <glad/glad.h>
#include <vector>
#include <memory>
#include "material.h"

class Mesh {
        public:
                Mesh(const std::vector<float>& vertices, std::shared_ptr<Material> materialPtr);
                ~Mesh();

                void render();
                Material* getMaterialPtr();
                void setMaterialPtr(std::shared_ptr<Material> material);
        private:
                std::vector<float> vertices;
                std::shared_ptr<Material> materialPtr;
                unsigned int VAO, VBO;
                int vertexCount;

                void setupMesh();
};
