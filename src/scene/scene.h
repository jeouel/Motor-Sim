#pragma once

#include <glad/glad.h>
#include <vector>
#include <map>
#include "../shapes/shape.h"

class Scene {
public:
        Scene();
        virtual ~Scene() = default;

        int addShape(Shape* shape);
        void deleteShape(int id);

        static Shape* getShapeById(int id);
        static std::vector<int> getShapeIdList();
        static int getShapeCount();

private:
        static std::shared_ptr<std::map<int, Shape*>> shapeRegistery;
        static void initializeRegistry();
        static int generateNextID();
};
