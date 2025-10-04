#include "VertexBuffer.h"
#include <glad/glad.h> 

/**
 * VertexBuffer Constructor
 * Creates and uploads vertex data to GPU memory for efficient rendering
 * 
 * @param data - Pointer to the raw vertex data (positions, colors, texture coordinates, etc.)
 * @param size - Size of the data in bytes (e.g., sizeof(vertices) for an array)
 */
VertexBuffer::VertexBuffer(const void *data, unsigned int size) { //gives gpu position and colors

    // Generate a new OpenGL buffer object and store its unique ID
    // This creates a buffer object on the GPU but doesn't allocate memory yet
    glGenBuffers(1, &renderID);
    
    // Bind this buffer to the GL_ARRAY_BUFFER target
    // This tells OpenGL that all subsequent buffer operations apply to this buffer
    glBindBuffer(GL_ARRAY_BUFFER, renderID);
    
    // Upload the vertex data to GPU memory
    // GL_STATIC_DRAW indicates the data won't change often (good for performance)
    // Other options: GL_DYNAMIC_DRAW (changes frequently), GL_STREAM_DRAW (changes every frame)
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);

}

/**
 * VertexBuffer Destructor
 * Cleans up GPU memory when the object is destroyed to prevent memory leaks
 */
VertexBuffer::~VertexBuffer() {
    glDeleteBuffers(1, &renderID); 
}

/**
 * Bind the vertex buffer for use in rendering
 * Must be called before drawing to make this buffer active
 * Only one buffer can be bound to GL_ARRAY_BUFFER at a time
 */
void VertexBuffer::bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, renderID);
}

/**
 * Unbind any vertex buffer
 * Useful for cleanup or when switching between different buffers
 * Binding buffer ID 0 effectively unbinds any current buffer
 */
void VertexBuffer::unbind() const {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
