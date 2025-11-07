#pragma once
#include <GL/glew.h>
#include "color.h"
#include <string>
#include "shader.h"
#include <memory>

class Material {
        public:
                Material(const Color& color, const float shininess, const std::string textureInfo);
                ~Material();

                Color getMaterialColor();
                float getShininess();
                std::string getTextureInfo();

                void applyShaders(Shader* shader);
                Material* getPtr();
        private:
                std::shared_ptr<Material> materialPtr;
                Color color;
                float shininess;
                std::string textureInfo;
};
