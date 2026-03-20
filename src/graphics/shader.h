#pragma once
#include <glad/glad.h>
#include <string>
#include <glm/glm.hpp>

class Shader {
public:
        unsigned int ID;
    
        Shader(const char* vertexPath, const char* fragmentPath);
        void use();
        void setMat4(const std::string &name, const glm::mat4 &mat);
        void setVec4(const std::string &name, const glm::vec4 &vec);

private:
        std::string loadFile(const char* path);
        void checkCompileErrors(unsigned int shader, std::string type);
};
