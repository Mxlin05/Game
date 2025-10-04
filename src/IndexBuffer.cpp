#include "IndexBuffer.h"
#include <glad/glad.h> 


IndexBuffer::IndexBuffer(const void *data, unsigned int count) 
: count(count)
{

    //ASSERT(sizeof(unsigned int) == sizeof(GLuint));

    glGenBuffers(1, &renderID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);

}

IndexBuffer::~IndexBuffer() {
    glDeleteBuffers(1, &renderID);
}

void IndexBuffer::bind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderID);
}

void IndexBuffer::unbind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
