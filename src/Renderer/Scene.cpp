#include "Scene.h"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
Scene::Scene(std::vector<Player*> players, TileMap *tileMap, std::vector<Enemy*> enemies) : players(players), tileMap(tileMap), Enemies(enemies){
    //will add as needed
}

Scene::~Scene(){
    //will add as needed
}

void Scene::draw(Render *renderer, Shader *shader, int windowWidth, int windowHeight, int tileSize, float startX, float startY) const {
    tileMap->draw(*renderer, *shader, windowWidth, windowHeight, tileSize, startX, startY);
    shader->setUniformVec2("uOffset", glm::vec2(0.0f, 0.0f));
    shader->setUniformVec2("uScale", glm::vec2(1.0f, 1.0f));
    for (const auto& player : players){
        player->draw(windowWidth, windowHeight);
    }
    for (const auto& enemy : Enemies){
        enemy->draw(windowWidth, windowHeight);
        //std::cout << "drawing enemy" << std::endl;
    }
    for (const auto& object : objects){
        object->draw(windowWidth, windowHeight);
    }

    //will; add moore ass needed
}

void Scene::draw_battle(Render *renderer, Shader *shader, int windowWidth, int windowHeight, int tileSize, float startX, float startY) const {
    // Draw the tile map first
    tileMap->draw(*renderer, *shader, windowWidth, windowHeight, tileSize, startX, startY);
    
    // Calculate the battle area (70% of screen height)
    float overlayHeight = windowHeight * 0.7f;
    float overlayY = windowHeight - overlayHeight;
    float battleAreaWidth = windowWidth;
    float battleAreaHeight = overlayHeight;
    
    // Position and draw players on the left side
    for (size_t i = 0; i < players.size(); i++) {
        if (players[i]) {
            // Position player on the left side of the battle area
            float leftX = battleAreaWidth * 0.1f; // 10% from left edge
            float centerY = overlayY + (battleAreaHeight / 2.0f);
            float yOffset = (i - (players.size() - 1) / 2.0f) * 80.0f; // Spread vertically
            glm::vec2 newPosition(leftX, centerY + yOffset);
            
            players[i]->setPosition(newPosition);
            players[i]->draw_battle(windowWidth, windowHeight, true); // true = isPlayer
        }
    }
    
    // Position and draw enemies on the right side
    for (size_t i = 0; i < Enemies.size(); i++) {
        if (Enemies[i]) {
            // Position enemy on the right side of the battle area
            float rightX = battleAreaWidth * 0.9f; // 90% from left edge (10% from right edge)
            float centerY = overlayY + (battleAreaHeight / 2.0f);
            float yOffset = (i - (Enemies.size() - 1) / 2.0f) * 80.0f; // Spread vertically
            glm::vec2 newPosition(rightX, centerY + yOffset);
            
            Enemies[i]->setPosition(newPosition);
            Enemies[i]->draw_battle(windowWidth, windowHeight, false); // false = isEnemy
        }
    }
    
    // Draw other objects as players (left side)
    for (const auto& object : objects){
        object->draw_battle(windowWidth, windowHeight, true);
    }
}

void Scene::addEnemy(Enemy *enemy){
    Enemies.push_back(enemy);
}

void Scene::addObjects(GameObject *object){
    objects.push_back(object);
}