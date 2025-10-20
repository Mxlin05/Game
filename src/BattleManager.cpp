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
        if(currentPlayerIndex >= players.size()){
            currentPlayerIndex = 0;
        }else{
            currentPlayerIndex = currentPlayerIndex + 1;
        }

        currState = TurnState::EnemyTurn;
        return;
    }

    if(currState == TurnState::EnemyTurn){
        std::cout << "Enemy turn, go to Player turn: " << std::endl;
        if(currentEnemyIndex >= enemies.size()){
            currentEnemyIndex = 0;
        }else{
            currentEnemyIndex = currentEnemyIndex + 1;
        }
        currState = TurnState::PlayerTurn;
        return;
    }
}


//check if everyone is dead
// void BattleManager::checlBattleOver(){

// }


