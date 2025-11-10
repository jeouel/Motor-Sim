#pragma once
#include <vector>
#include <memory>
#include <string>
#include <map>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../graphics/mesh.h"
#include "../graphics/material.h"

class Shape2D {
public:
    Shape2D(const std::vector<glm::vec3>& points, const std::string& name);
    ~Shape2D();

    void translate(const glm::vec3& offset);
    void scale(const glm::vec3& scaleFactors);
    void rotate(float angleRadians, const glm::vec3& axis);

    void render(Shader* shader);

    int getID() const;
    std::string getName() const;

    glm::mat4 getTransformMatrix() const;
    Mesh* getMesh() const;
    void setMaterial(std::shared_ptr<Material> material);
    static Shape2D* getShapeByID(int id);
    static std::vector<int> getAllShapeIDs();
    static int getShapeCount();

private:
    int shapeID;
    std::string shapeName;
    std::vector<glm::vec3> vertices;

    std::unique_ptr<Mesh> mesh;
    std::shared_ptr<Material> material;

    glm::mat4 transformMatrix;

    static std::shared_ptr<std::map<int, Shape2D*>> shapeRegistry;

    std::vector<float> flattenVertices(const std::vector<glm::vec3>& points);
    static void initializeRegistry();
    static int generateNextID();
};