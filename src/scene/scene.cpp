#include "scene.h"

std::shared_ptr<std::map<int, Shape*>> Scene::shapeRegistery; 

Scene::Scene() {
}

int Scene::generateNextID() {
        initializeRegistry();
        if (shapeRegistery->empty()) {
                return 0;
        }
        return shapeRegistery->rbegin()->first + 1;
        
}

void Scene::initializeRegistry() {
        if (!shapeRegistery) {
                shapeRegistery = std::make_shared<std::map<int, Shape*>>();
        }
}

int Scene::addShape(Shape* shape) {
        initializeRegistry();
	int id = generateNextID();
        shapeRegistery->insert({id, shape});
	return id;
}

void Scene::deleteShape(int id) {
        initializeRegistry();
        if (auto search = shapeRegistery->find(id); search != shapeRegistery->end()) {
                shapeRegistery->erase(id);
        }
}

Shape* Scene::getShapeById(int id) {
        initializeRegistry();
        if (auto search = shapeRegistery->find(id); search != shapeRegistery->end()) {
                return search->second;
        }
	return nullptr;
}


std::vector<int> Scene::getShapeIdList() {
        initializeRegistry();
        std::vector<int> ids;
        if (shapeRegistery->size()) {
                for (const auto& pair : *shapeRegistery) {
                        ids.push_back(pair.first);
                }
        }
        return ids;
}


int Scene::getShapeCount() {
        initializeRegistry();
        return shapeRegistery->size();
}
