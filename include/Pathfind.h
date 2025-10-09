#pragma once
#include <vector>
#include "glm/glm.hpp"
#include "TileMap.h"
#include <queue>
#include <unordered_map>

struct Node {
    glm::ivec2 position;
    float gCost;
    float hCost;
    float fCost() const { return gCost + hCost; }
    glm::ivec2 parent;

    Node(glm::ivec2 pos, float g, float h, glm::ivec2 par) : position(pos), gCost(g), hCost(h), parent(par) {}
    Node() : position({-1, -1}), gCost(0), hCost(0), parent({-1, -1}) {}
};

struct CompareNode {
    bool operator() (const Node& lhs, const Node& rhs) const {
        return lhs.fCost() > rhs.fCost();
    }
};

class PathFind {

    public:
        int width;
        int height;
        std::vector<int> grid;

        PathFind(int width, int height, const std::vector<int> &TileMap);

        bool isWalkable(int x, int y) const;
        std::vector<glm::ivec2> findPath(const glm::ivec2 start, const glm::ivec2 end);
};
