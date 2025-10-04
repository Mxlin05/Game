#pragma once
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "shader.h"

class Render {

    public:
        Render();
        ~Render();

        void Draw(const VertexArray& va, const IndexBuffer& Ib, const Shader& shader) const;
        void clear() const;

};