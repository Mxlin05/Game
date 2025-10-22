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
    std::cout << "Current Player Index: " << currentPlayerIndex << std::endl;
    return players[currentPlayerIndex];
}


Enemy* BattleManager::getEnemy(){
    return enemies[currentEnemyIndex];
}

//check if everyone is dead
// void BattleManager::checlBattleOver(){

// }


void BattleManager::selectTarget(GLFWwindow *window, Player *player){

    currState = TurnState::SelectingTarget;
    int selectedEnemyIndex = 0;
    selectedTargets.clear();
    targetConfirmed = false;
    processInputs(window, player);

}

void BattleManager::processInputs(GLFWwindow *window, Player *player){
    if (currState != TurnState::SelectingTarget) return;


    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        if (selectedEnemyIndex > 0)
            selectedEnemyIndex--;
    } else if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        if (selectedEnemyIndex < enemies.size() - 1)
            selectedEnemyIndex++;
    } else if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        auto it = std::find(selectedTargets.begin(), selectedTargets.end(), selectedEnemyIndex);
        if (it == selectedTargets.end()) {
            selectedTargets.push_back(selectedEnemyIndex);
            std::cout << "Enemy " << selectedEnemyIndex << " selected.\n";
        } else {
            selectedTargets.erase(it);
            std::cout << "Enemy " << selectedEnemyIndex << " deselected.\n";
        }
    }else if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS) {
        targetConfirmed = true;
        confirmTargets(player);
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
            pendingMove.useMove(*player, static_cast<GameObject&>(*target));        
        }
    }

}