#pragma once

#include "UImanager.h"
#include "Global.h"
#include <vector>
#include <GLFW/glfw3.h>
#include "Move.h"
#include <algorithm>
#include "GameObject.h"
#include "Enemy.h"
#include "Player.h"

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
        bool nextTurn();
        void playerAction();
        void enemyAction();
        void selectTarget(Player *player);

        bool checkEnd() const;

        Player *getPlayer();
        Enemy *getEnemy();
        std::vector<Player*> getAllPlayers();
        std::vector<Enemy*> getAllEnemies();

        void processInputs(int key, Player *player);
        void setPendingMove(Move m);
        void confirmTargets(Player *player);

        TurnState getCurrentState();

        bool targetConfirmed;


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

        Move pendingMove;
        bool hasPendingMove;

        bool checkBattleOver();

};