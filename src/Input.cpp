#include <iostream>     
#include <glad/glad.h>  
#include <GLFW/glfw3.h> 
#include "input.h"

//will put input into something else and read into something else prob
void processInputs(GLFWwindow *window, float deltaTime, Player *player){
    
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        printf("pressed escape\n");
    }

    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
        player -> update({0.0f, -0.01f}, deltaTime);
    }

    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
        player -> update({0.01f, 0.0f}, deltaTime);
    }

    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
        player -> update({0.0f, 0.01f}, deltaTime);
    }

    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
        player -> update({-0.01f, 0.0f}, deltaTime);
    }
}