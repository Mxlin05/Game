#pragma once //this header file is defined and read once

/*
*header file for 2D vector class and its basic functions
*/

struct Vector2D { 
    float x;
    float y;

    Vector2D();
    Vector2D(float x, float y);

    Vector2D operator+(const Vector2D& other);
    Vector2D operator-(const Vector2D& other);
    Vector2D operator*(float scalar);
    Vector2D operator/(float scalar);
};