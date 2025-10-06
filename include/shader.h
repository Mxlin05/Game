#ifndef SHADER_H
#define SHADER_H
#pragma once
#include <string>
#include <glad/glad.h>
#include <glm/glm.hpp>
class Shader{
    unsigned int ID;
public:

    Shader(const char* filepath);
    
    //add other functions later as abstraction ahppens
    void use() const;
    
    unsigned int getID() const { return ID; }
    void setUniform1i(const std::string &name, int value) const {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
    }
    void setUniform1f(const std::string &name, float value) const {
        glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
    }
    void setUniform4f(const std::string &name, float v0, float v1, float v2, float v3) const {
        glUniform4f(glGetUniformLocation(ID, name.c_str()), v0, v1, v2, v3);
    }
    void setUniformMat4f(const std::string &name, const float* matrix) const {
        glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, matrix);
    }
    void setUniformVec2(const std::string &name, const glm::vec2 &vector) const {
        glUniform2f(glGetUniformLocation(ID, name.c_str()), vector.x, vector.y);
    }
    

private:

    void parseShaderFile(const std::string& source, std::string& vertexCode, std::string& fragmentCode);
    unsigned int compileShader(GLenum type, const char *source);
};

#endif 