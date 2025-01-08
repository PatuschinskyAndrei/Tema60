#include "dino.h"
#include "constants.h"

dino::dino(float x, float y) {
    shape.setPosition(x, y);
    shape.setSize({ 50, 50 });
    shape.setFillColor(sf::Color::Green);
}

void dino::jump() {
    if (!isJumping) {
        yVelocity = JUMP_VELOCITY;
        isJumping = true;
    }
}

void dino::update(float deltaTime) {
    yVelocity += GRAVITY * deltaTime;
    shape.move(0, yVelocity * deltaTime);

    if (shape.getPosition().y >= GROUND_HEIGHT - shape.getSize().y) {
        shape.setPosition(shape.getPosition().x, GROUND_HEIGHT - shape.getSize().y);
        yVelocity = 0;
        isJumping = false;
    }
}
