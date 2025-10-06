#pragma once
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "shader.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"

class Render {

    public:
        unsigned int vertices[16];
        unsigned indices[6];
        VertexArray vao;
        VertexBuffer vb;
        IndexBuffer ib;
        Render();
        ~Render();

        void Draw(const VertexArray& va, const IndexBuffer& Ib, const Shader& shader) const;
        void clear() const;
    
};