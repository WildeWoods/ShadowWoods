#pragma once
#ifndef AI_SNAKE_H
#define AI_SNAKE_H

#include "Snake.h"
#include <cmath>  // For hypot function to calculate distances

class AISnake : public Snake {
public:
    AISnake(float x, float y, const sf::Color& color) : Snake(x, y, color) {}

    // Correct override of the update method
    void update(float dt, const sf::Vector2f& target)  {
        sf::Vector2f headPos = segments.front().getPosition();
        sf::Vector2f diff = target - headPos;
        float dist = std::hypot(diff.x, diff.y);
        if (dist > 0) {
            diff /= dist;  // Normalize vector
            direction = diff * 20.f;  // Adjust speed
        }
        Snake::update(dt);  // Use the base update for movement
    }

};

#endif // AI_SNAKE_H


