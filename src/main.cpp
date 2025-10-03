// OpenGL Game - Basic Window Setup
// This program creates a simple OpenGL window using GLFW and GLAD

#include <iostream>     // For console output (cout, endl)
#include <glad/glad.h>  // OpenGL function loader (loads OpenGL functions at runtime)
#include <GLFW/glfw3.h> // Window management library (creates windows, handles input)
#include "input.h"
#include "shader.h"


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

    // ========================================
    // 6. MAIN RENDER LOOP
    // ========================================
    
    // Keep the window open until the user closes it
    while(!glfwWindowShouldClose(window))
    {
        // Swap the front and back buffers
        // This displays what we've rendered and prepares for the next frame
        glfwSwapBuffers(window);
        
        // Process all pending events (keyboard, mouse, window events)
        // This keeps the window responsive and updates internal state
        glfwPollEvents();    

        processInputs(window);
    }

    // ========================================
    // 7. CLEANUP
    // ========================================
    
    // Clean up all GLFW resources
    // This closes the window and frees all allocated memory
    glfwTerminate();
    return 0; // Exit successfully
}