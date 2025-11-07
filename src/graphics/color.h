#pragma once
#include <glm/glm.hpp>

class Color {
        public:
                Color();
                Color(float r, float g, float b, float opacity);
                ~Color();
                
                glm::vec4 getColor();
                Color* getPtr();

                static Color Red();
                static Color Green();
                static Color Blue();
                static Color White();
                static Color Black();
        private:
                glm::vec4 color;
};
