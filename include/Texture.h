#pragma once

#include <glad/glad.h> // Include GLAD to get OpenGL headers
#include <stb_image.h> // Include stb_image for image loading

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