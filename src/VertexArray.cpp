#include "VertexArray.h"

/**
 * VertexArray Constructor
 * Creates a Vertex Array Object (VAO) which stores the configuration of vertex attributes
 * VAOs act as a "recipe" that tells OpenGL how to interpret vertex buffer data
 */
VertexArray::VertexArray() {
    // Generate a new Vertex Array Object and store its unique ID
    glGenVertexArrays(1, &renderID);
    
    // Bind the VAO to make it active
    // All subsequent vertex attribute configurations will be stored in this VAO
    glBindVertexArray(renderID);
}

/**
 * VertexArray Destructor
 * Cleans up GPU memory when the object is destroyed
 */
VertexArray::~VertexArray() {
    glDeleteVertexArrays(1, &renderID);
}

/**
 * Bind the Vertex Array Object for use in rendering
 * Must be called before drawing to make this VAO active
 * Only one VAO can be bound at a time
 */
void VertexArray::bind() const {
    glBindVertexArray(renderID);
}

/**
 * Unbind any Vertex Array Object
 * Useful for cleanup or when switching between different VAOs
 */
void VertexArray::unbind() const {
    glBindVertexArray(0);
}

/**
 * Configure a vertex attribute within this VAO
 * This function sets up how OpenGL should interpret vertex data for a specific attribute
 * 
 * @param vb - The vertex buffer containing the actual data
 * @param index - The attribute index (matches layout location in shader)
 * @param size - Number of components per attribute (e.g., 3 for vec3 position)
 * @param type - Data type of each component (e.g., GL_FLOAT)
 * @param normalized - Whether to normalize integer values to [0,1] or [-1,1]
 * @param stride - Byte offset between consecutive vertex attributes
 * @param pointer - Byte offset of the first component of this attribute
 */
void VertexArray::addBuffer(const VertexBuffer& vb, unsigned int index, int size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer) {
    // Bind the vertex buffer that contains the data for this attribute
    vb.bind();
    
    // This tells OpenGL how to interpret the data for attribute at 'index'
    glVertexAttribPointer(index, size, type, normalized, stride, pointer);
    
    // Without this, the attribute would be disabled and default to (0,0,0,1)
    glEnableVertexAttribArray(index);
}
