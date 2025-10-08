#include "Enemy.h"

Enemy::Enemy(Sprite *sprite, glm::vec2 position, glm::vec2 size, glm::vec2 rotation, glm::vec2 patrolStart, glm::vec2 patrolEnd, float speed, float detectionRange) 
    : GameObject(sprite, position, size, rotation), patrolStart(patrolStart), patrolEnd(patrolEnd), speed(speed), dectectionRange(detectionRange) {
    state = AIState::Idle;
}

Enemy::~Enemy() {

}

void Enemy::updateAABB(){
    if (aabbID >= 0){
        Physics::updateAABB(aabbID, position, size);
    }
}

void Enemy::update(float deltaTime, const glm ::vec2 &playerPos){
    float distance = glm::length(playerPos - position);
    glm::vec2 old = position;
    std::cout << "Enemy position: (" << position.x << ", " << position.y << ")\n";
    std::cout << "case:" << static_cast<int>(state) << std::endl;

    switch (state) {
        case AIState::Idle:
            if (distance < dectectionRange)
                state = AIState::Chase;
            else
                state = AIState::Patrol;
            break;

        case AIState::Patrol: {
            if (glm::length(patrolEnd - position) < 5.0f)
                std::swap(patrolStart, patrolEnd);

            glm::vec2 dir = glm::normalize(patrolEnd - position);
            position += dir * speed;
            for (size_t i = 0; i < Physics::getAABBCount(); i++) {
                if (aabbID == Physics::aabbs[i].id) {
                    std::cout << "skipping self" << std::endl;
                    continue;   
                }
                if (Physics::aabbOverlap(Physics::getAABB_byID(aabbID), Physics::getAABB_byID(i))) {
                    std::cout << "collision detected" << std::endl;
                    position = old;
                    updateAABB();
                    break;
                }
            }

            if (distance < dectectionRange)
                state = AIState::Chase;
            break;
        }

        case AIState::Chase:
            if (distance > dectectionRange)
                state = AIState::Patrol;
            else
                position += glm::normalize(playerPos - position) * speed;
                for (size_t i = 0; i < Physics::getAABBCount(); i++){
                    if (aabbID == Physics::aabbs[i].id){
                        std::cout << "skipping self" << std::endl;
                        continue;   
                    }
                    if (Physics::aabbOverlap(Physics::getAABB_byID(aabbID), Physics::getAABB_byID(i))){
                        std::cout << "collision detected" << std::endl;
                        position = old;
                        updateAABB();
                        break;
                    }
                }
            break;

    }

    updateAABB(); 
}