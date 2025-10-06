#pragma once

#include <glm/glm.hpp>

struct AABB{
    glm::vec2 min;
    glm::vec2 max;
};

class Physics{
    public:
    static AABB createAABB(glm::vec2 position, glm::vec2 size);
    static bool aabbOverlap(AABB a, AABB b);
};