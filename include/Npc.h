#pragma once
#include "GameObject.h"

class Npc : public GameObject {

    public:

    //add stats when needed

    float speed;
    Npc(Sprite *sprite, glm::vec2 position, glm::vec2 size, glm::vec2 rotation);
    ~Npc();

    void draw(int windowWidth, int windowHeight) const override;
    void update(const glm::vec2 &move, float deltaTime);
    glm::vec2 getPosition() const;
    
};