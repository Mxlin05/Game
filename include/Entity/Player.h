#pragma once
#include "GameObject.h"
#include "Physics.h"
#include "Inventory.h"
#include "Move.h"
#include <vector>
#include "MoveCallBackMap.h"


class Player : public GameObject{
    
    public:
        
        //need to initalize inventory and add styff to it
        //Inventory Inventory;
        glm::vec2 velocity;
        float speed;
        Player(Sprite *sprite, glm::vec2 position, glm::vec2 size, glm::vec2 rotation);
        ~Player();


        //add stats
        Stats stats;
        std::vector<Move> Moves;
        //add collisions

        void draw(int windowWidth, int windowHeight) const override;
        void update(const glm::vec2 &move);
        void updateAABB();

        void updateHealth(int h) override;
        void updatePhysicalArmor(int a) override;
        void updateMagicArmor(int a) override;
        void updateBattleSpeed(int b) override;
        void updatePhysicalAttack(int a) override;
        void updateMagicAttack(int a) override;

        void initMoves();

        glm::vec2 getPosition() const;


        void learnMove(const Move& move);
        void useMove(int index);

        void useMove();

              
        void takeDamage(int damage, std::string type) override;
        void buffStat(std::vector<int> buffStats) override;
        void debuffStat(std::vector<int> buffStats) override;
        void heal(int heal) override;
        void setPosition(const glm::vec2& position) override;


};