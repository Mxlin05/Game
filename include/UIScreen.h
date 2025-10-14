#pragma once
#include "Render.h"
#include "Shader.h"
#include "TextRender.h"

class UIScreen{
    public:

        UIScreen();

        virtual void update(float deltaTime = 0);
        virtual void render(Render &renderer, Shader &shader, TextRenderer &textRenderer);
        virtual ~UIScreen();
        virtual void init();
        virtual void onKeyPress(int key);
        virtual void onMouseClick(double x, double y);
};