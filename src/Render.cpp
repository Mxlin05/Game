#include "Render.h"

/**
 * 
 * issuing the draw call to the GPU to complete rendering process
 * 
 * @param va - VertexArray containing vertex attribute configuration
 * @param Ib - IndexBuffer containing indices for indexed drawing
 * @param shader - Shader program to use for rendering
 */
void Render::Draw(const VertexArray& va, const IndexBuffer& Ib, const Shader& shader) const {
    // This tells the GPU which vertex and fragment shaders to use
    shader.use();
    // This activates the vertex attribute configuration (positions, colors, etc.)
    va.bind();
    // This tells OpenGL which vertices to draw and in what order
    Ib.bind();

    //will cghange from triangle later
    glDrawElements(GL_TRIANGLES, Ib.getCount(), GL_UNSIGNED_INT, nullptr);

}

void Render::clear() const {
    // Clear the color buffer bit
    // This fills the entire screen with the clear color (set with glClearColor)
    glClear(GL_COLOR_BUFFER_BIT);
}

Render::Render() {

}
Render::~Render() {

}
