#include "GameObject.h"
#include <iostream>
#include "Physics.h"

// Initialize the static member variable
std::map<const AABB, std::string> GameObject::enemyType;
GameObject::GameObject(Sprite *sprite, glm::vec2 position, glm::vec2 size, glm::vec2 rotation) 
    : sprite(sprite), position(position), size(size), rotation(rotation) {
    Physics::addAABB(Physics::createAABB(position, size));
    aabbID = Physics::getAABBCount() - 1;
}

GameObject::~GameObject() {
}

void GameObject::draw(int windowWidth, int windowHeight) const {
    //std::cout << "Drawing GameObject at position (" << position.x << ", " << position.y << ") with size (" << size.x << ", " << size.y << ")\n";
    sprite -> draw(windowWidth, windowHeight, position, size, rotation);
}

void GameObject::draw_battle(int windowWidth, int windowHeight, bool isPlayer) const {
    sprite -> draw_battle(windowWidth, windowHeight, position, size, rotation, isPlayer);
}

void GameObject::setPosition(const glm::vec2& position) {
    this->position = position;
}

void GameObject::setSize(const glm::vec2& size) {
    this->size = size;
}

glm::vec2 GameObject::getPosition() const {
    return position;
}

glm::vec2 GameObject::getSize() const {
    return size;
}

void GameObject::registerObjectType(const std::string& type) {
    if (aabbID >= 0) {
        AABB myAABB = Physics::getAABB_byID(aabbID);
        enemyType[myAABB] = type;
    }
}

std::string GameObject::getObjectType() const {
    AABB myAABB = Physics::getAABB_byID(aabbID);
    auto it = enemyType.find(myAABB);
    if (it != enemyType.end()) {
        return it->second;
    }
    return "unknown"; // Return "unknown" if not found
}


void GameObject::takeDamage(int damage, std::string type)  {
    int damageTaken = 0; 
    if(type == "physical"){
        damageTaken = damage - stats.armor;
        std::cout << "phys damage: " << damageTaken << std::endl;
    }else if(type == "magic"){
        damageTaken = damage - stats.magicArmor;
        std::cout << "magic damage: " << damageTaken << std::endl;
    }else{
        std::cout << "NEITHER DAMAGE TYPE, WE FUCKED UP" << std::endl;
    }
    
    stats.health = stats.health - damageTaken;
    std::cout << "Player health: " << stats.health << std::endl;
    return;
}