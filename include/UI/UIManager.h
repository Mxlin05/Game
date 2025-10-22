#pragma once
#include <vector>
#include "UIScreen.h"
#include "unordered_map"
#include <memory>
#include "Render.h"
#include "Shader.h"

class UIManager {

    public:
        std::unordered_map<std::string, std::unique_ptr<UIScreen>> screens;
        UIScreen *currScreen = nullptr;
        std::string currScreenName = "";

        UIManager();
        ~UIManager();

        void addScreen(const std::string &name, std::unique_ptr<UIScreen> screen);
        void setCurrScreen(const std::string &name);
        std::string getCurrScreenName() const;
        void update(float deltaTime = 0);
        void render(Render &renderer, Shader &shader, TextRenderer &textRenderer);
};