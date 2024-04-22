#pragma once


#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <iostream>
#include "Snake.h"
#include "AISnake.h"
#include "Food.h"

class Game {
private:
    sf::RenderWindow window;
    std::vector<std::unique_ptr<Snake>> snakes;
    std::vector<std::unique_ptr<Food>> foods;
    sf::Clock clock;

public:
    Game() : window(sf::VideoMode(800, 600), "SFML Multi-Snake") {
        window.setFramerateLimit(60);
        initSnakes();
        spawnFood(5);
    }

    void run() {
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
            }
            float dt = clock.restart().asSeconds();
            update(dt);
            render();
        }
    }

private:
    void initSnakes() {
        snakes.push_back(std::make_unique<Snake>(400.f, 300.f, sf::Color::Green));
        snakes.push_back(std::make_unique<AISnake>(100.f, 100.f, sf::Color::Blue));
    }

    void update(float dt) {
        for (auto& snake : snakes) {
            snake->update(dt);
            AISnake* aiSnake = dynamic_cast<AISnake*>(snake.get());
            if (aiSnake && !foods.empty()) {
                aiSnake->update(dt, findNearestFood(aiSnake->getPosition()));
            }
        }
        checkCollisions();
    }

    void render() {
        window.clear();
        for (const auto& snake : snakes) {
            snake->render(window);
        }
        for (const auto& food : foods) {
            food->render(window);
        }
        window.display();
    }

    void spawnFood(int count) {
        for (int i = 0; i < count; ++i) {
            float x = std::rand() % (window.getSize().x - 20) + 10;
            float y = std::rand() % (window.getSize().y - 20) + 10;
            foods.push_back(std::make_unique<Food>(x, y));
        }
    }

    sf::Vector2f findNearestFood(const sf::Vector2f& pos) {
        sf::Vector2f nearestPos;
        float minDist = std::numeric_limits<float>::max();
        for (const auto& food : foods) {
            float dist = hypot(pos.x - food->getPosition().x, pos.y - food->getPosition().y);
            if (dist < minDist) {
                minDist = dist;
                nearestPos = food->getPosition();
            }
        }
        return nearestPos;
    }

    void checkCollisions() {
        for (auto& snake : snakes) {
            for (auto it = foods.begin(); it != foods.end();) {
                if (snake->checkCollision((*it)->getPosition())) {
                    snake->grow();
                    it = foods.erase(it);
                }
                else {
                    ++it;
                }
            }
        }
        handleSnakeCollisions();
    }
    void handleSnakeCollisions() {
        for (size_t i = 0; i < snakes.size(); ++i) {
            if (snakes[i]->checkSelfCollision()) {
                std::cout << "Self-collision detected for snake " << i << std::endl;
                endGame();
                return;
            }
            for (size_t j = 0; j < snakes.size(); ++j) {
                if (i != j && snakes[i]->checkCollisionWithSnake(snakes[j].get())) {
                    std::cout << "Collision detected between snake " << i << " and snake " << j << std::endl;
                    endGame();
                    return;
                }
            }
        }
    }


    void endGame() {
        std::cout << "Game Over!" << std::endl;
        window.close();
    }
};

#endif // GAME_H
