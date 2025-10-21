#include "Enemy.h"


Enemy::Enemy(Sprite *sprite, glm::vec2 position, glm::vec2 size, glm::vec2 rotation, glm::vec2 patrolStart, glm::vec2 patrolEnd, float speed, float detectionRange) 
    : GameObject(sprite, position, size, rotation), patrolStart(patrolStart), patrolEnd(patrolEnd), speed(speed), dectectionRange(detectionRange) {
    state = AIState::Idle;
    registerObjectType("enemy");
}

Enemy::~Enemy() {

}
void Enemy::updateAABB(){
    if (aabbID >= 0){
        Physics::updateAABB(aabbID, position, size);
    }
}

void Enemy::update(float deltaTime, const glm::vec2 &playerPos) {
    float distance = glm::length(playerPos - position);
    static glm::vec2 lastTarget = glm::vec2(-1, -1); 
    glm::vec2 old = position;
    
    switch (state) {
        case AIState::Idle:
            if (distance < dectectionRange) {
                state = AIState::Chase;
                if (lastTarget != playerPos) {
                    calculatePath(playerPos);
                    lastTarget = playerPos;
                }
            }
            break;

        case AIState::Patrol:
            if (lastTarget != patrolEnd) {
                calculatePath(patrolEnd);
                lastTarget = patrolEnd;
            }
            // follow path as usual
            followPath(deltaTime);
            if (distance < dectectionRange) {
                state = AIState::Chase;
            }
            break;

        case AIState::Chase:
            if (distance > dectectionRange) {
                state = AIState::Patrol;
                if (lastTarget != patrolEnd) {
                    calculatePath(patrolEnd);
                    lastTarget = patrolEnd;
                }
            } else {
                if (lastTarget != playerPos) {
                    calculatePath(playerPos);
                    lastTarget = playerPos;
                }
                followPath(deltaTime);
            }
            break;
    }

    // Collision detection
    for (size_t i = 0; i < Physics::getAABBCount(); i++) {
        if (aabbID == Physics::aabbs[i].id) {
            // Skip self
            continue;
        }
        if (Physics::aabbOverlap(Physics::getAABB_byID(aabbID), Physics::getAABB_byID(i))) {
            // std::cout << "Collision detected" << std::endl;
            position = old;
            break;
        }
    }

    updateAABB();
}

void Enemy::calculatePath(const glm::vec2& target) {
    if (!pathFinder) return;

    int tileSize = 32; 

    glm::ivec2 startTile = worldToTile(position, tileSize);
    glm::ivec2 endTile = worldToTile(target, tileSize);

    //std::cout << "Walkable start? " << pathFinder->isWalkable(startTile.x, startTile.y) << "\n";
    //std::cout << "Walkable end? " << pathFinder->isWalkable(endTile.x, endTile.y) << "\n";
    path = pathFinder->findPath(startTile, endTile);
    pathIndex = 0;
}

void Enemy::followPath(float deltaTime) {
    if (path.empty() || pathIndex >= path.size()) {
        //std::cout << "No path or end of path reached." << std::endl;
        return;
    }

    int tileSize = 32;
    glm::vec2 targetPos = tileToWorld(path[pathIndex], tileSize);
    
    glm::vec2 direction = targetPos - position;
    float dist = glm::length(direction);

    //std::cout << "Distance to waypoint: " << dist << std::endl;
    // printPath(path);
    if (dist < 1.0f) {
        pathIndex++;
        // std::cout << "Advancing to waypoint index: " << pathIndex << std::endl;
    } else {
        direction = glm::normalize(direction);
        position += direction * speed * deltaTime;
        // std::cout << "Moving to: " << position.x << ", " << position.y << std::endl;
    }
}

glm::ivec2 Enemy::worldToTile(const glm::vec2& pos, float tileSize) {
    int x = static_cast<int>(pos.x) / tileSize;
    int y = static_cast<int>(pos.y) / tileSize;
    return glm::ivec2(x, y);
}

glm::vec2 Enemy::tileToWorld(const glm::ivec2& tile, float tileSize) {
    return glm::vec2(tile.x * tileSize + tileSize / 2, tile.y * tileSize + tileSize / 2);
}

void Enemy::updateHealth(int h) {
    stats.health = h;
}

void Enemy::updatePhysicalArmor(int a){
    stats.armor = a;
}

void Enemy::updateMagicArmor(int a){
    stats.magicArmor = a;
}

void Enemy::updateBattleSpeed(int b){
    stats.battleSpeed = b;
}

void Enemy::updatePhysicalAttack(int a){
    stats.physAttack = a;
}

void Enemy::updateMagicAttack(int a){
    stats.magicAttack = a;
}

void Enemy::takeDamage(int damage, std::string type) {

    int damageTaken = 0; 
    if(type == "physical"){
        damageTaken = damage - stats.armor;
        std::cout << "phys damage: " << damageTaken << std::endl;
    }else if(type == "magic"){
        damageTaken = damage - stats.magicArmor;
        std::cout << "magic damage: " << damageTaken << std::endl;
    }else{
        std::cout << "NEITHER DAMAGE TYPE, WE FUCKED UP" << std::endl;
    }
    
    stats.health = stats.health - damageTaken;
    std::cout << "Player health: " << stats.health << std::endl;
    return;

}

void Enemy::buffStat(std::vector<int> s) {
    // TODO
}

void Enemy::debuffStat(std::vector<int> s) {
    // TODO
}

void Enemy::heal(int amount) {
    // TODO
}
