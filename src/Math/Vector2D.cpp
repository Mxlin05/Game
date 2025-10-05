#include "Math/vector2D.h"
#include <iostream>
#include <cmath>

// Constructors
Vector2D::Vector2D(){
    x = 0.0f;
    y = 0.0f;
}

Vector2D::Vector2D(float x, float y){
    this->x = x;
    this->y = y;
}

// Arithmetic operators
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
    if (scalar == 0.0f) {
        return Vector2D(0.0f, 0.0f);
    }
    return Vector2D(x / scalar, y / scalar);
}

// Assignment operators
Vector2D& Vector2D::operator+=(const Vector2D& other){
    x = x + other.x;
    y = y + other.y;
    return *this; 
}

Vector2D& Vector2D::operator-=(const Vector2D& other){
    x = x - other.x;
    y = y - other.y;
    return *this;
}

Vector2D& Vector2D::operator*=(float scalar){
    x = x * scalar;
    y = y * scalar;
    return *this;
}

Vector2D& Vector2D::operator/=(float scalar){
    if (scalar == 0.0f) {
        x = 0.0f;
        y = 0.0f;
    } else {
        x = x / scalar;
        y = y / scalar;
    }
    return *this;
}

// Comparison operators
bool Vector2D::operator==(const Vector2D& other) const{
    return x == other.x && y == other.y;
}

bool Vector2D::operator!=(const Vector2D& other) const{
    return x != other.x || y != other.y;
}

// Vector operations
float Vector2D::magnitude() const{
    return sqrt(x*x + y*y);
}

float Vector2D::magnitudeSquared() const{
    return x*x + y*y;
}

Vector2D Vector2D::normalize_create() const{
    float mag = magnitude();
    if (mag != 0.0f) {
        return Vector2D(x / mag, y / mag);
    }
    return Vector2D(0.0f, 0.0f);
}

Vector2D& Vector2D::normalize_inplace(){
    float mag = magnitude();
    if (mag != 0.0f) {
        x /= mag;
        y /= mag;
    }
    return *this;
}

float Vector2D::dot(const Vector2D& other) const{
    return x * other.x + y * other.y;
}

float Vector2D::distance(const Vector2D& other) const{
    float dx = x - other.x;
    float dy = y - other.y;
    return sqrt(dx*dx + dy*dy);
}

float Vector2D::distanceSquared(const Vector2D& other) const{
    float dx = x - other.x;
    float dy = y - other.y;
    return dx*dx + dy*dy;
}

bool Vector2D::isZero() const{
    return x == 0.0f && y == 0.0f;
}

Vector2D Vector2D::perpendicular() const{
    return Vector2D(-y, x);
}

float Vector2D::angle() const{
    return atan2(y, x);
}

Vector2D Vector2D::fromAngle(float angle){
    return Vector2D(cos(angle), sin(angle));
}

Vector2D Vector2D::lerp(const Vector2D& a, const Vector2D& b, float t){
    return Vector2D((1-t)*a.x + t*b.x, (1-t)*a.y + t*b.y);
}
