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

        void updateHealth(int h);
        void updatePhysicalArmor(int a);
        void updateMagicArmor(int a);
        void updateBattleSpeed(int b);
        void updatePhysicalAttack(int a);
        void updateMagicAttack(int a);

        void initMoves();

        glm::vec2 getPosition() const;


        void learnMove(const Move& move);
        void useMove(int index);

        void useMove();

};