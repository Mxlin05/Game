#pragma once
#include <utility>  // For std::make_pair

// Text Alignment Macros for UI Elements
// These macros calculate the correct X,Y position for text within a frame/button

// Helper macro to get text width (approximate calculation)
#define GET_TEXT_WIDTH(text, scale) (text.length() * 8.0f * scale)

// HORIZONTAL ALIGNMENT MACROS
#define ALIGN_LEFT(frameX) (frameX)
#define ALIGN_CENTER(frameX, frameWidth, textWidth) (frameX + (frameWidth - textWidth) / 2.0f)
#define ALIGN_RIGHT(frameX, frameWidth, textWidth) (frameX + frameWidth - textWidth)

// VERTICAL ALIGNMENT MACROS  
#define ALIGN_TOP(frameY) (frameY)
#define ALIGN_MIDDLE(frameY, frameHeight, textHeight) (frameY + (frameHeight - textHeight) / 2.0f)
#define ALIGN_BOTTOM(frameY, frameHeight, textHeight) (frameY + frameHeight - textHeight)

// SIMPLE ALIGNMENT MACROS (most commonly used)
// These assume standard text height of 20 pixels and calculate text width automatically

// Top alignments
#define ALIGN_TOP_LEFT(frameX, frameY, text, scale) \
    std::make_pair((frameX), (frameY))

#define ALIGN_TOP_CENTER(frameX, frameY, frameWidth, text, scale) \
    std::make_pair((frameX + (frameWidth - GET_TEXT_WIDTH(text, scale)) / 2.0f), (frameY))

#define ALIGN_TOP_RIGHT(frameX, frameY, frameWidth, text, scale) \
    std::make_pair((frameX + frameWidth - GET_TEXT_WIDTH(text, scale)), (frameY))

// Middle alignments
#define ALIGN_MIDDLE_LEFT(frameX, frameY, frameHeight, text, scale) \
    std::make_pair((frameX), (frameY + (frameHeight - 20.0f * scale) / 2.0f))

#define ALIGN_MIDDLE_CENTER(frameX, frameY, frameWidth, frameHeight, text, scale) \
    std::make_pair((frameX + (frameWidth - GET_TEXT_WIDTH(text, scale)) / 2.0f), (frameY + (frameHeight - 20.0f * scale) / 2.0f))

#define ALIGN_MIDDLE_RIGHT(frameX, frameY, frameWidth, frameHeight, text, scale) \
    std::make_pair((frameX + frameWidth - GET_TEXT_WIDTH(text, scale)), (frameY + (frameHeight - 20.0f * scale) / 2.0f))

// Bottom alignments
#define ALIGN_BOTTOM_LEFT(frameX, frameY, frameHeight, text, scale) \
    std::make_pair((frameX), (frameY + frameHeight - 20.0f * scale))

#define ALIGN_BOTTOM_CENTER(frameX, frameY, frameWidth, frameHeight, text, scale) \
    std::make_pair((frameX + (frameWidth - GET_TEXT_WIDTH(text, scale)) / 2.0f), (frameY + frameHeight - 20.0f * scale))

#define ALIGN_BOTTOM_RIGHT(frameX, frameY, frameWidth, frameHeight, text, scale) \
    std::make_pair((frameX + frameWidth - GET_TEXT_WIDTH(text, scale)), (frameY + frameHeight - 20.0f * scale))

// CONVENIENCE MACRO FOR RENDERING ALIGNED TEXT
#define RENDER_ALIGNED_TEXT(renderer, shader, textRenderer, frameX, frameY, frameWidth, frameHeight, text, scale, alignment) \
    do { \
        auto [alignedX, alignedY] = alignment(frameX, frameY, frameWidth, frameHeight, text, scale); \
        renderText(renderer, shader, textRenderer, alignedX, alignedY, text, scale); \
    } while(0)
