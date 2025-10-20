#pragma once
#include "Render.h"
#include "Shader.h"
#include <string>
#include <functional>
#include "TextRender.h"
#include <ostream>


class Button {

    public:

        float positionx, positiony;
        int widthx; int widthy;
        float textScale;
        std::string label;

        bool hovering;
        bool pressed;

        std::function<void()> onClick;

        Button(float positionX, float positionY, int widthX, int widthY, float txtScale, const std::string &label);

        void render(Render &renderer, Shader &shader, TextRenderer &textRenderer, int windowWidth, int windowHeight);
        void update(double mouseX, double mouseY, bool mousePressed);
        bool isInside(double mouseX, double mouseY, bool mousePressed) const;



    private:


};

// Free function (non-member)
inline std::ostream& operator<<(std::ostream &os, const Button &button) {
    os << "Button(label=\"" << button.label 
       << "\", pos=(" << button.positionx << ", " << button.positiony 
       << "), size=(" << button.widthx << ", " << button.widthy << "))";
    return os;
}