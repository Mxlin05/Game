#include <iostream>     
#include <glad/glad.h>  
#include <GLFW/glfw3.h> 
#include "input.h"

void processInputs(GLFWwindow *window){

    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        printf("pressed escape\n");
    }

    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
        printf("pressed w\n");
    }

    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
        printf("pressed a\n");
    }

    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
        printf("pressed s\n");
    }

    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
        printf("pressed d\n");
    }
}