#pragma once
#include "GameObject.h"
#include "Physics.h"
#include "Inventory.h"
class Player : public GameObject{
    
    public:
        
        //need to initalize inventory and add styff to it
        Inventory Inventory;
        glm::vec2 velocity;
        float speed;
        Player(Sprite *sprite, glm::vec2 position, glm::vec2 size, glm::vec2 rotation);
        ~Player();

        //add stats

        //add collisions

        void draw(int windowWidth, int windowHeight) const override;
        void update(const glm::vec2 &move, float deltaTime);
        void updateAABB();

        glm::vec2 getPosition() const;
};