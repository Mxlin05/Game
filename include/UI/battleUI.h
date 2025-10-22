#pragma once
#include "UIScreen.h"
#include "Render.h"
#include "Shader.h"
#include "TextRender.h"
#include "Button.h"
#include <vector>
#include "BattleManager.h"
#include "Player.h"
#include "Enemy.h"
#include "Scene.h"

enum class BattleState {
    MAIN,
    TRAVEL, 
    ATTACK,
    MAGIC,
    ITEM
};

#include "TileMap.h"
#include "unordered_map"

class BattleUI : public UIScreen{
    int windowWidth, windowHeight;
    std::unordered_map<std::string, TileMap*> tileMaps;
    std::unordered_map<std::string, std::vector<GameObject*>> units;
    Shader *tileMapShader;
    Shader *unitShader;
    Scene *scene;
    public: 
        BattleUI(int windowWidth, int windowHeight, std::vector<Player *> players = {}, std::vector<Enemy *> enemies = {});
        ~BattleUI();

        void update(float deltaTime) override;
        void render(Render &renderer, Shader &shader, TextRenderer &textRenderer) override;
        void init() override;
        void onKeyPress(int key) override;
        void onMouseClick(double x, double y) override;

        bool isActive() const { return active; }
        void hideMenu() { active = false; }

    private:
        // Button properties

        BattleState currentState = BattleState::MAIN;
        BattleManager manager;

        float statsWidth, statsHeight, statsX, statsY, playerX, playerY, playerWidth, playerHeight;
        std::string statsText1, statsText2, statsText3, statsText4, statsText5;
        std::vector<Button> buttons;

        // Helper methods
        void createButtons();
        void createMainButtons();
        void createAttackButtons();


        void renderText(Render &renderer, Shader &shader, TextRenderer &textRenderer, float buttonX, float buttonY, std::string buttonText, float scale);
        void renderMap(Render &renderer, Shader &shader);
        void renderStats(Render &renderer, Shader &shader, TextRenderer &textRenderer, float statsX, float statsY);
        bool isPointInButton(double x, double y);
};