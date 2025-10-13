#pragma once
#include "Sprite.h"
#include "Physics.h"

class Stats {
    public:
        //add stats
        int health;
        int armor;
        int battleSpeed;
        int physAttack;
        int magicAttack;
};

class GameObject{
    public:
        Sprite *sprite;
        glm::vec2 position;
        glm::vec2 size;
        glm::vec2 rotation;
        size_t aabbID;
        //need to add more abouot physics, anminations and more



        GameObject(Sprite *sprite, glm::vec2 position, glm::vec2 size, glm::vec2 rotation);
        ~GameObject();

        virtual void draw(int windowWidth, int windowHeight) const;
        //virtual void update(float deltaTime ......... add more);
        
        virtual void setPosition(const glm::vec2& position);
        virtual void setSize(const glm::vec2& size);

        glm::vec2 getPosition() const;
        glm::vec2 getSize() const;
};