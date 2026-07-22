#pragma once
#include <glad/glad.h>
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

                void applyTempColor(Shader* shader, Color newColor);
                void applyShaders(Shader* shader);
        private:
                std::shared_ptr<Material> materialPtr;
                Color color;
                float shininess;
                std::string textureInfo;
};
