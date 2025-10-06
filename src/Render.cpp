#include "Render.h"


void Render::Draw(const VertexArray& va, const IndexBuffer& Ib, const Shader& shader) const {
    shader.use();
    va.bind();
    Ib.bind();

    //will cghange from triangle later
    glDrawElements(GL_TRIANGLES, Ib.getCount(), GL_UNSIGNED_INT, nullptr);

}

void Render::clear() const {
    glClear(GL_COLOR_BUFFER_BIT);
}

Render::Render() 
    {
    
    float verts[] = {
        -0.5f, -0.5f, 0.0f, 0.0f,
        0.5f, -0.5f, 1.0f, 0.0f,
        0.5f,  0.5f, 1.0f, 1.0f,
        -0.5f,  0.5f, 0.0f, 1.0f
    };
    std::copy(std::begin(verts), std::end(verts), vertices);
    
    unsigned inds[] = {
        0, 1, 2,
        2, 3, 0
    };
    std::copy(std::begin(inds), std::end(inds), indices);

    vb.setData(verts, sizeof(verts));
    ib.setData(inds, 6);
    // position attribute
    vao.addBuffer(vb, 0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    vao.addBuffer(vb, 1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
}
Render::~Render() {

}
