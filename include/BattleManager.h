#pragma once

#include "UIScreen.h"
#include <vector>


class Player;
class Enemy;

enum class TurnState {
    PlayerTurn,
    EnemyTurn,
    BattleOver,
    StartBattle,
};

class BattleManager {

    public:

        BattleManager(std::vector<Player*> player, std::vector<Enemy*> enemies);
        ~BattleManager();

        void startBattle();
        void nextTurn();
        void playerAction();
        void enemyAction();

        bool checkEnd() const;

        Player *getPlayer();
        Enemy *getEnemy();


        //something to deal wioth turn

        //something to deal with who is selected

    private:

        std::vector<Player *> players;
        std::vector<Enemy *> enemies;

        TurnState currState;
        size_t currentEnemyIndex;
        size_t currentPlayerIndex;
    
        void checkBattleOver();

};