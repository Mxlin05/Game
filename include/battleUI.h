#pragma once
#include "UIScreen.h"
#include "Render.h"
#include "Shader.h"
#include "TextRender.h"
#include "Button.h"
#include <vector>


enum class BattleState {
    MAIN, 
    ATTACK,
    MAGIC,
    ITEM
};

class BattleUI : public UIScreen{
    int windowWidth, windowHeight;
    public: 
        BattleUI(int windowWidth, int windowHeight);
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

        float statsWidth, statsHeight, statsX, statsY, playerX, playerY, playerWidth, playerHeight;
        std::string statsText1, statsText2, statsText3, statsText4, statsText5;
        std::vector<Button> buttons;

        // Helper methods
        void createButtons();
        void createMainButtons();
        void createAttackButtons();


        void renderText(Render &renderer, Shader &shader, TextRenderer &textRenderer, float buttonX, float buttonY, std::string buttonText, float scale);
        void renderOverlay(Render &renderer, Shader &shader);
        void renderStats(Render &renderer, Shader &shader, TextRenderer &textRenderer, float statsX, float statsY);
        void renderPlayer(Render &renderer, Shader &shader, TextRenderer &textRenderer, float playerX, float playerY, float playerWidth, float playerHeight);
        bool isPointInButton(double x, double y);
};