#include "Npc.h"

Npc::Npc(Sprite *sprite, glm::vec2 position, glm::vec2 size, glm::vec2 rotation) 
: GameObject(sprite, position, size, rotation), speed(1.0f) 
{

}

Npc::~Npc() {

}

void Npc::draw(int windowWidth, int windowHeight) const{
    sprite -> draw(windowWidth, windowHeight, position, size, rotation);
}