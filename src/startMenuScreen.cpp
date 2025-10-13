#include "StartMenuScreen.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>
#include <iostream>

StartMenuScreen::StartMenuScreen(int windowWidth, int windowHeight) : windowWidth(windowWidth), windowHeight(windowHeight) {
    active = true;
    
    // Set button properties - center the button on screen
    buttonWidth = 200.0f;
    buttonHeight = 60.0f;
    buttonX = (windowWidth - buttonWidth) / 2.0f;
    buttonY = (windowHeight - buttonHeight) / 2.0f;
    buttonText = "Play Game";
}

StartMenuScreen::~StartMenuScreen() {}

void StartMenuScreen::render(Render &renderer, Shader &shader) {
    // std::cout << "Render is called" << std::endl;
    if (!active) return;
    
    // 1. Render black overlay (semi-transparent background)
    renderOverlay(renderer, shader);
    
    // 2. Render button background
    renderButton(renderer, shader);
}

void StartMenuScreen::update(float deltaTime) {
    // No updates needed for start menu
}

void StartMenuScreen::init() {
    // Initialize any resources if needed
}

void StartMenuScreen::onKeyPress(int key) {
    if (!active) return;
    
    // Check for Enter key (GLFW_KEY_ENTER) or Space key
    if (key == GLFW_KEY_ENTER || key == GLFW_KEY_SPACE) {
        std::cout << "Enter or Space pressed" << std::endl;
        startGame();
    }
}

void StartMenuScreen::onMouseClick(double x, double y) {
    if (!active) return;
    
    // Convert GLFW coordinates (top-left origin) to OpenGL coordinates (bottom-left origin)
    double openGLY = windowHeight - y;
    
    if (isPointInButton(x, openGLY)) {
        std::cout << "Mouse clicked on button" << std::endl;
        startGame();
    }
}

void StartMenuScreen::renderOverlay(Render &renderer, Shader &shader) {
    // Set up projection matrix for UI rendering (screen space)

    // std::cout << "Render overlay is called" << std::endl;
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
    
    // Set overlay color (semi-transparent white)
    shader.setUniform4f("uColor", 1.0f, 1.0f, 1.0f, 0.8f);
    
    // Render full-screen quad
    renderer.Draw(renderer.vao, renderer.ib, shader);
}

void StartMenuScreen::renderButton(Render &renderer, Shader &shader) {
    // Set up projection matrix for UI rendering
    // std::cout << "Render button is called" << std::endl;
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
    
    // Button background (red)
    shader.setUniform4f("uColor", 1.0f, 0.0f, 0.0f, 1.0f);
    
    // Render button background
    renderer.Draw(renderer.vao, renderer.ib, shader);
}

// Text rendering removed - just showing button without text for now

bool StartMenuScreen::isPointInButton(double x, double y) {
    return (x >= buttonX && x <= buttonX + buttonWidth && 
            y >= buttonY && y <= buttonY + buttonHeight);
}

void StartMenuScreen::startGame() {
    std::cout << "Starting game!" << std::endl;
    active = false;
}
