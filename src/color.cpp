#include "color.h"
#include <iostream>

Color::Color() {
        color = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
}

Color::Color(float r, float g, float b, float opacity) 
{
        color = glm::vec4(r, g, b, opacity);
}

Color::~Color(){}

glm::vec4 Color::getColor() {
        return color;
}

Color* Color::getPtr() {
        return this;
}

Color Color::Red() { return Color(1.0f, 0.0f, 0.0f, 1.0f); }
Color Color::Green() { return Color(0.0f, 1.0f, 0.0f, 1.0f); }
Color Color::Blue() { return Color(0.0f, 0.0f, 1.0f, 1.0f); }
Color Color::White() { return Color(1.0f, 1.0f, 1.0f, 1.0f); }
Color Color::Black() { return Color(0.0f, 0.0f, 0.0f, 1.0f); }
