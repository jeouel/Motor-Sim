#include "graphics/color.h"
#include "graphics/material.h"
#include "core/renderer.h"
#include "shapes/shape2D.h" 
#include <iostream>
#include <vector>

int main() {
	Renderer renderer;
	if (!renderer.initialize(800, 600)) {
		std::cerr << "Failed to initialize renderer" << std::endl;
		return -1;
	}

	std::vector<glm::vec3> planeVertices = {
	    glm::vec3(-5.0f, 0.0f, -5.0f), glm::vec3(5.0f, 0.0f, -5.0f), glm::vec3(5.0f,  0.0f, 5.0f),
	    glm::vec3(-5.0f, 0.0f, -5.0f), glm::vec3(5.0f, 0.0f, 5.0f),  glm::vec3(-5.0f, 0.0f, 5.0f)
	};

	std::vector<glm::vec3> triangleVertices = {
		glm::vec3(0.0f, 2.0f, 0.0f), 
		glm::vec3(-1.0f, 1.0f, 0.0f),
		glm::vec3(1.0f, 1.0f, 0.0f)
	};

	Shape2D plane(planeVertices, "GroundPlane");
	Shape2D triangle(triangleVertices, "PlayerTriangle");

	plane.setMaterial(std::make_shared<Material>(Color::Blue(), 0.0f, "plane_material"));
	triangle.setMaterial(std::make_shared<Material>(Color::Red(), 0.0f, "triangle_material"));

	renderer.addShape(&plane);
	renderer.addShape(&triangle);

	triangle.translate(glm::vec3(0.0f, 1.0f, 0.0f));
	triangle.scale(glm::vec3(1.5f)); // Uniform scale

	float deltaTime = 0.0f;
	float lastFrame = 0.0f;

	while (!renderer.shouldClose()) {
		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		renderer.processInput(deltaTime);

		renderer.pollEvents();
		renderer.render();
		renderer.swapBuffers();
	}

	return 0;
}
