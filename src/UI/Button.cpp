#include "Button.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "TextAlignment.h"

Button::Button(float x, float y, int wx, int wy, float textScale, const std::string &label)
    : positionx(x), positiony(y), widthx(wx), widthy(wy), textScale(textScale), label(label)
    {

    }


void Button::render(Render &renderer, Shader &shader, TextRenderer &textRenderer, int windowWidth, int windowHeight) {
    
    // Set up projection matrix for UI rendering
    glm::mat4 projection = glm::ortho(0.0f, (float)windowWidth, 0.0f, (float)windowHeight);
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 model = glm::mat4(1.0f);
    
    // Position and scale the button
    model = glm::translate(model, glm::vec3(positionx, positiony, 0.0f));
    model = glm::translate(model, glm::vec3(widthx/2.0f, widthy/2.0f, 0.0f));
    model = glm::scale(model, glm::vec3(widthx, widthy, 1.0f));
    
    shader.use();
    shader.setUniformMat4f("uModel", glm::value_ptr(model));
    shader.setUniformMat4f("uView", glm::value_ptr(view));
    shader.setUniformMat4f("uProjection", glm::value_ptr(projection));
    
    // Button background (white)
    shader.setUniform4f("uColor", 1.0f, 1.0f, 1.0f, 1.0f);
    
    // Render button background
    renderer.Draw(renderer.vao, renderer.ib, shader);

    float lineHeight = 2.0f;
    float padding = 5.0f;
    // // Debug: Test with full text vs half text
    // std::string halfText = buttonText.substr(0, buttonText.length() / 2);
    // float fullTextWidth = GET_TEXT_WIDTH(buttonText, scale);
    // float halfTextWidth = GET_TEXT_WIDTH(halfText, scale);
    
    // std::cout << "=== DEBUG TEXT WIDTH ===" << std::endl;
    // std::cout << "Full text: '" << buttonText << "' (length=" << buttonText.length() << ") -> Width: " << fullTextWidth << std::endl;
    // std::cout << "Half text: '" << halfText << "' (length=" << halfText.length() << ") -> Width: " << halfTextWidth << std::endl;
    // std::cout << "Button: X=" << buttonX << ", W=" << buttonWidth << std::endl;
    
    // // Test both calculations manually
    // float fullTextX = buttonX + (buttonWidth - fullTextWidth) / 2.0f;
    // float halfTextX = buttonX + (buttonWidth - halfTextWidth) / 2.0f;
    
    // std::cout << "Manual calculation - Full text X: " << fullTextX << std::endl;
    // std::cout << "Manual calculation - Half text X: " << halfTextX << std::endl;
    // std::cout << "Difference: " << (fullTextX - halfTextX) << std::endl;
    // std::cout << "========================" << std::endl;
    
    auto [alignedX, alignedY] = ALIGN_MIDDLE_CENTER(positionx - 15.0f, positiony, widthx, widthy, label, textScale);
    // std::cout << "Macro result with half text: X=" << alignedX << ", Y=" << alignedY << std::endl;
    
    // Render button text
    textRenderer.RenderText(label, alignedX, alignedY, textScale, glm::vec3(0.0f, 0.0f, 0.0f), projection);
}


void Button::update(double mouseX, double mouseY, bool mousePressed) {
    hovering = isInside(mouseX, mouseY, mousePressed);
    if (hovering && mousePressed && onClick) {
        pressed = true;
        onClick(); 
    } else {
        pressed = false;
    }
}

bool Button::isInside(double mousex, double mousey, bool mousePressed) const{
    return (mousex >= positionx && mousex <= positionx + widthx &&
            mousey >= positiony && mousey <= positiony + widthy);
}