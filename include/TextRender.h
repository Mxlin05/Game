#pragma once

#include <map>
#include <glm/glm.hpp>
#include <string>
#include <glad/glad.h> // Include GLAD to get OpenGL headers
#include "Shader.h"
#include <ft2build.h>
#include FT_FREETYPE_H

struct Character {
    unsigned int textureID; 
    glm::ivec2 size;  
    glm::ivec2 bearing;
    unsigned int advance;    
};

class TextRenderer {
public:
    std::map<char, Character> Characters;
    unsigned int VAO, VBO;
    Shader textShader;

    TextRenderer(const Shader& shader);
    void Load(std::string font, unsigned int fontSize);
    void RenderText(std::string text, float x, float y, float scale, glm::vec3 color); //pretty sure this isn't used
    void RenderText(std::string text, float x, float y, float scale, glm::vec3 color, glm::mat4 projection);
};
