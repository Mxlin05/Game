#pragma once
#include "UIScreen.h"
#include "Render.h"
#include "Shader.h"
#include "TextRender.h"

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
        float buttonX_topl, buttonY_topl, buttonX_topr, buttonY_topr, buttonX_botl, buttonY_botl, buttonX_botr, buttonY_botr, buttonWidth, buttonHeight, statsWidth, statsHeight, statsX, statsY;
        std::string buttonText1, buttonText2, buttonText3, buttonText4;
        std::string statsText1, statsText2, statsText3, statsText4, statsText5;
        // Helper methods
        void renderOverlay(Render &renderer, Shader &shader);
        void renderButton(Render &renderer, Shader &shader, TextRenderer &textRenderer, float buttonX, float buttonY, std::string buttonText);
        void renderStats(Render &renderer, Shader &shader, TextRenderer &textRenderer, float statsX, float statsY);
        void renderText(Render &renderer, Shader &shader, TextRenderer &textRenderer, float buttonX, float buttonY, std::string buttonText, float scale);
        bool isPointInButton(double x, double y);
};