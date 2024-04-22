

#ifndef SNAKE_H
#define SNAKE_H

#include "GameObject.h"
#include <deque>
#include <SFML/Graphics.hpp>

class Snake : public GameObject {
protected:
    std::deque<sf::RectangleShape> segments;
    sf::Vector2f direction;
    float speed;
    float accumulator;
    sf::Color color;  // Store color as a member variable
    sf::Clock clock;  // Clock to manage update intervals

public:
    Snake(float startX, float startY, const sf::Color& snakeColor) : direction(0.f, -20.f), speed(0.1f), accumulator(0.f), color(snakeColor) {
        sf::RectangleShape initialSegment(sf::Vector2f(20.f, 20.f));
        initialSegment.setFillColor(color);
        initialSegment.setPosition(startX, startY);
        segments.push_back(initialSegment);
    }

    void update(float dt) {
        accumulator += dt;
        if (accumulator >= speed) {
            move();
            accumulator = 0.f;
        }
    }

    void render(sf::RenderWindow& window) override {
        for (auto& segment : segments) {
            window.draw(segment);
        }
    }

    void setDirection(const sf::Vector2f& newDirection) {
        if (newDirection + direction != sf::Vector2f(0, 0)) { // Prevent reversing direction
            direction = newDirection;
        }
    }

    sf::Vector2f getDirection() const {
        return direction;
    }

    void move() {
        if (segments.empty()) return;

        sf::Vector2f headPosition = segments.front().getPosition();
        sf::Vector2f newHeadPosition = headPosition + direction;

        // Implementing wrap-around logic for the game boundaries
        if (newHeadPosition.x < 0) newHeadPosition.x = 800 - 20;
        else if (newHeadPosition.x >= 800) newHeadPosition.x = 0;
        if (newHeadPosition.y < 0) newHeadPosition.y = 600 - 20;
        else if (newHeadPosition.y >= 600) newHeadPosition.y = 0;

        // Debug output
        std::cout << "Moving from " << headPosition.x << ", " << headPosition.y << " to " << newHeadPosition.x << ", " << newHeadPosition.y << std::endl;

        for (size_t i = segments.size() - 1; i > 0; --i) {
            segments[i].setPosition(segments[i - 1].getPosition());
        }
        segments.front().setPosition(newHeadPosition);
    }

    bool checkSelfCollision() const {
        if (segments.size() < 2) return false; // No collision if there is only one segment

        const sf::FloatRect headBounds = segments.front().getGlobalBounds();
        for (size_t i = 1; i < segments.size(); ++i) {
            if (headBounds.intersects(segments[i].getGlobalBounds())) {
                std::cout << "Self-collision at segment " << i << std::endl;
                return true;
            }
        }
        return false;
    }


    void grow() {
        if (segments.empty()) return;  // Ensure there is at least one segment to work with

        // Get the last segment's position and direction to place the new segment correctly
        sf::Vector2f lastSegmentPosition = segments.back().getPosition();
        sf::Vector2f newSegmentPosition = lastSegmentPosition - direction;

        // Check if the new segment position is valid or needs adjustment for wrap around
        if (newSegmentPosition.x < 0) newSegmentPosition.x += 800;
        else if (newSegmentPosition.x >= 800) newSegmentPosition.x -= 800;
        if (newSegmentPosition.y < 0) newSegmentPosition.y += 600;
        else if (newSegmentPosition.y >= 600) newSegmentPosition.y -= 600;

        sf::RectangleShape newSegment(sf::Vector2f(20.f, 20.f));
        newSegment.setFillColor(color);
        newSegment.setPosition(newSegmentPosition);
        segments.push_back(newSegment);
    }



    bool checkCollision(const sf::Vector2f& position) const {
        // Only check collision with the head segment
        return segments.front().getGlobalBounds().contains(position);
    }

    bool checkSelfCollision() const {
        // Check if the head collides with any other part of the body
        for (size_t i = 1; i < segments.size(); ++i) {
            if (segments.front().getGlobalBounds().intersects(segments[i].getGlobalBounds())) {
                return true;
            }
        }
        return false;
    }

    bool checkCollisionWithSnake(const Snake* otherSnake) const {
        // Check if this snake's head collides with any segment of another snake
        for (auto& segment : otherSnake->segments) {
            if (segments.front().getGlobalBounds().intersects(segment.getGlobalBounds())) {
                return true;
            }
        }
        return false;
    }
    sf::Vector2f getPosition() const override {
        if (!segments.empty()) {
            return segments.front().getPosition();
        }
        return sf::Vector2f();  // Return a default value if no segments exist
    }

};

#endif // SNAKE_H

