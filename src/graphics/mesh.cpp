#include "mesh.h"
#include <cstddef>


Mesh::Mesh(const std::vector<Vertex>& verts,const std::vector<unsigned int>& inds, std::shared_ptr<Material> mat) 
	: materialPtr(mat), indexCount(inds.size()) {
        setupMesh(verts, inds);
}


Mesh::~Mesh() {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}


void Mesh::setupMesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices) {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER,
                        vertices.size() * sizeof(Vertex),
                        vertices.data(),
                        GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
			indices.size() * sizeof(unsigned int),
			indices.data(),
			GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
        glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));
	glEnableVertexAttribArray(2);

        glBindVertexArray(0);
}


void Mesh::draw() {
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}


Material* Mesh::getMaterialPtr() {
        return materialPtr.get();
}

void Mesh::setMaterialPtr(std::shared_ptr<Material> material) {
        materialPtr = material;
}


