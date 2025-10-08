#pragma once
#include "Render.h"
#include "Shader.h"

class UIScreen{
    public:
        virtual void update(float deltaTime = 0);
        virtual void render(Render &renderer, Shader &shader);
        virtual ~UIScreen();
        virtual void init();
        virtual void onKeyPress(int key);
        virtual void onMouseClick(double x, double y);
};