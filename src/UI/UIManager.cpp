#include "UIManager.h"

UIManager::UIManager(){
    
}

UIManager::~UIManager(){

}

void UIManager::addScreen(const std::string &name, std::unique_ptr<UIScreen> screen){
    screens[name] = std::move(screen);
    if(currScreen == nullptr){
        currScreen = screens[name].get();
        currScreenName = name;
    }
};

void UIManager::setCurrScreen(const std::string &name){
    currScreen = screens[name].get();
    currScreenName = name;
}

std::string UIManager::getCurrScreenName() const {
    return currScreenName;
}

void UIManager::update(float deltaTime){
    if(currScreen != nullptr){
        currScreen->update(deltaTime);
    }
}

void UIManager::render(Render &renderer, Shader &shader, TextRenderer &textRenderer){
    if(currScreen != nullptr){
        currScreen -> render(renderer, shader, textRenderer);
    }
}