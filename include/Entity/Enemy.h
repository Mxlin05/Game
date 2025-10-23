#pragma once
#include "GameObject.h"
#include "glm/glm.hpp"
#include "Pathfind.h"
#include "Move.h"
#include "MoveCallBackMap.h"

enum class AIState {
    Idle,
    Patrol,
    Chase,
    Attack
};


class Enemy : public GameObject {

    public:
        PathFind *pathFinder = nullptr;
        AIState state;
        std::vector<glm::ivec2> path; 
        int pathIndex = 0;
        float speed;
        float dectectionRange;
        glm::vec2 patrolStart;
        glm::vec2 patrolEnd;
        
        std::string name;

        //add stats
        Stats stats;
        std::vector<Move> moves;

        Enemy(std::string name, Sprite *sprite, glm::vec2 position, glm::vec2 size, glm::vec2 rotation, glm::vec2 patrolStart, glm::vec2 patrolEnd, float speed, float detectionRange, std::vector<Move> moves = {});
        ~Enemy();

        void update(float deltaTime, const glm::vec2& playerPosition);
        void followPath(float deltaTime);
        void calculatePath(const glm::vec2 &target);
        void updateAABB();

        void updateHealth(int h) override;
        void updatePhysicalArmor(int a) override;
        void updateMagicArmor(int a) override;
        void updateBattleSpeed(int b) override;
        void updatePhysicalAttack(int a) override;
        void updateMagicAttack(int a) override;

        void initMoves();

        glm::ivec2 worldToTile(const glm::vec2& pos, float tileSize);
        glm::vec2 tileToWorld(const glm::ivec2& tile, float tileSize);

        void printPath(const std::vector<glm::ivec2>& path) {
            std::cout << "Path waypoints (" << path.size() << "):\n";
            for (const glm::ivec2& point : path) {
                std::cout << "(" << point.x << ", " << point.y << ")\n";
            }
        }


        void setPosition(const glm::vec2& position) override;
        void takeDamage(int damage, std::string type) override;
        void buffStat(std::vector<int> buffStats) override;
        void debuffStat(std::vector<int> buffStats) override;
        void heal(int heal) override;
};