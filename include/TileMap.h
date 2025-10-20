#pragma once
#include <vector>
#include "Texture.h"
#include "Render.h"
#include "shader.h"
#include <unordered_map>
#include <iostream>

class TileMap{
    public:
        TextureAtlas *atlas;
        TileMap(const char *filePath);
        ~TileMap();

        int width, height;
        std::vector<std::vector<int>> map;

        void draw(Render& renderer, Shader& shader, int windowWidth, int windowHeight, int tileSize, int startX = 0, int startY = 0);
        std::vector<int> GenerateWalkabilityGrid();

        void printWalkabilityGrid(const std::vector<int>& grid, int width, int height) {
            for (int y = 0; y < height; ++y) {
                for (int x = 0; x < width; ++x) {
                    std::cout << grid[y * width + x];
                    if (x < width - 1) std::cout << ", ";
                }
                std::cout << "\n";
            }
        }

    private:
        
        
        void loadFromFile(const char *filePath);

};