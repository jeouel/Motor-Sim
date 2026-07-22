#pragma once
#include <vector>
#include <memory>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../graphics/mesh.h"
#include "../graphics/material.h"
#include "vertex.h"

class Shape {
public:
	Shape(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const std::string& name); 
	
	virtual ~Shape() = default;

	void translate(const glm::vec3& offset);
	void scale(const glm::vec3& scaleFactors);
	void rotate(float angleRadians, const glm::vec3& axis);

	std::string getName() const;

	glm::mat4 getTransformMatrix() const;
	Mesh* getMesh() const;
	void setMaterial(std::shared_ptr<Material> material);

private:
	std::string shapeName;

	std::unique_ptr<Mesh> mesh;
	std::shared_ptr<Material> material;

	glm::mat4 transformMatrix;
};

