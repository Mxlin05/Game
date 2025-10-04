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

Render::Render() {

}
Render::~Render() {

}
