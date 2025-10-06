#pragma once
#include "Sprite.h"
#include "Physics.h"

class GameObject{
    public:
        Sprite *sprite;
        glm::vec2 position;
        glm::vec2 size;
        glm::vec2 rotation;
        //need to add more abouot physics, anminations and more



        GameObject(Sprite *sprite, glm::vec2 position, glm::vec2 size, glm::vec2 rotation);
        ~GameObject();

        virtual void draw(int windowWidth, int windowHeight) const;
        //virtual void update(float deltaTime ......... add more);
        
        virtual void setPosition(const glm::vec2& position);
        virtual void setSize(const glm::vec2& size);
        glm::vec2 getPosition() const;
        glm::vec2 getSize() const;
        AABB getAABB() const;
        bool checkCollision(const GameObject &other) const;
};