#include "obstacle.h"

obstacle::obstacle(float x, float y, float width, float height) {
    shape.setPosition(x, y);
    shape.setSize({ width, height });
    shape.setFillColor(sf::Color::Red);
}

void obstacle::update(float deltaTime) {
    shape.move(-300 * deltaTime, 0);
}
