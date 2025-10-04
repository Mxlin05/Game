#include "Math/Vector2D.h"
#include <iostream>

Vector2D::Vector2D(){
    x = 0.0f;
    y = 0.0f;
}

Vector2D::Vector2D(float x, float y){
    this->x = x;
    this->y = y;
}

Vector2D Vector2D::operator+(const Vector2D& other){
    return Vector2D(x + other.x, y + other.y);
}

Vector2D Vector2D::operator-(const Vector2D& other){
    return Vector2D(x - other.x, y - other.y);
}

Vector2D Vector2D::operator*(float scalar){
    return Vector2D(x * scalar, y * scalar);
}

Vector2D Vector2D::operator/(float scalar){
    return Vector2D(x / scalar, y / scalar);
}