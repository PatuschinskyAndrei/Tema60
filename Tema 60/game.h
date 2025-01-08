#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <sstream>


class Game {
public:
    Game();
    void startGame();

private:
    void resetGame();
    void render();
    void update(float deltaTime);
    void handleEvents();

    sf::RenderWindow window;
    sf::RectangleShape ground;
    sf::Font font;
    sf::Text timerText;
    sf::Text pauseText;
    sf::Text retryText;
    sf::Text highscoreText;  // Text pentru afisarea Highscore-ului
    sf::RectangleShape retryButton;

    Dino dino;
    std::vector<Obstacle> obstacles;

    float timer;
    bool isGameOver;
    bool isPaused;
    float obstacleSpawnTimer;
    float highscore;  // Highscore-ul
};

#endif // GAME_H
