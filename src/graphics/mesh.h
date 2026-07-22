#pragma once
#include <glad/glad.h>
#include <vector>
#include <memory>
#include "material.h"
#include "../shapes/vertex.h"

class Mesh {
        public:
                Mesh(const std::vector<Vertex>& verts, const std::vector<unsigned int>& inds ,std::shared_ptr<Material> mat);
                ~Mesh();

                void draw();
                Material* getMaterialPtr();
                void setMaterialPtr(std::shared_ptr<Material> material);
        private:
                std::shared_ptr<Material> materialPtr;
                unsigned int VAO, VBO, EBO;
		unsigned int indexCount;			
		
                void setupMesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);
};
