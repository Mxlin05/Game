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
    

    statsWidth = 150.0f;
    statsHeight = 125.0f;


    statsX = windowWidth - statsWidth - 20.0f;  // Position at right edge
    statsY = (windowHeight - statsHeight) / 12.0 - 10.0f; // Position at bottom edge


    statsText1 = "Health: " + std::to_string(g_player->stats.health);
    statsText2 = "Armor: " + std::to_string(g_player->stats.armor);
    statsText3 = "Battle Speed: " + std::to_string(g_player->stats.battleSpeed);
    statsText4 = "Physical Attack: " + std::to_string(g_player->stats.physAttack);
    statsText5 = "Magic Attack: " + std::to_string(g_player->stats.magicAttack);
    
    init();
}

BattleUI::~BattleUI() {}

void BattleUI::render(Render &renderer, Shader &shader, TextRenderer &textRenderer) {
    if (!active) return;
    
    // 1. Render red overlay (semi-transparent background for battle)
    renderOverlay(renderer, shader);
    // 2. Render button background
    for (auto &button : buttons) {
        // std::cout << button <<std::endl;
        button.render(renderer, shader, textRenderer, windowWidth, windowHeight);
    }

    renderStats(renderer, shader, textRenderer, statsX, statsY);
}

void BattleUI::createButtons(){
    float buttonWidth = 200.0f;
    float buttonHeight = 50.0f;
    float startY = windowHeight / 2.0f;

    buttons.clear();

    buttons.emplace_back(windowWidth / 2.0f - buttonWidth / 2.0f, startY + 60.0f, buttonWidth, buttonHeight, 0.5, "Attack");
    buttons.emplace_back(windowWidth / 2.0f - buttonWidth / 2.0f, startY, buttonWidth, buttonHeight, 0.5, "Defend");
    buttons.emplace_back(windowWidth / 2.0f - buttonWidth / 2.0f, startY - 60.0f, buttonWidth, buttonHeight, 0.5, "Run");


    // Assign callbacks
    buttons[0].onClick = []() { std::cout << "Attack!\n"; };
    buttons[1].onClick = []() { std::cout << "Defend!\n"; };
    buttons[2].onClick = []() { std::cout << "Run Away!\n"; };
}

void BattleUI::update(float deltaTime) {
    // No updates needed for battle screen
}

void BattleUI::init() {
    createButtons();
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

bool BattleUI::isPointInButton(double x, double y) {
    for (auto &button : buttons) {
        if (button.isInside(x, y, false) && button.onClick){
            button.onClick();
            return true;
        }
    }
    return true;
}
