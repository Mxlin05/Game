#pragma once
#include "Sprite.h"
#include "Physics.h"
#include <map>

class Stats {
    public:
        //add stats
        int health;
        int armor;
        int magicArmor;
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

        Stats stats;

        virtual void updateHealth(int) {}
        virtual void updatePhysicalArmor(int) {}
        virtual void updateMagicArmor(int) {}
        virtual void updateBattleSpeed(int) {}
        virtual void updatePhysicalAttack(int) {}
        virtual void updateMagicAttack(int) {}
        virtual void takeDamage(int damage, std::string type) {}
        virtual void buffStat(std::vector<int>) {}
        virtual void debuffStat(std::vector<int>) {}
        virtual void heal(int) {}
        
        // Static global map for all object types
        static std::map<const AABB, std::string> enemyType; 
        //need to add more abouot physics, anminations and more



        GameObject(Sprite *sprite, glm::vec2 position, glm::vec2 size, glm::vec2 rotation);
        ~GameObject();

        virtual void draw(int windowWidth, int windowHeight) const;
        //virtual void update(float deltaTime ......... add more);
        
        virtual void setPosition(const glm::vec2& position);
        virtual void setSize(const glm::vec2& size);
        virtual void registerObjectType(const std::string& type);
        virtual std::string getObjectType() const;
        
        glm::vec2 getPosition() const;
        glm::vec2 getSize() const;



};