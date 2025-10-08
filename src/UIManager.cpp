#include "UIManager.h"

UIManager::UIManager(){

}

UIManager::~UIManager(){

}

void UIManager::addScreen(const std::string &name, std::unique_ptr<UIScreen> screen){
    screens[name] = std::move(screen);
    if(currScreen == nullptr){
        currScreen = screens[name].get();
    }
};

void UIManager::setCurrScreen(const std::string &name){
    currScreen = screens[name].get();
}

void UIManager::update(float deltaTime = 0){
    if(currScreen != nullptr){
        currScreen->update(deltaTime);
    }
}

void UIManager::render(Render &renderer, Shader &shader){
    if(currScreen != nullptr){
        currScreen -> render(renderer, shader);
    }
}