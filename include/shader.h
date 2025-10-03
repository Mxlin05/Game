#ifndef SHADER_H
#define SHADER_H
#pragma once
#include <string>
#include <glad/glad.h>
class Shader{
    unsigned int ID;
public:

    Shader(const char* filepath);
    
    //add other functions later as abstraction ahppens
    void use() const;

private:

    void parseShaderFile(const std::string& source, std::string& vertexCode, std::string& fragmentCode);
    unsigned int compileShader(GLenum type, const char *source);
};

#endif 