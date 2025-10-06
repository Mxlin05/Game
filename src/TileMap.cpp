#include "TileMap.h"
#include <fstream>
#include <sstream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
TileMap::TileMap(const char *filePath) {
    loadFromFile(filePath);
    Texture* tex = new Texture("res/textures/texture.png");
    atlas = new TextureAtlas(tex);

    //need to fix the pixels
    atlas->addRegion(2, 0, 0, 1060, 760, 1212, 1464); 
    atlas->addRegion(0, 700, 750, 350, 700, 1212, 1464); 
}
TileMap::~TileMap() {

}

void TileMap::loadFromFile(const char *filePath) {
    std::ifstream file(filePath);
    std::string line;
    map.clear();
    height = 0;
    width = 0;

    while (std::getline(file, line)) {
        std::vector<int> row;
        std::string cell;
        std::istringstream lineStream(line);
        while (std::getline(lineStream, cell, ',')) {
            row.push_back(std::stoi(cell));
        }
        if (width == 0) {
            width = row.size();
        }
        map.push_back(row);
        height++;
    }
}

void TileMap::draw(Render& renderer, Shader& shader, int windowWidth, int windowHeight) {
    int tileSize = 32;

    atlas->texture->bind(0); 

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int tileType = map[y][x];
            if (tileType == -1) continue;

            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, glm::vec3(x * tileSize, y * tileSize, 0.0f));
            model = glm::scale(model, glm::vec3(tileSize, tileSize, 1.0f));

            const texcord& sub = atlas->get(tileType);

            shader.use();
            shader.setUniformMat4f("uModel", glm::value_ptr(model));
            shader.setUniform1i("uTexture", 0);

            // Set atlas offset/scale uniforms
            glm::vec2 offset = sub.coords[0]; // bottom-left
            glm::vec2 scale = sub.coords[2] - sub.coords[0]; // top-right - bottom-left
            shader.setUniformVec2("uOffset", offset);
            shader.setUniformVec2("uScale", scale);

            renderer.Draw(renderer.vao, renderer.ib, shader);
        }
    }
}
