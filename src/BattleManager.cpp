#include "BattleManager.h"
#include <iostream>

BattleManager::BattleManager(std::vector<Player*> players, std::vector<Enemy*> enemies) :
    players(players), enemies(enemies), currState(TurnState::StartBattle), currentEnemyIndex(0), currentPlayerIndex(0)
{

}

BattleManager::~BattleManager(){

}


//use SPEED STAT
void BattleManager::startBattle(){
    currState = TurnState::PlayerTurn;

    currentEnemyIndex = 0;
    currentPlayerIndex = 0;
    
}

//USE SPEED STATS, NEEED TO CHECK IF PLAYER IS ALIVE
void BattleManager::nextTurn(){

    //checkBattleOver();
    if(currState == TurnState::BattleOver){

        //show battle over
        return;
    }

    if (currState == TurnState::PlayerTurn)
    {
        std::cout << "Playe turn, go to enemy turn: " << std::endl;
        std::cout << "Player size : " << players.size() << std::endl;
        if(currentPlayerIndex < players.size() - 1){
            currentPlayerIndex = currentPlayerIndex + 1;
        }else{
            currentPlayerIndex = 0;
            std::cout << "This should be running, player index should be 0" << std::endl;

        }

        currState = TurnState::EnemyTurn;
        return;
    }

    if(currState == TurnState::EnemyTurn){

        //THIS WILL BE CHANGED IN THE FURTURE BUT JKUST SKIP FOR NOW
        currState = TurnState::PlayerTurn;
        return;

        std::cout << "Enemy turn, go to Player turn: " << std::endl;
        if(currentEnemyIndex < enemies.size() - 1){
            currentEnemyIndex = currentEnemyIndex + 1;
        }else{
            currentEnemyIndex = 0;
        }
        currState = TurnState::PlayerTurn;
        return;
    }
}

Player* BattleManager::getPlayer(){
    return players[currentPlayerIndex];
}


Enemy* BattleManager::getEnemy(){
    return enemies[currentEnemyIndex];
}

//check if everyone is dead
// void BattleManager::checlBattleOver(){

// }

std::vector<Player*> BattleManager::getAllPlayers(){
    return players;
}

std::vector<Enemy*> BattleManager::getAllEnemies(){
    return enemies;
}


void BattleManager::selectTarget(Player *player){

    currState = TurnState::SelectingTarget;
    int selectedEnemyIndex = 0;
    selectedTargets.clear();
    targetConfirmed = false;

}

void BattleManager::processInputs(int key, Player *player){

    std::cout << "Selecting targets, start of process inputs" << std::endl;
    if (currState != TurnState::SelectingTarget) return;

    for (auto* e : enemies)
        e->sprite->isHovered = false;

    if (key == GLFW_KEY_LEFT) {
        if (selectedEnemyIndex > 0){
            std::cout << "going down 1" << std::endl;
            selectedEnemyIndex--;
            std::cout << "Name: " << enemies[selectedEnemyIndex]->name << std::endl;
        }
        std::cout << "registered press" << std::endl;
    } else if (key == GLFW_KEY_RIGHT) {
        if (selectedEnemyIndex < enemies.size() - 1){
            std::cout << "going up one" << std::endl;
            selectedEnemyIndex++;
            std::cout << "Name: " << enemies[selectedEnemyIndex]->name << std::endl;
        }

        std::cout << "registered press" << std::endl;
    } else if (key == GLFW_KEY_SPACE) {
        std::cout << "registered spcawe press" << std::endl;
        auto it = std::find(selectedTargets.begin(), selectedTargets.end(), selectedEnemyIndex);
        if (it == selectedTargets.end()) {
            selectedTargets.push_back(selectedEnemyIndex);
            std::cout << "Enemy " << selectedEnemyIndex << " selected.\n";
            enemies[selectedEnemyIndex]->sprite->isSelected = true;
        } else {
            selectedTargets.erase(it);
            std::cout << "Enemy " << selectedEnemyIndex << " deselected.\n";
            enemies[selectedEnemyIndex]->sprite->isSelected = false;
        }
    }else if (key == GLFW_KEY_ENTER) {
        std::cout << "confirmed press" << std::endl;
        targetConfirmed = true;
        confirmTargets(player);
    }

    if (selectedEnemyIndex >= 0 && selectedEnemyIndex < enemies.size())
    {
        for (size_t i = 0; i < enemies.size(); ++i) {
            enemies[i]->sprite->isHovered = (i == selectedEnemyIndex);
        }
    }
}


void BattleManager::setPendingMove(Move m) {
    pendingMove = m;
    hasPendingMove = true;
}

void BattleManager::confirmTargets(Player *player){

    if(targetConfirmed == false || hasPendingMove == false){
        std::cout << "FUCKED UP" << std::endl;
        return;
    }

    for (int idx : selectedTargets) {
        if (idx >= 0 && idx < enemies.size()) {
            Enemy* target = enemies[idx];
            std::cout << "Using " << pendingMove.name 
                      << " on enemy "  << std::endl;
            std::cout << "Name: " << target->name << std::endl;
            pendingMove.useMove(*player, static_cast<GameObject&>(*target));        
        }
    }

}

TurnState BattleManager::getCurrentState(){
    return currState;
}