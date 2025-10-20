#include "battleUI.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>
#include "TextRender.h"
#include "Global.h"
#include "UIManager.h"
#include "Player.h"
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
    renderButton(renderer, shader, buttonX_topl, buttonY_topl);
    renderButton(renderer, shader, buttonX_topr, buttonY_topr);
    renderButton(renderer, shader, buttonX_botl, buttonY_botl);
    renderButton(renderer, shader, buttonX_botr, buttonY_botr);

    renderText(renderer, shader, textRenderer, buttonX_topl, buttonY_topl, buttonText1, 0.3f);
    renderText(renderer, shader, textRenderer, buttonX_topr, buttonY_topr, buttonText2, 0.3f);
    renderText(renderer, shader, textRenderer, buttonX_botl, buttonY_botl, buttonText3, 0.3f);
    renderText(renderer, shader, textRenderer, buttonX_botr, buttonY_botr, buttonText4, 0.3f);

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
    
    if (isPointInButton(x, openGLY)) {
        std::cout << "Mouse clicked on end battle button" << std::endl;
        g_uiManager.setCurrScreen("StartMenu"); // Return to game
    }
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

void BattleUI::renderButton(Render &renderer, Shader &shader, float buttonX, float buttonY) {
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

    renderText(renderer, shader, textRenderer, statsX, statsY, statsText1, 0.3f);
    renderText(renderer, shader, textRenderer, statsX, statsY + 20.0f, statsText2, 0.3f);
    renderText(renderer, shader, textRenderer, statsX, statsY + 40.0f, statsText3, 0.3f);
    renderText(renderer, shader, textRenderer, statsX, statsY + 60.0f, statsText4, 0.3f);
    renderText(renderer, shader, textRenderer, statsX, statsY + 80.0f, statsText5, 0.3f);
}

void BattleUI::renderText(Render &renderer, Shader &shader, TextRenderer &textRenderer, float buttonX, float buttonY, std::string buttonText, float scale) {
    // Set up projection matrix for text rendering (screen space)
    glm::mat4 projection = glm::ortho(0.0f, (float)windowWidth, 0.0f, (float)windowHeight);
    
    // Calculate actual text width using character metrics
    float textWidth = 0.0f;
    for (char c : buttonText) {
        textWidth += 12.0f * scale; // Approximate character width
    }
    
    // Center the text horizontally within the button
    float textX = buttonX + (buttonWidth / 2.0f) - (textWidth / 2.0f);
    
    // Center the text vertically within the button
    float textY = buttonY + (buttonHeight / 2.0f);
    
    // Render button text
    textRenderer.RenderText(buttonText, textX, textY, scale, glm::vec3(0.0f, 0.0f, 0.0f), projection);
}

bool BattleUI::isPointInButton(double x, double y) {
    return (x >= buttonX_topl && x <= buttonX_topl + buttonWidth && 
            y >= buttonY_topl && y <= buttonY_topl + buttonHeight);
}
