#pragma once
#include "GameObject.h"
#include "Physics.h"

class Player : public GameObject{
    
    public:
        
        glm::vec2 velocity;
        float speed;
        Player(Sprite *sprite, glm::vec2 position, glm::vec2 size, glm::vec2 rotation);
        ~Player();

        //add stats

        //add collisions

        void draw(int windowWidth, int windowHeight) const override;
        void update(const glm::vec2 &move);
        void updateAABB();

        glm::vec2 getPosition() const;
};