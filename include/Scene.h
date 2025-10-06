#pragma once
#include <vector>
#include "GameObject.h"
#include "TileMap.h"
#include "Render.h"
#include "Player.h"
class Scene {
    
    public:
        TileMap *tileMap;
        Player *player;

        std::vector<GameObject *> Enemies;
        //need to add other rhings based on what is needed per level
        std::vector<GameObject *> objects;

        Scene(Player *player, TileMap *tileMap);
        ~Scene();

        void draw(Render *renderer, Shader *shader, int windowWidth, int windowHeight) const;
        void addEnemy(GameObject *enemy);
        void addObjects(GameObject *object);
};