#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <SFML/Graphics.hpp>

class obstacle {
public:
    sf::RectangleShape shape;

    obstacle(float x, float y, float width, float height);
    void update(float deltaTime);
};

#endif
