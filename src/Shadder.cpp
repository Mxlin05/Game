#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include "shader.h"

/**
 * Shader Constructor
 * Creates a complete shader program from a single file containing both vertex and fragment shaders
 * The file must contain both shaders separated by specific tags
 * 
 * @param filepath - Path to the .glsl file containing vertex and fragment shader code
 */
Shader::Shader(const char* filepath){

    // This will hold both the vertex and fragment shaders
    ID = glCreateProgram();

    //will open file with vertex and shader code
    std::ifstream file(filepath);
    if(!file.is_open()){
        std::cout << "failed to open file, might not exist: " << filepath << std::endl;
        return;
    }
    
    // Read the entire file content into a string
    std::stringstream ss;
    ss << file.rdbuf();
    std::string source = ss.str();

    // Parse the source code to separate vertex and fragment shaders
    std::string vertexSource, fragmentSource;
    parseShaderFile(source, vertexSource, fragmentSource);

    // Compile the individual shaders
    unsigned int vertexShader = compileShader(GL_VERTEX_SHADER, vertexSource.c_str());
    unsigned int fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentSource.c_str());

    // Attach the compiled shaders to the program
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    
    // Link the shaders together into a complete program
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

    // Clean up the individual shader objects (they're now part of the program)
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::use() const {
    // Activate this shader program for use in rendering
    glUseProgram(ID);
}

/**
 * Parse Shader File
 * Helper function to separate vertex and fragment shader code from a single file
 * The file format uses special tags to mark the beginning of each shader type
 * 
 * @param source - The complete source code from the shader file
 * @param vertexSource - Output parameter for vertex shader code
 * @param fragmentSource - Output parameter for fragment shader code
 */
void Shader::parseShaderFile(const std::string& source, std::string& vertexSource, std::string& fragmentSource){
    
    // Define the tags that mark the beginning of each shader type
    const std::string& vertexTag = "#shader vertex";
    const std::string& fragmentTag = "#shader fragment";
    //std::cout << "WTF" << source << std::endl;

    // Find the positions of these tags in the source code
    size_t vStart = source.find(vertexTag);
    size_t fStart = source.find(fragmentTag);

    // Check if both tags were found
    if(vStart == std::string::npos || fStart == std::string::npos){
        std::cout << "ERROR FINDING CODE FOR SHADER, COULD NOT COMPILE" << std::endl;
        return;
    }

    //split codfe into substring [parts to grab them]
    vStart += vertexTag.length();
    vertexSource = source.substr(vStart, fStart - vStart); 

    // Extract fragment shader code
    // Skip past the fragment tag and extract everything to the end of the file
    fStart += fragmentTag.length();
    fragmentSource = source.substr(fStart);
}

/**
 * Compiles individual shader source code into a shader object
 * 
 * @param type - Type of shader (GL_VERTEX_SHADER or GL_FRAGMENT_SHADER)
 * @param source - Source code for the shader
 * @return - OpenGL shader object ID
 */
unsigned int Shader::compileShader(GLenum type, const char *source){

    // Create a shader object of the specified type
    unsigned int shader = glCreateShader(type);
    
    // Set the source code for the shader
    //std::cout << "WTF" << source << std::endl;
    glShaderSource(shader, 1, &source, nullptr);
    
    // Compile the shader
    glCompileShader(shader);

    // Check for compilation errors
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
