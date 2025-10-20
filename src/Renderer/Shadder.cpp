#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include "shader.h"



//neeed to deal with uniforms
Shader::Shader(const char* filepath){

    ID = glCreateProgram();

    //will open file with vertex and shader code
    std::ifstream file(filepath);
    if(!file.is_open()){
        std::cout << "failed to open file, might not exist: " << filepath << std::endl;
        return;
    }
    std::stringstream ss;
    ss << file.rdbuf();
    std::string source = ss.str();

    std::string vertexSource, fragmentSource;
    parseShaderFile(source, vertexSource, fragmentSource);

    unsigned int vertexShader = compileShader(GL_VERTEX_SHADER, vertexSource.c_str());
    unsigned int fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentSource.c_str());

    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    glLinkProgram(ID);

    //errorsssss
    int success;
    char infoLog[512];
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" 
                    << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::use() const {
    glUseProgram(ID);
}


//helper to read through sahdder file and get the vertex and fragment
void Shader::parseShaderFile(const std::string& source, std::string& vertexSource, std::string& fragmentSource){
    
    const std::string& vertexTag = "#shader vertex";
    const std::string& fragmentTag = "#shader fragment";
    //std::cout << "WTF" << source << std::endl;

    size_t vStart = source.find(vertexTag);
    size_t fStart = source.find(fragmentTag);

    if(vStart == std::string::npos || fStart == std::string::npos){
        std::cout << "ERROR FINDING CODE FOR SHADER, COULD NOT COMPILE" << std::endl;
        return;
    }

    //split codfe into substring [parts to grab them]
    vStart += vertexTag.length();
    vertexSource = source.substr(vStart, fStart - vStart); 

    
    fStart += fragmentTag.length();
    fragmentSource = source.substr(fStart);
}

unsigned int Shader::compileShader(GLenum type, const char *source){

    unsigned int shader = glCreateShader(type);
    //std::cout << "WTF" << source << std::endl;
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);

    //error check
    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::COMPILATION_FAILED of type "
                    << (type == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT")
                    << "\n" << infoLog << std::endl;
    }

    return shader;
}
