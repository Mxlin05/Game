#pragma once
#include <glad/glad.h>
#include "VertexBuffer.h"

class VertexArray {

private:
    unsigned int renderID;

public:

    VertexArray();
    ~VertexArray();

    void bind() const;
    void unbind() const;

    void addBuffer(const VertexBuffer& vb, unsigned int index, int size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer);
};
