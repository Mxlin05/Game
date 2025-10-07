#pragma once

#include <glm/glm.hpp>
#include <iostream>
#include <algorithm>
#include <vector>


class AABB{
    glm::vec2 min;
    glm::vec2 max;
    public:
        AABB(glm::vec2 min, glm::vec2 max);
        ~AABB();

        bool operator==(const AABB& other) const;

        void setMin(glm::vec2 min);
        void setMax(glm::vec2 max);
        glm::vec2 getMin() const;
        glm::vec2 getMax() const;
};

class Physics{
    public:
    static std::vector<AABB> aabbs;

    static AABB createAABB(glm::vec2 position, glm::vec2 size);
    static bool aabbOverlap(AABB a, AABB b);
    static glm::vec2 aabbResolve(AABB a, AABB b);

    static void addAABB(AABB aabb);
    static void removeAABB(AABB aabb);
    static void updateAABB(AABB& aabb, glm::vec2 position, glm::vec2 size);
    static void clearAABBs();
    static size_t getAABBCount();
    static AABB getAABB(size_t index);
};

