#include "shader.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/gtc/type_ptr.hpp>

Shader::Shader(const char* vertexPath, const char* fragmentPath) {
        std::string vertexCode = loadFile(vertexPath);
        std::string fragmentCode = loadFile(fragmentPath);
    
        const char* vShaderCode = vertexCode.c_str();
        const char* fShaderCode = fragmentCode.c_str();
    
        unsigned int vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vShaderCode, NULL);
        glCompileShader(vertex);
        checkCompileErrors(vertex, "VERTEX");
    
        unsigned int fragment = glCreateShader(GL_FRAGMENT_SHADER);
         glShaderSource(fragment, 1, &fShaderCode, NULL);
         glCompileShader(fragment);
         checkCompileErrors(fragment, "FRAGMENT");
    
         ID = glCreateProgram();
         glAttachShader(ID, vertex);
         glAttachShader(ID, fragment);
         glLinkProgram(ID);
         checkCompileErrors(ID, "PROGRAM");
    
        glDeleteShader(vertex);
        glDeleteShader(fragment);
}

void Shader::use() {
        glUseProgram(ID);
}

void Shader::setMat4(const std::string &name, const glm::mat4 &mat) {
        glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
}

std::string Shader::loadFile(const char* path) {
        std::ifstream file;
        std::stringstream stream;
    
        file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        try {
                file.open(path);
                stream << file.rdbuf();
                file.close();
                return stream.str();
        } catch (std::ifstream::failure& e) {
                std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what() << std::endl;
                return "";
        }
}

void Shader::checkCompileErrors(unsigned int shader, std::string type) {
        int success;
        char infoLog[1024];
    
        if (type != "PROGRAM") {
                glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
                if (!success) {
                        glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                        std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << std::endl;
                }
        } else {
                glGetProgramiv(shader, GL_LINK_STATUS, &success);
                if (!success) {
                        glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                        std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << std::endl;
                }
        }
}
