#include "graphics/color.h"
#include "graphics/material.h"
#include "graphics/renderer.h"
#include "core/controller.h"
#include "shapes/shape.h"
#include "scene/scene.h"
#include <iostream>
#include <vector>

int main() {
	Renderer renderer;
	if (!renderer.initialize(800, 600)) {
		std::cerr << "Failed to initialize renderer" << std::endl;
		return -1;
	}

        Camera* camera = new Camera(glm::vec3(0.0f, 5.0f, 10.0f));
        Controller controller(renderer.getWindow(), camera);

	std::vector<Vertex> planeVertices = {
		{glm::vec3(-5.0f, 0.0f, -5.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f)},
		{glm::vec3( 5.0f, 0.0f, -5.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 0.0f)},
		{glm::vec3( 5.0f, 0.0f,  5.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 1.0f)},
		{glm::vec3(-5.0f, 0.0f, -5.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 0.0f)},
		{glm::vec3( 5.0f, 0.0f,  5.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(1.0f, 1.0f)},
		{glm::vec3(-5.0f, 0.0f,  5.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 1.0f)}
	};
	std::vector<unsigned int> planeIndices = {0, 1, 2, 3, 4, 5};

	std::vector<Vertex> triangleVertices = {
		{glm::vec3( 0.0f, 2.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.5f, 1.0f)}, 
		{glm::vec3(-1.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
		{glm::vec3( 1.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f)}
	};
	std::vector<unsigned int> triangleIndices = {0, 1, 2};

	Shape plane(planeVertices, planeIndices, "GroundPlane");
	Shape triangle(triangleVertices, triangleIndices, "PlayerTriangle");

	plane.setMaterial(std::make_shared<Material>(Color::Blue(), 0.0f, "plane_material"));
	triangle.setMaterial(std::make_shared<Material>(Color::Red(), 0.0f, "triangle_material"));
	
	Scene* scene1 = new Scene();
	
	scene1->addShape(&plane);
	scene1->addShape(&triangle);

	triangle.translate(glm::vec3(0.0f, 1.0f, 0.0f));
	triangle.scale(glm::vec3(1.5f)); // Uniform scale

	float deltaTime = 0.0f;
	float lastFrame = 0.0f;

	while (!renderer.shouldClose()) {
		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		controller.processInput(deltaTime);

		renderer.pollEvents();
		renderer.render(camera, scene1);
		renderer.swapBuffers();
	}

	delete scene1;
	delete camera;

	return 0;
}
