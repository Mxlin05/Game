#include "Sprite.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>


//need to get right includes for glm

Sprite::Sprite(Texture *texture, Shader *shader, Render *renderer) : texture(*texture), shader(*shader), renderer(*renderer) {
}

Sprite::~Sprite() {

}


//nmeed to draw
void Sprite::draw(int windowWidth, int windowHeight, glm::vec2 position, glm::vec2 size, glm::vec2 rotation) const {
    
    
    shader.use();
    glm::mat4 model = glm::mat4(1.0f);

    model = glm::translate(model, glm::vec3(position.x, position.y, 0.0f));
    model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
    model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(0, 0, 1));
    model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));
    model = glm::scale(model, glm::vec3(size.x, size.y, 1.0f));

    glGetError();
    
    glm::mat4 projection = glm::ortho(0.0f, (float)windowWidth, 0.0f, (float)windowHeight);
    glm::mat4 view = glm::mat4(1.0f);

    shader.setUniformMat4f("uModel", glm::value_ptr(model));
    //need to change where bind later
    texture.bind();
    shader.setUniform1i("uTexture", 0);
    glGetError();

    renderer.Draw(renderer.vao, renderer.ib, shader);
    glGetError();

}