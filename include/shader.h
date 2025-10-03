#ifndef SHADER_H
#define SHADER_H
#include <string>
#include <glad/glad.h>
class Shader{
public:

    Shader(const char* filepath);
    
    //add other functions later as abstraction ahppens
    void use() const;

private:

    void parseShaderFile(const char* filepath, std::string& vertexCode, std::string& fragmentCode);
    unsigned int compileShader(GLenum type, const std::string& source);
}

#endif 