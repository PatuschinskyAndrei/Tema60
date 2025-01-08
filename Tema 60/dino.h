#ifndef DINO_H
#define DINO_H

#include <SFML/Graphics.hpp>

class dino {
public:
    sf::RectangleShape shape;
    float yVelocity = 0;
    bool isJumping = false;

    dino(float x, float y);
    void jump();
    void update(float deltaTime);
};

#endif
