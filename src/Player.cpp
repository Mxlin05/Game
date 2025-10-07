#include "Player.h"
#include "Physics.h"

Player::Player(Sprite *sprite, glm::vec2 position, glm::vec2 size, glm::vec2 rotation)
    : GameObject(sprite, position, size, rotation), velocity(0.0f, 0.0f), speed(10.0f) {
}

Player::~Player() {
    if (aabbPtr){
        Physics::removeAABB(*aabbPtr);
    }
}

void Player::draw(int windowWidth, int windowHeight) const {
    GameObject::draw(windowWidth, windowHeight);
}

void Player::update(const glm::vec2 &move, float deltaTime){
    //if player aabb collides iwth any of the aabbs in the array, don't change the position
    //glm::vec2 old = position;
    //position += move * speed * deltaTime;
    //update the aabb
    //check the updated aabb for collisions
    //no collisions, move on, else resolve the collision
    updateAABB();

    for (size_t i = 0; i < Physics::getAABBCount(); i++){
        std::cout << &Physics::aabbs[i] << std::endl;
        if (aabbPtr == &Physics::aabbs[i]){
            //std::cout << "skipping self" << std::endl;
            continue;   
        }
        if (Physics::aabbOverlap(*aabbPtr, Physics::aabbs[i])){
            //updateAABB();
            ;
        }
    }
    position += move * speed * deltaTime;
    //no collisions, move on
}

void Player::updateAABB(){
    if (aabbPtr){
        Physics::updateAABB(*aabbPtr, position, size);
    }
}

glm::vec2 Player::getPosition() const {
    //std::cout << "Player position: (" << position.x << ", " << position.y << ")\n";
    return position;
}