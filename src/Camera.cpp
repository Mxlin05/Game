#include "Camera.h"
#include <iostream>

void Camera::move(const glm::vec2& delta){
    this -> position += delta;
    // std::cout << "Camera position: (" 
    // << this -> position.x << ", " 
    // << this -> position.y << ")\r" << std::endl;

}

void Camera::setPosition(const glm::vec2& pos){
    this -> position = pos;
}

void Camera::setZoom(float z){
    this -> size = z;
}

glm::mat4 Camera::getViewMatrix() const {
    return glm::translate(glm::mat4(1.0f), glm::vec3(-position.x, -position.y, 0.0f));
}

glm::mat4 Camera::getProjectionMatrix(float screenWidth, float screenHeight) const {
    float halfW = screenWidth / 2.0f / this->size;
    float halfH = screenHeight / 2.0f / this->size;
    return glm::ortho(-halfW, halfW, -halfH, halfH);
}

void Camera::follow(const glm::vec2& target, int windowWidth, int windowHeight) {
    //make sure not go out of bounds
    position = target;
}

