#pragma once
#include <vector>
#include "Texture.h"
#include "Render.h"
#include "shader.h"
#include <unordered_map>

class TileMap{
    public:
        TextureAtlas *atlas;
        TileMap(const char *filePath);
        ~TileMap();

        void draw(Render& renderer, Shader& shader, int windowWidth, int windowHeight);

    private:
        std::vector<std::vector<int>> map;
        int width, height;
        void loadFromFile(const char *filePath);

};