#pragma once
#include <vector>
#include "GameObject.h"
#include "TileMap.h"
#include "Render.h"
#include "Player.h"
#include "Enemy.h"
class Scene {
    
    public:
        TileMap *tileMap;
        std::vector <Player*>players;

        std::vector<Enemy *> Enemies;
        //need to add other rhings based on what is needed per level
        std::vector<GameObject *> objects;

        Scene(std::vector<Player*> players = {}, TileMap *tileMap = nullptr, std::vector<Enemy*> enemies = {});
        ~Scene();

        void draw(Render *renderer, Shader *shader, int windowWidth, int windowHeight, int tileSize, float startX, float startY) const;
        void draw_battle(Render *renderer, Shader *shader, int windowWidth, int windowHeight, int tileSize, float startX, float startY) const;
        void addEnemy(Enemy *enemy);
        void addObjects(GameObject *object);
};