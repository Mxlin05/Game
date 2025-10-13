// OpenGL Game - Basic Window Setup
// This program creates a simple OpenGL window using GLFW and GLAD

#include <iostream>     // For console output (cout, endl)
#include <glad/glad.h>  // OpenGL function loader (loads OpenGL functions at runtime)
#include <GLFW/glfw3.h> // Window management library (creates windows, handles input)
#include "input.h"
#include "shader.h"
#include "Render.h"
#include "Texture.h"
#include "Camera.h"
#include <glm/gtc/type_ptr.hpp>
#include "Scene.h"
#include "TileMap.h"
#include "Player.h"
#include "Enemy.h"
#include "PathFind.h"
#include "UIManager.h"
#include "UIScreen.h"
#include "StartMenuScreen.h"
#include <chrono>

// Declare these outside your game loop (e.g., as member variables)
auto lastTime = std::chrono::high_resolution_clock::now();

float getDeltaTime() {
    auto currentTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> elapsed = currentTime - lastTime;
    lastTime = currentTime;
    return elapsed.count(); // seconds as float
}

using namespace std; 

/**
 * Callback function for window resize events
 * This function is automatically called by GLFW when the window is resized
 * @param window - Pointer to the GLFW window that was resized
 * @param width - New width of the window in pixels
 * @param height - New height of the window in pixels
 */
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // Tell OpenGL the new size of the rendering area
    // This ensures graphics are properly scaled when window is resized
    glViewport(0, 0, width, height);
}

// Global UI manager for input callbacks
UIManager* g_uiManager = nullptr;

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        
        if (g_uiManager && g_uiManager->currScreen) {
            g_uiManager->currScreen->onMouseClick(xpos, ypos);
        }
    }
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS) {
        if (g_uiManager && g_uiManager->currScreen) {
            g_uiManager->currScreen->onKeyPress(key);
        }
    }
}


int main()
{
    // ========================================
    // 1. INITIALIZE GLFW (Window Management)
    // ========================================
    
    // Initialize the GLFW library
    // This sets up all the internal data structures GLFW needs
    if (!glfwInit())
    {
        cout << "Failed to initialize GLFW" << endl;
        return -1; // Exit with error code
    }

    // ========================================
    // 2. CONFIGURE WINDOW HINTS
    // ========================================
    
    // Set window creation hints before creating the window
    // These tell GLFW what kind of OpenGL context we want
    
    glfwWindowHint(GLFW_SAMPLES, 4);                    // Enable 4x MSAA anti-aliasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);      // Request OpenGL 3.x
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);      // Request OpenGL 3.3 specifically
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // Use core profile (no deprecated functions)

    // ========================================
    // 3. CREATE WINDOW
    // ========================================
    
    // Create the actual window
    // Parameters: width, height, title, monitor (NULL = windowed), share (NULL = no sharing)
    GLFWwindow* window;
    window = glfwCreateWindow(800, 600, "Schmeet", NULL, NULL);
    if (window == NULL)
    {
        cout << "Failed to open GLFW window" << endl;
        glfwTerminate(); // Clean up GLFW before exiting
        return -1;
    }
    
    // Make the OpenGL context of this window current
    // This tells OpenGL that all subsequent OpenGL calls apply to this window
    glfwMakeContextCurrent(window);

    // ========================================
    // 4. INITIALIZE GLAD (OpenGL Loader)
    // ========================================
    
    // GLAD loads OpenGL function pointers at runtime
    // This is necessary because OpenGL drivers are loaded dynamically
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        cout << "Failed to initialize GLAD" << endl;
        glfwTerminate();
        return -1;
    }

    // ========================================
    // 5. SET UP OPENGL VIEWPORT
    // ========================================
    
    // Tell OpenGL the size of the rendering area
    // Parameters: x, y, width, height (in pixels)
    // (0,0) is bottom-left corner in OpenGL coordinates
    glViewport(0, 0, 800, 600);
    
    // Set up callback function for window resize events
    // This ensures the viewport updates when the window is resized
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    
    // Set up UI input callbacks
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetKeyCallback(window, key_callback);

    // ========================================
    // 6. MAIN RENDER LOOP
    // ========================================
    
    // Keep the window open until the user closes it
    Shader test("res/shaders/basicTest.glsl");
    Shader uiShader("res/shaders/ui.glsl");

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    Render renderer;
    Texture texture1("res/textures/lilla_fat_cheeks.png");
    Texture texture2("res/textures/test1.png");

    Sprite sprite1(&texture1, &test, &renderer);
    Sprite sprite2(&texture2, &test, &renderer);

    Player player1(&sprite2, glm::vec2(0.0f, 0.0f), glm::vec2(100.0f, 100.0f), glm::vec2(0.0f));
    Enemy obj2(&sprite1, glm::vec2(150.0f, 300.0f), glm::vec2(100.0f, 100.0f), glm::vec2(0.0f),  glm::vec2(150.0f, 300.0f), glm::vec2(400.0f), 50.0f, 300.0f); 

    TileMap tileMap("res/tilemap.csv");
    std::vector<int> walkGrid = tileMap.GenerateWalkabilityGrid();
    tileMap.printWalkabilityGrid(walkGrid, tileMap.width, tileMap.height);
    PathFind pathFinder(tileMap.width, tileMap.height, walkGrid);
    obj2.pathFinder = &pathFinder;
    Scene scene(&player1, &tileMap);
    scene.addEnemy(&obj2);
    
    int windowWidth, windowHeight;
    glfwGetWindowSize(window, &windowWidth, &windowHeight);
    Camera camera(windowWidth, windowHeight);
    
    // Initialize UI system
    UIManager uiManager;
    uiManager.addScreen("StartMenu", std::make_unique<StartMenuScreen>(windowWidth, windowHeight));
    uiManager.setCurrScreen("StartMenu");
    
    // Set global UI manager for input callbacks
    g_uiManager = &uiManager;
    
    float lastTime = glfwGetTime();
    while(!glfwWindowShouldClose(window))
    {
        float deltaTime = getDeltaTime();
        
        // Clear the screen first
        renderer.clear();

        processInputs(window, deltaTime, &player1);

        camera.follow(player1.getPosition(), windowWidth, windowHeight);
        glm::mat4 view = camera.getViewMatrix();
        glm::mat4 projection = camera.getProjectionMatrix(windowWidth, windowHeight);

        test.use();
        // glm::mat4 view = glm::mat4(1.0f);
        // glm::mat4 projection = glm::ortho(0.0f, (float)windowWidth, (float)windowHeight, 0.0f, -1.0f, 1.0f);
        test.setUniformMat4f("uView", glm::value_ptr(view));
        test.setUniformMat4f("uProjection", glm::value_ptr(projection));
        scene.draw(&renderer, &test, windowWidth, windowHeight);

        for (auto& enemy : scene.Enemies) {
            enemy->update(deltaTime, player1.getPosition());
        }
        glGetError();
        
        // Render UI last (on top of everything)
        uiManager.render(renderer, uiShader);

        glfwSwapBuffers(window);


        // Process all pending events (keyboard, mouse, window events)
        // This keeps the window responsive and updates internal state
        glfwPollEvents(); 
        //std::cout << "Press Enter to continue..." << std::flush;
        //std::cin.get();   

    }

    // ========================================
    // 7. CLEANUP
    // ========================================
    
    // Clean up all GLFW resources
    // This closes the window and frees all allocated memory
    glfwTerminate();
    return 0; // Exit successfully
}