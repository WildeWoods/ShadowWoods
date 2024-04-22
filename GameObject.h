#pragma once


#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <SFML/Graphics.hpp>

// Abstract base class for all game objects in the game
class GameObject {
public:
    // Virtual destructor to ensure proper cleanup of derived classes
    virtual ~GameObject() {}

    // Virtual update method, to be overridden by derived classes
    // This method will be called every game tick to update the state of the game object
    virtual void update(float dt) = 0;

    // Virtual render method, to be overridden by derived classes
    // This method will be called every game tick to render the game object
    virtual void render(sf::RenderWindow& window) = 0;

    // Virtual method to get the position of the game object
    // This is important for collision detection and interactions between objects
    virtual sf::Vector2f getPosition() const = 0;

    // Depending on the game design, you might also want to include methods for handling collisions directly here
    // virtual void handleCollision(GameObject& other) = 0;
};

#endif // GAME_OBJECT_H
