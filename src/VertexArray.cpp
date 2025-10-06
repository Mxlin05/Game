#include "VertexArray.h"

VertexArray::VertexArray() {
    glGenVertexArrays(1, &renderID);
    glBindVertexArray(renderID);
}

VertexArray::~VertexArray() {
    glDeleteVertexArrays(1, &renderID);
}


void VertexArray::bind() const {
    glBindVertexArray(renderID);
}

void VertexArray::unbind() const {
    glBindVertexArray(0);
}

void VertexArray::addBuffer(const VertexBuffer& vb, unsigned int index, int size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer) {
    vb.bind();
    glVertexAttribPointer(index, size, type, normalized, stride, pointer);
    glEnableVertexAttribArray(index);
}
