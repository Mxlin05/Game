#include "TileMap.h"
#include <fstream>
#include <sstream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
TileMap::TileMap(const char *filePath) {
    loadFromFile(filePath);
    tileTextures[0] = new Texture("res/textures/grass.png");
    tileTextures[2] = new Texture("res/textures/water.png");
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

    //std::cout<<"size:" << width << "," << height << "\n";
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int tileType = map[y][x];
            //std::cout<<"tile:" << tileType << "\n";
            if (tileType == -1) continue; 

            float texX = (tileType % 2) * 0.5f; 
            float texY = (tileType / 2) * 0.5f; 

            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, glm::vec3(x * tileSize, y * tileSize, 0.0f));
            model = glm::scale(model, glm::vec3(tileSize, tileSize, 1.0f));

            shader.use();
            
            shader.setUniformMat4f("uModel", glm::value_ptr(model));
            shader.setUniform1i("uTexture", 0);

            tileTextures[tileType]->bind(0);
            renderer.Draw(renderer.vao, renderer.ib, shader);
        }
    }
}