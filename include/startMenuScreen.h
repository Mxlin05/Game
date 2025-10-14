#pragma once

#include "UIScreen.h"
#include "Render.h"
#include "Shader.h"
#include "TextRender.h"

class StartMenuScreen : public UIScreen{
    bool active;
    int windowWidth, windowHeight;

    public:
        StartMenuScreen(int windowWidth, int windowHeight);
        ~StartMenuScreen();

        // Override virtual methods from UIScreen
        void update(float deltaTime) override;
        void render(Render &renderer, Shader &shader, TextRenderer &textRenderer) override;
        void init() override;
        void onKeyPress(int key) override;
        void onMouseClick(double x, double y) override;

        bool isActive() const { return active; }
        void hideMenu() { active = false; }

    private:
        // Button properties
        float buttonX, buttonY, buttonWidth, buttonHeight;
        std::string buttonText;
        
        // Helper methods
        void renderOverlay(Render &renderer, Shader &shader);
        void renderButton(Render &renderer, Shader &shader);
        void renderText(Render &renderer, Shader &shader, TextRenderer &textRenderer);
        bool isPointInButton(double x, double y);
        void startGame();
};