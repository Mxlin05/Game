#include "Texture.h"
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <glad/glad.h>

Texture::Texture(const char* imagePath) {
    // Load image data using stb_image
    stbi_set_flip_vertically_on_load(1); // Flip the image vertically on load
    data = stbi_load(imagePath, &width, &height, &nrChannels, 0);
    if (!data) {
        std::cerr << "Failed to load texture: " << imagePath << std::endl;
        return;
    }

    // Generate and bind OpenGL texture
    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);

    // Set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Upload texture data to GPU
    GLenum format = (nrChannels == 4) ? GL_RGBA : (nrChannels == 3) ? GL_RGB : GL_RED;
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    // Free image data after uploading to GPU
    stbi_image_free(data);
}
Texture::~Texture() {
    glDeleteTextures(1, &ID);
}
void Texture::bind(unsigned int slot) const {
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, ID);
}

void Texture::unbind() const {
    glBindTexture(GL_TEXTURE_2D, 0);
}

int Texture::getWidth() const {
    return width;
}
int Texture::getHeight() const {
    return height;
}
unsigned int Texture::getID() const {
    return ID;
}

TextureAtlas::TextureAtlas(Texture *texture)
: texture(texture)
{

};

void TextureAtlas::addRegion(int name, float x, float y, float w, float h, float atlasWidth, float atlasHeight){
    float u1 = x / atlasWidth;           
    float u2 = (x + w) / atlasWidth;     

    // Flip V coordinates
    float v2 = 1.0f - (y / atlasHeight);       
    float v1 = 1.0f - ((y + h) / atlasHeight);

    texcord region;
    region.coords[0] = { u1, v1 }; 
    region.coords[1] = { u2, v1 }; 
    region.coords[2] = { u2, v2 }; 
    region.coords[3] = { u1, v2 }; 

    regions[name] = region;
}

const texcord& TextureAtlas::get(int name) const{
    auto it = regions.find(name);
    if(it != regions.end()){
        return it->second;
    } else {
        throw std::runtime_error("Region not found in texture atlas: " + name);
    }
}