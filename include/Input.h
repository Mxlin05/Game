
#ifndef INPUT_H
#define INPUT_H
#pragma once
#include "Camera.h"
#include "Player.h"


#include <GLFW/glfw3.h>

void processInputs(GLFWwindow *window, float deltaTime, Player *player);

#endif