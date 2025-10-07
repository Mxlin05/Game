#include "Player.h"
#include "Physics.h"

Player::Player(Sprite *sprite, glm::vec2 position, glm::vec2 size, glm::vec2 rotation)
    : GameObject(sprite, position, size, rotation), velocity(10.0f, 10.0f), speed(50.0f) {
}

Player::~Player() {
    Physics::removeAABB(Physics::getAABB_byID(aabbID));
}

void Player::draw(int windowWidth, int windowHeight) const {
    GameObject::draw(windowWidth, windowHeight);
}

void Player::update(const glm::vec2 &move){
    //if player aabb collides iwth any of the aabbs in the array, don't change the position
    glm::vec2 old = position;
    position += move * speed;
    //update the aabb
    //check the updated aabb for collisions
    //no collisions, move on, else resolve the collision
    updateAABB();

    std::cout << "number of items: " << Physics::getAABBCount() << std::endl;

    for (size_t i = 0; i < Physics::getAABBCount(); i++){
        if (aabbID == Physics::aabbs[i].id){
            std::cout << "skipping self" << std::endl;
            continue;   
        }
        if (Physics::aabbOverlap(Physics::getAABB_byID(aabbID), Physics::getAABB_byID(i))){
            std::cout << "collision detected" << std::endl;
            position = old;
            updateAABB();
            break;
        }
    }
    position += move * speed;
    //no collisions, move on
}

void Player::updateAABB(){
    if (aabbID >= 0){
        Physics::updateAABB(aabbID, position, size);
    }
}

glm::vec2 Player::getPosition() const {
    //std::cout << "Player position: (" << position.x << ", " << position.y << ")\n";
    return position;
}