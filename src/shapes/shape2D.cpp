#include "shape2D.h"
#include <algorithm> 

std::shared_ptr<std::map<int, Shape2D*>> Shape2D::shapeRegistry = nullptr;


Shape2D::Shape2D(const std::vector<glm::vec3>& points, const std::string& name)
    : shapeName(name), vertices(points), transformMatrix(glm::mat4(1.0f)) {
    initializeRegistry();
    shapeID = generateNextID();

    (*shapeRegistry)[shapeID] = this;

    std::vector<float> flatVertices = flattenVertices(vertices);
    material = std::make_shared<Material>(Color::White(), 0.0f, "default_material");

    mesh = std::make_unique<Mesh>(flatVertices, material);
}

Shape2D::~Shape2D() {

    if (shapeRegistry && shapeRegistry->count(shapeID)) {
        shapeRegistry->erase(shapeID);
    }
}

void Shape2D::translate(const glm::vec3& offset) {
    transformMatrix = glm::translate(transformMatrix, offset);
}

void Shape2D::scale(const glm::vec3& scaleFactors) {
    transformMatrix = glm::scale(transformMatrix, scaleFactors);
}

void Shape2D::rotate(float angleRadians, const glm::vec3& axis) {
    transformMatrix = glm::rotate(transformMatrix, angleRadians, axis);
}

void Shape2D::render(Shader* shader) {
    shader->setMat4("model", transformMatrix);
    material->applyShaders(shader);
    mesh->render();
}

int Shape2D::getID() const { return shapeID; }

std::string Shape2D::getName() const { return shapeName; }

glm::mat4 Shape2D::getTransformMatrix() const { return transformMatrix; }

Mesh* Shape2D::getMesh() const { return mesh.get(); }

void Shape2D::setMaterial(std::shared_ptr<Material> newMaterial) {
    material = newMaterial;
    if (mesh) {
        mesh->setMaterialPtr(material);
    }
}

void Shape2D::initializeRegistry() {
    if (!shapeRegistry) {
        shapeRegistry = std::make_shared<std::map<int, Shape2D*>>();
    }
}

int Shape2D::generateNextID() {
    if (shapeRegistry->empty()) {
        return 0;
    }
    auto maxElement = std::max_element(shapeRegistry->begin(), shapeRegistry->end(),
        [](const auto& a, const auto& b) {
            return a.first < b.first;
        });
    return maxElement->first + 1;
}

Shape2D* Shape2D::getShapeByID(int id) {
    if (shapeRegistry && shapeRegistry->count(id)) {
        return (*shapeRegistry)[id];
    }
    return nullptr;
}

std::vector<int> Shape2D::getAllShapeIDs() {
    std::vector<int> ids;
    if (shapeRegistry) {
        for (const auto& pair : *shapeRegistry) {
            ids.push_back(pair.first);
        }
    }
    return ids;
}

int Shape2D::getShapeCount() {
    if (shapeRegistry) {
        return shapeRegistry->size();
    }
    return 0;
}


std::vector<float> Shape2D::flattenVertices(const std::vector<glm::vec3>& points) {
    std::vector<float> flatVertices;
    flatVertices.reserve(points.size() * 3);
    for (const auto& vec : points) {
        flatVertices.push_back(vec.x);
        flatVertices.push_back(vec.y);
        flatVertices.push_back(vec.z);
    }
    return flatVertices;
}