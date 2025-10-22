#pragma once

#include "UIScreen.h"
#include <vector>
#include <GLFW/glfw3.h>
#include "Move.h"
#include <algorithm>
#include "GameObject.h"
#include "Enemy.h"

class Player;

enum class TurnState {
    PlayerTurn,
    EnemyTurn,
    BattleOver,
    StartBattle,
    SelectingTarget,
};

class BattleManager {

    public:

        BattleManager(std::vector<Player*> player, std::vector<Enemy*> enemies);
        ~BattleManager();

        void startBattle();
        void nextTurn();
        void playerAction();
        void enemyAction();
        void selectTarget(Player *player);

        bool checkEnd() const;

        Player *getPlayer();
        Enemy *getEnemy();

        void processInputs(int key, Player *player);
        void setPendingMove(Move m);
        void confirmTargets(Player *player);

        TurnState getCurrentState();



        //something to deal wioth turn

        //something to deal with who is selected

    private:

        std::vector<Player *> players;
        std::vector<Enemy *> enemies;

        TurnState currState;
        size_t currentEnemyIndex;
        size_t currentPlayerIndex;
    
        int selectedEnemyIndex = 0;
        std::vector<int> selectedTargets;
        bool targetConfirmed;

        Move pendingMove;
        bool hasPendingMove;

        void checkBattleOver();

};