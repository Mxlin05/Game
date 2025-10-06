#include "Player.h"

Player::Player(Sprite *sprite, glm::vec2 position, glm::vec2 size, glm::vec2 rotation)
    : GameObject(sprite, position, size, rotation), velocity(0.0f, 0.0f), speed(10.0f) {
}

Player::~Player() {
}

void Player::draw(int windowWidth, int windowHeight) const {
    GameObject::draw(windowWidth, windowHeight);
}

void Player::update(const glm::vec2 &move, float deltaTime){

    position += move * speed * deltaTime;
}

glm::vec2 Player::getPosition() const {
    //std::cout << "Player position: (" << position.x << ", " << position.y << ")\n";
    return position;
}