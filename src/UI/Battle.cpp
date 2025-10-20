#include "battleUI.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>
#include "TextRender.h"
#include "Global.h"
#include "UIManager.h"
#include "Player.h"
#include "TextAlignment.h"
#include <iostream>

BattleUI::BattleUI(int windowWidth, int windowHeight) : windowWidth(windowWidth), windowHeight(windowHeight) {
    active = true;
    
    // Set button properties - center the button on screen
    buttonWidth = 100.0f;
    buttonHeight = 30.0f;

    statsWidth = 150.0f;
    statsHeight = 125.0f;

    buttonX_topl = (windowWidth - buttonWidth) / 8.0f;
    buttonY_topl = (windowHeight - buttonHeight) / 8.0f;
    buttonX_topr = (windowWidth - buttonWidth) / 3.0f;
    buttonY_topr = (windowHeight - buttonHeight) / 8.0f;
    buttonX_botl = (windowWidth - buttonWidth) / 8.0f;
    buttonY_botl = (windowHeight - buttonHeight) / 16.0f;
    buttonX_botr = (windowWidth - buttonWidth) / 3.0f;
    buttonY_botr = (windowHeight - buttonHeight) / 16.0f;

    statsX = windowWidth - statsWidth - 20.0f;  // Position at right edge
    statsY = (windowHeight - statsHeight) / 12.0 - 10.0f; // Position at bottom edge

    buttonText1 = "Move";
    buttonText2 = "Attack";
    buttonText3 = "Defend";
    buttonText4 = "Item";

    statsText1 = "Health: " + std::to_string(g_player->stats.health);
    statsText2 = "Armor: " + std::to_string(g_player->stats.armor);
    statsText3 = "Battle Speed: " + std::to_string(g_player->stats.battleSpeed);
    statsText4 = "Physical Attack: " + std::to_string(g_player->stats.physAttack);
    statsText5 = "Magic Attack: " + std::to_string(g_player->stats.magicAttack);
}

BattleUI::~BattleUI() {}

void BattleUI::render(Render &renderer, Shader &shader, TextRenderer &textRenderer) {
    if (!active) return;
    
    // 1. Render red overlay (semi-transparent background for battle)
    renderOverlay(renderer, shader);
    
    // 2. Render button background
    renderButton(renderer, shader, textRenderer, buttonX_topl, buttonY_topl, buttonText1);
    renderButton(renderer, shader, textRenderer, buttonX_topr, buttonY_topr, buttonText2);
    renderButton(renderer, shader, textRenderer, buttonX_botl, buttonY_botl, buttonText3);
    renderButton(renderer, shader, textRenderer, buttonX_botr, buttonY_botr, buttonText4);

    renderStats(renderer, shader, textRenderer, statsX, statsY);
}

void BattleUI::update(float deltaTime) {
    // No updates needed for battle screen
}

void BattleUI::init() {
    // Initialize any resources if needed
}

void BattleUI::onKeyPress(int key) {
    if (!active) return;
    
    // Check for Escape key to end battle
    if (key == GLFW_KEY_ESCAPE) {
        std::cout << "Escape pressed - ending battle" << std::endl;
        g_uiManager.setCurrScreen("StartMenu"); // Return to game
    }
}

void BattleUI::onMouseClick(double x, double y) {
    if (!active) return;
    
    // Convert GLFW coordinates (top-left origin) to OpenGL coordinates (bottom-left origin)
    double openGLY = windowHeight - y;
    bool clickedOnButton = isPointInButton(x, openGLY);
}

void BattleUI::renderOverlay(Render &renderer, Shader &shader) {
    // Set up projection matrix for UI rendering (screen space)
    glm::mat4 projection = glm::ortho(0.0f, (float)windowWidth, 0.0f, (float)windowHeight);
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 model = glm::mat4(1.0f);
    
    // Scale to full screen
    model = glm::scale(model, glm::vec3(windowWidth, windowHeight, 1.0f));
    model = glm::translate(model, glm::vec3(0.5f, 0.5f, 0.0f));
    
    shader.use();
    shader.setUniformMat4f("uModel", glm::value_ptr(model));
    shader.setUniformMat4f("uView", glm::value_ptr(view));
    shader.setUniformMat4f("uProjection", glm::value_ptr(projection));
    
    // Set overlay color (semi-transparent red for battle)
    shader.setUniform4f("uColor", 0.0f, 0.0f, 0.0f, 0.8f);
    
    // Render full-screen quad
    renderer.Draw(renderer.vao, renderer.ib, shader);
}

void BattleUI::renderButton(Render &renderer, Shader &shader, TextRenderer &textRenderer, float buttonX, float buttonY, std::string buttonText) {
    // Set up projection matrix for UI rendering
    glm::mat4 projection = glm::ortho(0.0f, (float)windowWidth, 0.0f, (float)windowHeight);
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 model = glm::mat4(1.0f);
    
    // Position and scale the button
    model = glm::translate(model, glm::vec3(buttonX, buttonY, 0.0f));
    model = glm::translate(model, glm::vec3(buttonWidth/2.0f, buttonHeight/2.0f, 0.0f));
    model = glm::scale(model, glm::vec3(buttonWidth, buttonHeight, 1.0f));
    
    shader.use();
    shader.setUniformMat4f("uModel", glm::value_ptr(model));
    shader.setUniformMat4f("uView", glm::value_ptr(view));
    shader.setUniformMat4f("uProjection", glm::value_ptr(projection));
    
    // Button background (white)
    shader.setUniform4f("uColor", 1.0f, 1.0f, 1.0f, 1.0f);
    
    // Render button background
    renderer.Draw(renderer.vao, renderer.ib, shader);

    float scale = 0.3f;
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
    
    auto [alignedX, alignedY] = ALIGN_MIDDLE_CENTER(buttonX - 15.0f, buttonY, buttonWidth, buttonHeight, buttonText, scale);
    // std::cout << "Macro result with half text: X=" << alignedX << ", Y=" << alignedY << std::endl;
    
    renderText(renderer, shader, textRenderer, alignedX, alignedY, buttonText, scale);
}

void BattleUI::renderStats(Render &renderer, Shader &shader, TextRenderer &textRenderer, float statsX, float statsY) {
    // Set up projection matrix for UI rendering
    glm::mat4 projection = glm::ortho(0.0f, (float)windowWidth, 0.0f, (float)windowHeight);
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 model = glm::mat4(1.0f);

    // Position and scale the button
    model = glm::translate(model, glm::vec3(statsX, statsY, 0.0f));
    model = glm::translate(model, glm::vec3(statsWidth/2.0f, statsHeight/2.0f, 0.0f));
    model = glm::scale(model, glm::vec3(statsWidth, statsHeight, 1.0f));

    shader.use();
    shader.setUniformMat4f("uModel", glm::value_ptr(model));
    shader.setUniformMat4f("uView", glm::value_ptr(view));
    shader.setUniformMat4f("uProjection", glm::value_ptr(projection));

    shader.setUniform4f("uColor", 1.0f, 1.0f, 1.0f, 1.0f);

    renderer.Draw(renderer.vao, renderer.ib, shader);

    // Render stats text with proper alignment within the stats frame
    float scale = 0.3f;
    float lineHeight = 20.0f;
    float padding = 20.0f;
    
    // Top-left aligned stats text with padding
    auto [text1X, text1Y] = ALIGN_TOP_LEFT(statsX + padding, statsY + padding + lineHeight * 4, statsText1, scale);
    renderText(renderer, shader, textRenderer, text1X, text1Y, statsText1, scale);
    
    auto [text2X, text2Y] = ALIGN_TOP_LEFT(statsX + padding, statsY + padding + lineHeight * 3, statsText2, scale);
    renderText(renderer, shader, textRenderer, text2X, text2Y, statsText2, scale);
    
    auto [text3X, text3Y] = ALIGN_TOP_LEFT(statsX + padding, statsY + padding + lineHeight * 2, statsText3, scale);
    renderText(renderer, shader, textRenderer, text3X, text3Y, statsText3, scale);
    
    auto [text4X, text4Y] = ALIGN_TOP_LEFT(statsX + padding, statsY + padding + lineHeight * 1, statsText4, scale);
    renderText(renderer, shader, textRenderer, text4X, text4Y, statsText4, scale);
    
    auto [text5X, text5Y] = ALIGN_TOP_LEFT(statsX + padding, statsY + padding, statsText5, scale);
    renderText(renderer, shader, textRenderer, text5X, text5Y, statsText5, scale);
}

void BattleUI::renderText(Render &renderer, Shader &shader, TextRenderer &textRenderer, float X, float Y, std::string buttonText, float scale) {
    // Set up projection matrix for text rendering (screen space)
    glm::mat4 projection = glm::ortho(0.0f, (float)windowWidth, 0.0f, (float)windowHeight);
    // Render button text
    textRenderer.RenderText(buttonText, X, Y, scale, glm::vec3(0.0f, 0.0f, 0.0f), projection);
}

bool BattleUI::isPointInButton(double x, double y) {

    if (x >= buttonX_topl && x <= buttonX_topl + buttonWidth && y >= buttonY_topl && y <= buttonY_topl + buttonHeight){
        std::cout << "Mouse clicked on Move button" << std::endl;
        return true;
    }
    if (x >= buttonX_topr && x <= buttonX_topr + buttonWidth && y >= buttonY_topr && y <= buttonY_topr + buttonHeight){
        std::cout << "Mouse clicked on Attack button" << std::endl;
        return true;
    }
    if (x >= buttonX_botl && x <= buttonX_botl + buttonWidth && y >= buttonY_botl && y <= buttonY_botl + buttonHeight){
        std::cout << "Mouse clicked on Defend button" << std::endl;
        return true;
    }
    if (x >= buttonX_botr && x <= buttonX_botr + buttonWidth && y >= buttonY_botr && y <= buttonY_botr + buttonHeight){
        std::cout << "Mouse clicked on Item button" << std::endl;
        return true;
    }
    return false;
}
