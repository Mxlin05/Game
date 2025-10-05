#pragma once //this header file is defined and read once

/*
*header file for 2D vector class and its basic functions
*/

struct Vector2D { 
    float x;
    float y;

    // Constructors
    Vector2D();
    Vector2D(float x, float y);

    // Arithmetic operators
    Vector2D operator+(const Vector2D& other);
    Vector2D operator-(const Vector2D& other);
    Vector2D operator*(float scalar);
    Vector2D operator/(float scalar);
    
    // Assignment operators
    Vector2D& operator+=(const Vector2D& other);
    Vector2D& operator-=(const Vector2D& other);
    Vector2D& operator*=(float scalar);
    Vector2D& operator/=(float scalar);
    
    // Comparison operators
    bool operator==(const Vector2D& other) const;
    bool operator!=(const Vector2D& other) const;
    
    // Vector operations
    float magnitude() const;           // Get vector length
    float magnitudeSquared() const;    // Get squared length (faster for comparisons)
    Vector2D normalize_create() const;      // creates a new normalized vector
    Vector2D& normalize_inplace();     // normalizes the vector in place
    float dot(const Vector2D& other) const;  // Dot product
    float distance(const Vector2D& other) const;  // Distance to another vector
    float distanceSquared(const Vector2D& other) const;  // Squared distance (faster)
    
    // Utility functions
    bool isZero() const;               // Check if vector is zero
    Vector2D perpendicular() const;    // Get perpendicular vector (rotated 90 degrees)
    float angle() const;               // Get angle in radians
    static Vector2D fromAngle(float angle);  // Create vector from angle
    static Vector2D lerp(const Vector2D& a, const Vector2D& b, float t);  // Linear interpolation
};