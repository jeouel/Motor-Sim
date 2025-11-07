#include "material.h"

Material::Material(const Color& newColor, float newShininess, std::string newTextureInfo) : color(newColor) {
        shininess = newShininess;
        textureInfo = newTextureInfo;
}


Material::~Material() {

}

Color Material::getMaterialColor() {
        return color;
}

float Material::getShininess() {
        return shininess;
}

std::string Material::getTextureInfo() {
        return textureInfo;
}

void Material::applyShaders(Shader* shader) {
        shader->setVec4("setColor", color.getColor());
}

Material* Material::getPtr() {
        return this;
}

