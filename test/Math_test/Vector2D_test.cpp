#include "Math/vector2D.h"
#include <iostream>
#include <cassert>

// Simple test framework
#define TEST_ASSERT(condition, message) \
    if (!(condition)) { \
        std::cout << "❌ FAIL: " << message << std::endl; \
        return false; \
    } else { \
        std::cout << "✅ PASS: " << message << std::endl; \
    }

bool testConstructors() {
    std::cout << "\n=== Testing Constructors ===" << std::endl;
    
    // Test default constructor
    Vector2D v1;
    TEST_ASSERT(v1.x == 0.0f, "Default constructor x = 0");
    TEST_ASSERT(v1.y == 0.0f, "Default constructor y = 0");
    
    // Test parameterized constructor
    Vector2D v2(3.0f, 4.0f);
    TEST_ASSERT(v2.x == 3.0f, "Parameterized constructor x = 3");
    TEST_ASSERT(v2.y == 4.0f, "Parameterized constructor y = 4");
    
    return true;
}

bool testAddition() {
    std::cout << "\n=== Testing Addition ===" << std::endl;
    
    Vector2D v1(1.0f, 2.0f);
    Vector2D v2(3.0f, 4.0f);
    Vector2D result = v1 + v2;
    
    TEST_ASSERT(result.x == 4.0f, "Addition x: 1 + 3 = 4");
    TEST_ASSERT(result.y == 6.0f, "Addition y: 2 + 4 = 6");
    
    return true;
}

bool testSubtraction() {
    std::cout << "\n=== Testing Subtraction ===" << std::endl;
    
    Vector2D v1(5.0f, 3.0f);
    Vector2D v2(2.0f, 1.0f);
    Vector2D result = v1 - v2;
    
    TEST_ASSERT(result.x == 3.0f, "Subtraction x: 5 - 2 = 3");
    TEST_ASSERT(result.y == 2.0f, "Subtraction y: 3 - 1 = 2");
    
    return true;
}

bool testScalarMultiplication() {
    std::cout << "\n=== Testing Scalar Multiplication ===" << std::endl;
    
    Vector2D v(2.0f, 3.0f);
    Vector2D result = v * 4.0f;
    
    TEST_ASSERT(result.x == 8.0f, "Scalar multiplication x: 2 * 4 = 8");
    TEST_ASSERT(result.y == 12.0f, "Scalar multiplication y: 3 * 4 = 12");
    
    return true;
}

bool testScalarDivision() {
    std::cout << "\n=== Testing Scalar Division ===" << std::endl;
    
    Vector2D v(12.0f, 8.0f);
    Vector2D result = v / 4.0f;
    
    TEST_ASSERT(result.x == 3.0f, "Scalar division x: 12 / 4 = 3");
    TEST_ASSERT(result.y == 2.0f, "Scalar division y: 8 / 4 = 2");
    
    return true;
}

bool testChainedOperations() {
    std::cout << "\n=== Testing Chained Operations ===" << std::endl;
    
    Vector2D v1(1.0f, 2.0f);
    Vector2D v2(3.0f, 4.0f);
    Vector2D result = (v1 + v2) * 2.0f;
    
    // (1,2) + (3,4) = (4,6), then * 2 = (8,12)
    TEST_ASSERT(result.x == 8.0f, "Chained operations x: (1+3)*2 = 8");
    TEST_ASSERT(result.y == 12.0f, "Chained operations y: (2+4)*2 = 12");
    
    return true;
}

bool testAssignmentOperators() {
    std::cout << "\n=== Testing Assignment Operators ===" << std::endl;
    
    // Test +=
    Vector2D v1(1.0f, 2.0f);
    Vector2D v2(3.0f, 4.0f);
    v1 += v2;
    TEST_ASSERT(v1.x == 4.0f, "+= operator x: 1 + 3 = 4");
    TEST_ASSERT(v1.y == 6.0f, "+= operator y: 2 + 4 = 6");
    
    // Test -=
    Vector2D v3(5.0f, 3.0f);
    Vector2D v4(2.0f, 1.0f);
    v3 -= v4;
    TEST_ASSERT(v3.x == 3.0f, "-= operator x: 5 - 2 = 3");
    TEST_ASSERT(v3.y == 2.0f, "-= operator y: 3 - 1 = 2");
    
    // Test *=
    Vector2D v5(2.0f, 3.0f);
    v5 *= 4.0f;
    TEST_ASSERT(v5.x == 8.0f, "*= operator x: 2 * 4 = 8");
    TEST_ASSERT(v5.y == 12.0f, "*= operator y: 3 * 4 = 12");
    
    // Test /=
    Vector2D v6(12.0f, 8.0f);
    v6 /= 4.0f;
    TEST_ASSERT(v6.x == 3.0f, "/= operator x: 12 / 4 = 3");
    TEST_ASSERT(v6.y == 2.0f, "/= operator y: 8 / 4 = 2");
    
    return true;
}

bool testComparisonOperators() {
    std::cout << "\n=== Testing Comparison Operators ===" << std::endl;
    
    Vector2D v1(3.0f, 4.0f);
    Vector2D v2(3.0f, 4.0f);
    Vector2D v3(1.0f, 2.0f);
    
    // Test ==
    TEST_ASSERT(v1 == v2, "== operator: identical vectors");
    TEST_ASSERT(!(v1 == v3), "== operator: different vectors");
    
    // Test !=
    TEST_ASSERT(v1 != v3, "!= operator: different vectors");
    TEST_ASSERT(!(v1 != v2), "!= operator: identical vectors");
    
    return true;
}

bool testMagnitude() {
    std::cout << "\n=== Testing Magnitude Functions ===" << std::endl;
    
    Vector2D v(3.0f, 4.0f);
    float mag = v.magnitude();
    float magSquared = v.magnitudeSquared();
    
    TEST_ASSERT(abs(mag - 5.0f) < 0.001f, "Magnitude: sqrt(3² + 4²) = 5");
    TEST_ASSERT(magSquared == 25.0f, "Magnitude squared: 3² + 4² = 25");
    
    // Test zero vector
    Vector2D zero;
    TEST_ASSERT(zero.magnitude() == 0.0f, "Zero vector magnitude = 0");
    TEST_ASSERT(zero.magnitudeSquared() == 0.0f, "Zero vector magnitude squared = 0");
    
    return true;
}

bool testNormalization() {
    std::cout << "\n=== Testing Normalization ===" << std::endl;
    
    Vector2D v(3.0f, 4.0f);
    Vector2D normalized = v.normalize_create();
    
    // Check magnitude is 1
    float mag = normalized.magnitude();
    TEST_ASSERT(abs(mag - 1.0f) < 0.001f, "Normalized vector magnitude = 1");
    
    // Check direction is preserved (3,4) -> (0.6, 0.8)
    TEST_ASSERT(abs(normalized.x - 0.6f) < 0.001f, "Normalized x: 3/5 = 0.6");
    TEST_ASSERT(abs(normalized.y - 0.8f) < 0.001f, "Normalized y: 4/5 = 0.8");
    
    // Test in-place normalization
    Vector2D v2(6.0f, 8.0f);
    v2.normalize_inplace();
    TEST_ASSERT(abs(v2.magnitude() - 1.0f) < 0.001f, "In-place normalization magnitude = 1");
    
    // Test zero vector normalization
    Vector2D zero;
    Vector2D zeroNorm = zero.normalize_create();
    TEST_ASSERT(zeroNorm.x == 0.0f && zeroNorm.y == 0.0f, "Zero vector normalization returns zero");
    
    return true;
}

bool testDotProduct() {
    std::cout << "\n=== Testing Dot Product ===" << std::endl;
    
    Vector2D v1(1.0f, 2.0f);
    Vector2D v2(3.0f, 4.0f);
    float dot = v1.dot(v2);
    
    // 1*3 + 2*4 = 3 + 8 = 11
    TEST_ASSERT(dot == 11.0f, "Dot product: 1*3 + 2*4 = 11");
    
    // Test perpendicular vectors (dot product should be 0)
    Vector2D v3(1.0f, 0.0f);
    Vector2D v4(0.0f, 1.0f);
    float dotPerp = v3.dot(v4);
    TEST_ASSERT(dotPerp == 0.0f, "Perpendicular vectors dot product = 0");
    
    return true;
}

bool testDistance() {
    std::cout << "\n=== Testing Distance Functions ===" << std::endl;
    
    Vector2D v1(0.0f, 0.0f);
    Vector2D v2(3.0f, 4.0f);
    
    float dist = v1.distance(v2);
    float distSquared = v1.distanceSquared(v2);
    
    TEST_ASSERT(abs(dist - 5.0f) < 0.001f, "Distance: sqrt(3² + 4²) = 5");
    TEST_ASSERT(distSquared == 25.0f, "Distance squared: 3² + 4² = 25");
    
    // Test same point
    float sameDist = v1.distance(v1);
    TEST_ASSERT(sameDist == 0.0f, "Distance to self = 0");
    
    return true;
}

bool testIsZero() {
    std::cout << "\n=== Testing isZero Function ===" << std::endl;
    
    Vector2D zero;
    Vector2D nonZero(1.0f, 0.0f);
    Vector2D nonZero2(0.0f, 1.0f);
    Vector2D nonZero3(0.1f, 0.1f);
    
    TEST_ASSERT(zero.isZero(), "Zero vector isZero() = true");
    TEST_ASSERT(!nonZero.isZero(), "Non-zero vector (1,0) isZero() = false");
    TEST_ASSERT(!nonZero2.isZero(), "Non-zero vector (0,1) isZero() = false");
    TEST_ASSERT(!nonZero3.isZero(), "Non-zero vector (0.1,0.1) isZero() = false");
    
    return true;
}

bool testPerpendicular() {
    std::cout << "\n=== Testing Perpendicular Function ===" << std::endl;
    
    Vector2D v(3.0f, 4.0f);
    Vector2D perp = v.perpendicular();
    
    // Perpendicular to (3,4) is (-4,3)
    TEST_ASSERT(perp.x == -4.0f, "Perpendicular x: -4");
    TEST_ASSERT(perp.y == 3.0f, "Perpendicular y: 3");
    
    // Test that perpendicular vectors have dot product = 0
    float dot = v.dot(perp);
    TEST_ASSERT(abs(dot) < 0.001f, "Vector and its perpendicular have dot product = 0");
    
    return true;
}

bool testAngle() {
    std::cout << "\n=== Testing Angle Function ===" << std::endl;
    
    Vector2D v1(1.0f, 0.0f);  // 0 radians
    Vector2D v2(0.0f, 1.0f);  // π/2 radians
    Vector2D v3(-1.0f, 0.0f); // π radians
    Vector2D v4(0.0f, -1.0f); // -π/2 radians
    
    float angle1 = v1.angle();
    float angle2 = v2.angle();
    float angle3 = v3.angle();
    float angle4 = v4.angle();
    
    TEST_ASSERT(abs(angle1) < 0.001f, "Angle of (1,0) = 0 radians");
    TEST_ASSERT(abs(angle2 - 1.5708f) < 0.001f, "Angle of (0,1) = π/2 radians");
    TEST_ASSERT(abs(angle3 - 3.14159f) < 0.001f, "Angle of (-1,0) = π radians");
    TEST_ASSERT(abs(angle4 + 1.5708f) < 0.001f, "Angle of (0,-1) = -π/2 radians");
    
    return true;
}

bool testFromAngle() {
    std::cout << "\n=== Testing fromAngle Function ===" << std::endl;
    
    Vector2D v1 = Vector2D::fromAngle(0.0f);      // 0 radians
    Vector2D v2 = Vector2D::fromAngle(1.5708f);   // π/2 radians
    Vector2D v3 = Vector2D::fromAngle(3.14159f);  // π radians
    
    TEST_ASSERT(abs(v1.x - 1.0f) < 0.001f, "fromAngle(0) x = 1");
    TEST_ASSERT(abs(v1.y) < 0.001f, "fromAngle(0) y = 0");
    
    TEST_ASSERT(abs(v2.x) < 0.001f, "fromAngle(π/2) x = 0");
    TEST_ASSERT(abs(v2.y - 1.0f) < 0.001f, "fromAngle(π/2) y = 1");
    
    TEST_ASSERT(abs(v3.x + 1.0f) < 0.001f, "fromAngle(π) x = -1");
    TEST_ASSERT(abs(v3.y) < 0.001f, "fromAngle(π) y = 0");
    
    return true;
}

bool testLerp() {
    std::cout << "\n=== Testing lerp Function ===" << std::endl;
    
    Vector2D a(0.0f, 0.0f);
    Vector2D b(10.0f, 20.0f);
    
    // Test t = 0 (should return a)
    Vector2D result0 = Vector2D::lerp(a, b, 0.0f);
    TEST_ASSERT(result0.x == 0.0f, "lerp t=0 x = 0");
    TEST_ASSERT(result0.y == 0.0f, "lerp t=0 y = 0");
    
    // Test t = 1 (should return b)
    Vector2D result1 = Vector2D::lerp(a, b, 1.0f);
    TEST_ASSERT(result1.x == 10.0f, "lerp t=1 x = 10");
    TEST_ASSERT(result1.y == 20.0f, "lerp t=1 y = 20");
    
    // Test t = 0.5 (should return midpoint)
    Vector2D result05 = Vector2D::lerp(a, b, 0.5f);
    TEST_ASSERT(result05.x == 5.0f, "lerp t=0.5 x = 5");
    TEST_ASSERT(result05.y == 10.0f, "lerp t=0.5 y = 10");
    
    return true;
}

bool testDivisionByZero() {
    std::cout << "\n=== Testing Division by Zero ===" << std::endl;
    
    Vector2D v(5.0f, 10.0f);
    
    // Test operator/
    Vector2D result1 = v / 0.0f;
    TEST_ASSERT(result1.x == 0.0f, "Division by zero operator/ x = 0");
    TEST_ASSERT(result1.y == 0.0f, "Division by zero operator/ y = 0");
    
    // Test operator/=
    Vector2D v2(5.0f, 10.0f);
    v2 /= 0.0f;
    TEST_ASSERT(v2.x == 0.0f, "Division by zero operator/= x = 0");
    TEST_ASSERT(v2.y == 0.0f, "Division by zero operator/= y = 0");
    
    return true;
}

bool testRealWorldExample() {
    std::cout << "\n=== Testing Real-World Example ===" << std::endl;
    
    // Simulate moving a sprite
    Vector2D spritePos(100.0f, 200.0f);
    Vector2D movement(5.0f, -10.0f);
    float speed = 2.0f;
    
    Vector2D newPos = spritePos + (movement * speed);
    
    // 100 + (5 * 2) = 110, 200 + (-10 * 2) = 180
    TEST_ASSERT(newPos.x == 110.0f, "Sprite movement x: 100 + (5*2) = 110");
    TEST_ASSERT(newPos.y == 180.0f, "Sprite movement y: 200 + (-10*2) = 180");
    
    return true;
}

int main() {
    std::cout << "🧮 Vector2D Math Library Test Suite" << std::endl;
    std::cout << "====================================" << std::endl;
    
    bool allTestsPassed = true;
    
    // Basic operations
    allTestsPassed &= testConstructors();
    allTestsPassed &= testAddition();
    allTestsPassed &= testSubtraction();
    allTestsPassed &= testScalarMultiplication();
    allTestsPassed &= testScalarDivision();
    allTestsPassed &= testChainedOperations();
    
    // Assignment operators
    allTestsPassed &= testAssignmentOperators();
    
    // Comparison operators
    allTestsPassed &= testComparisonOperators();
    
    // Vector operations
    allTestsPassed &= testMagnitude();
    allTestsPassed &= testNormalization();
    allTestsPassed &= testDotProduct();
    allTestsPassed &= testDistance();
    
    // Utility functions
    allTestsPassed &= testIsZero();
    allTestsPassed &= testPerpendicular();
    allTestsPassed &= testAngle();
    
    // Static functions
    allTestsPassed &= testFromAngle();
    allTestsPassed &= testLerp();
    
    // Edge cases
    allTestsPassed &= testDivisionByZero();
    
    // Real-world example
    allTestsPassed &= testRealWorldExample();
    
    std::cout << "\n====================================" << std::endl;
    if (allTestsPassed) {
        std::cout << "🎉 ALL TESTS PASSED! Your Vector2D is working correctly!" << std::endl;
    } else {
        std::cout << "❌ Some tests failed. Check the implementation." << std::endl;
    }
    
    return allTestsPassed ? 0 : 1;
}