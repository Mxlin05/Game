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
    
    allTestsPassed &= testConstructors();
    allTestsPassed &= testAddition();
    allTestsPassed &= testSubtraction();
    allTestsPassed &= testScalarMultiplication();
    allTestsPassed &= testScalarDivision();
    allTestsPassed &= testChainedOperations();
    allTestsPassed &= testRealWorldExample();
    
    std::cout << "\n====================================" << std::endl;
    if (allTestsPassed) {
        std::cout << "🎉 ALL TESTS PASSED! Your Vector2D is working correctly!" << std::endl;
    } else {
        std::cout << "❌ Some tests failed. Check the implementation." << std::endl;
    }
    
    return allTestsPassed ? 0 : 1;
}