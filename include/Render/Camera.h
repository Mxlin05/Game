#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera {
    
    public:
        glm::vec2 position;
        float size;
        int width, height;
        Camera(int width, int height)
            : position(0.0f, 0.0f), size(1.0f), width(width), height(height) {}
        ~Camera() {}

        void move(const glm::vec2& delta);
        void setPosition(const glm::vec2& pos);
        void setZoom(float newZoom);

        glm::mat4 getViewMatrix() const;
        glm::mat4 getProjectionMatrix(float screenWidth, float screenHeight) const;

        void follow(const glm::vec2& target, int windowWidth, int windowHeight); 
};