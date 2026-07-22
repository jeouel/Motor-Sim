#include "shape.h"
#include <algorithm>

Shape::Shape(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const std::string& name)
    : shapeName(name), transformMatrix(glm::mat4(1.0f)) {

    material = std::make_shared<Material>(Color::White(), 0.0f, "default_material");

    mesh = std::make_unique<Mesh>(vertices, indices, material);
}

void Shape::translate(const glm::vec3& offset) {
    transformMatrix = glm::translate(transformMatrix, offset);
}

void Shape::scale(const glm::vec3& scaleFactors) {
    transformMatrix = glm::scale(transformMatrix, scaleFactors);
}

void Shape::rotate(float angleRadians, const glm::vec3& axis) {
    transformMatrix = glm::rotate(transformMatrix, angleRadians, axis);
}

std::string Shape::getName() const { return shapeName; }

glm::mat4 Shape::getTransformMatrix() const { return transformMatrix; }

Mesh* Shape::getMesh() const { return mesh.get(); }

void Shape::setMaterial(std::shared_ptr<Material> newMaterial) {
    material = newMaterial;
    if (mesh) {
        mesh->setMaterialPtr(material);
    }
}
