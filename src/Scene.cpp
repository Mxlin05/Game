#include "Scene.h"

Scene::Scene(Player *player, TileMap *tileMap) : player(player), tileMap(tileMap){
    //will add as needed
}

Scene::~Scene(){
    //will add as needed
}

void Scene::draw(Render *renderer, Shader *shader, int windowWidth, int windowHeight) const {
    player->draw(windowWidth, windowHeight);
    tileMap->draw(*renderer, *shader, windowWidth, windowHeight);

    player-> draw(windowWidth, windowHeight);
    for (const auto& enemy : Enemies){
        enemy->draw(windowWidth, windowHeight);
    }
    for (const auto& object : objects){
        object->draw(windowWidth, windowHeight);
    }

    //will; add moore ass needed
}

void Scene::addEnemy(GameObject *enemy){
    //will add as needed
}

void Scene::addObjects(GameObject *object){
    objects.push_back(object);
}