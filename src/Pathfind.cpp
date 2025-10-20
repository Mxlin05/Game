#include "Pathfind.h"
#include <cmath>
#include <limits>
#include <iostream>
#include <string>
#include <algorithm>

constexpr int DIRS = 4;
const glm::ivec2 DIRECTIONS[DIRS] = { {1,0}, {-1,0}, {0,1}, {0,-1} };

float heuristic(glm::ivec2 a, glm::ivec2 b) {
    return std::abs(a.x - b.x) + std::abs(a.y - b.y); 
}

std::vector<glm::ivec2> PathFind::findPath(glm::ivec2 start, glm::ivec2 end) {
    std::vector<glm::ivec2> path;
    std::priority_queue<Node, std::vector<Node>, CompareNode> openSet;
    std::unordered_map<int, Node> allNodes; 

    auto nodeKey = [&](glm::ivec2 pos) { return pos.y * width + pos.x; };

    Node startNode(start, 0, heuristic(start, end), {-1, -1});
    openSet.push(startNode);
    allNodes[nodeKey(start)] = startNode;

    while(!openSet.empty()) {
        Node current = openSet.top();
        openSet.pop();

        if(current.position == end) {
            // reconstruct path
            glm::ivec2 pos = end;
            while (pos.x != -1) {
                path.push_back(pos);
                pos = allNodes[nodeKey(pos)].parent;
            }
            std::reverse(path.begin(), path.end());
            return path;
        }

        for (int i = 0; i < DIRS; i++) {
            glm::ivec2 neighborPos = current.position + DIRECTIONS[i];
            if (!isWalkable(neighborPos.x, neighborPos.y)) continue;

            float tentativeG = current.gCost + 1;

            int key = nodeKey(neighborPos);
            if (allNodes.find(key) == allNodes.end() || tentativeG < allNodes[key].gCost) {
                Node neighbor(neighborPos, tentativeG, heuristic(neighborPos, end), current.position);
                allNodes[key] = neighbor;
                openSet.push(neighbor);
            }
        }
    }

    // No path found
    return path;
}

bool PathFind::isWalkable(int x, int y) const {
    if (x < 0 || y < 0 || x >= width || y >= height) return false;
    return grid[y * width + x] == 0; 
}

PathFind::PathFind(int width, int height, const std::vector<int> &grid) : width(width), height(height), grid(grid) {

    
}
