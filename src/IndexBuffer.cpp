#include "IndexBuffer.h"
#include <glad/glad.h> 

/**
 * IndexBuffer Constructor
 * Creates an Index Buffer Object (IBO) for efficient vertex reuse in rendering
 * Index buffers allow you to reference vertices by index instead of duplicating vertex data
 * 
 * @param data - Pointer to the index array (e.g., {0, 1, 2} for a triangle)
 * @param count - Number of indices in the array
 */
IndexBuffer::IndexBuffer(const void *data, unsigned int count) 
: count(count)
{

    //ASSERT(sizeof(unsigned int) == sizeof(GLuint));

    // This creates a buffer object on the GPU for storing indices
    glGenBuffers(1, &renderID);
    
    // This tells OpenGL that this buffer contains indices (not vertex data)
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderID);
    
    // Upload the index data to GPU memory
    // count * sizeof(unsigned int) calculates total bytes needed
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);

}

IndexBuffer::~IndexBuffer() {
    // Delete the buffer object from GPU memory
    glDeleteBuffers(1, &renderID);
}

void IndexBuffer::bind() const {
    // Bind this buffer to the GL_ELEMENT_ARRAY_BUFFER target
    // This makes it the active index buffer for drawing operations
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderID);
}

void IndexBuffer::unbind() const {
    // Bind buffer ID 0 to effectively unbind any current index buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
