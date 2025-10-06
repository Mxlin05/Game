#include "Physics.h"
#include <iostream>

AABB Physics::createAABB(glm::vec2 position, glm::vec2 size){
    return {position, position + size};
}

bool Physics::aabbOverlap(AABB a, AABB b){
    return (a.min.x < b.max.x && b.max.x < a.max.x && a.min.y < b.max.y && b.min.y < a.max.y);
}