#pragma once


#ifndef FOOD_H
#define FOOD_H

#include "GameObject.h"
#include <SFML/Graphics.hpp>

class Food : public GameObject {
private:
    sf::CircleShape shape;  // The visual representation of food

public:
    // Constructor initializes the food's shape and position
    Food(float x, float y) {
        shape.setRadius(10.f);  // Set the radius of the food item
        shape.setFillColor(sf::Color::Red);  // Set the color of the food item
        shape.setPosition(x, y);  // Position the food item at the provided coordinates
    }

    // Update method from GameObject (does nothing for static food)
    void update(float dt) override {
        // Food does not need to update its state, as it's static
    }

    // Rder method to draw the food on the screen
    void render(sf::RenderWindow& window) override {
        window.draw(shape);  // Draw the food shape to the provided window
    }

    // Method to get the position of the food
    sf::Vector2f getPosition() const override {
        return shape.getPosition();  // Return the position of the food shape
    }

    // Method to get the bounding box of the food for collision detection
    sf::FloatRect getBounds() const {
        return shape.getGlobalBounds();  // Return the global bounds of the shape, useful for collision detection
    }
};

#endif // FOOD_H
