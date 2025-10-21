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


