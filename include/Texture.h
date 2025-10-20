#pragma once

#include <glad/glad.h> // Include GLAD to get OpenGL headers
#include <stb_image.h> // Include stb_image for image loading
#include <glm/glm.hpp> // Include GLM for vector types

struct texcord{
    glm::vec2 coords[4];
};

class Texture {
public:
    Texture(const char* imagePath);
    ~Texture();

    void bind(unsigned int slot = 0) const; // Bind texture to a texture unit
    void unbind() const;                     // Unbind the texture
    int getWidth() const;                    // Get texture width
    int getHeight() const;                   // Get texture height
    unsigned int getID() const;              // Get OpenGL texture ID
private:
    unsigned int ID; // OpenGL texture ID
    int width, height, nrChannels; // Texture dimensions and number of color channels
    unsigned char* data; // Pointer to image data
};

class TextureAtlas {
    public:
        Texture *texture;
        std::unordered_map<int, texcord> regions;

        TextureAtlas(Texture *texture);
        ~TextureAtlas();

        void addRegion(int name, float x, float y, float w, float h, float atlasWidth, float atlasHeight);
        const texcord& get(int name) const;

    private:

};