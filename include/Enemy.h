#pragma once
#include "GameObject.h"
#include "glm/glm.hpp"

enum class AIState {
    Idle,
    Patrol,
    Chase,
    Attack
};

class Enemy : public GameObject {

    public:
        AIState state;
        float speed;
        float dectectionRange;
        glm::vec2 patrolStart;
        glm::vec2 patrolEnd;
        

        Enemy(Sprite *sprite, glm::vec2 position, glm::vec2 size, glm::vec2 rotation, glm::vec2 patrolStart, glm::vec2 patrolEnd, float speed, float detectionRange);
        ~Enemy();

        void update(float deltaTime, const glm::vec2& playerPosition);
        void updateAABB();
};