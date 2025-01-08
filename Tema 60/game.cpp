#include "game.h"
#include "constants.h"
#include "dino.h"
#include "obstacle.h"


Game::Game() : window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Jump over obstacles game"),
dino(100, GROUND_HEIGHT - 50),
timer(0), isGameOver(false), isPaused(false), obstacleSpawnTimer(0), highscore(0) {
    ground.setSize({ WINDOW_WIDTH, 10 });
    ground.setFillColor(sf::Color(139, 69, 19));
    ground.setPosition(0, GROUND_HEIGHT);

    retryButton.setSize(sf::Vector2f(100, 50));
    retryButton.setFillColor(sf::Color::Blue);
    retryButton.setPosition(WINDOW_WIDTH / 2 - 50, WINDOW_HEIGHT / 2 - 25);

    if (!font.loadFromFile("resources/Arial.ttf")) {
        // Ensure the font file is available or replace with another font file
    }

    retryText.setFont(font);
    retryText.setString("Retry");
    retryText.setFillColor(sf::Color::White);
    retryText.setCharacterSize(24);
    retryText.setPosition(WINDOW_WIDTH / 2 - 25, WINDOW_HEIGHT / 2 - 15);

    pauseText.setFont(font);
    pauseText.setString("Paused");
    pauseText.setFillColor(sf::Color::White);
    pauseText.setCharacterSize(32);
    pauseText.setPosition(WINDOW_WIDTH / 2 - 50, WINDOW_HEIGHT / 2 - 50);

    timerText.setFont(font);
    timerText.setFillColor(sf::Color::White);
    timerText.setCharacterSize(24);
    timerText.setPosition(WINDOW_WIDTH / 2 - 50, 10);

    highscoreText.setFont(font);
    highscoreText.setFillColor(sf::Color::White);
    highscoreText.setCharacterSize(24);
    highscoreText.setPosition(WINDOW_WIDTH / 2 - 50, 40);
}

void Game::resetGame() {
    dino.shape.setPosition(100, GROUND_HEIGHT - dino.shape.getSize().y);
    dino.isJumping = false;
    dino.yVelocity = 0;
    obstacles.clear();
    timer = 0;
    isGameOver = false;
}

void Game::render() {
    window.clear(sf::Color::Black);
    window.draw(ground);
    window.draw(dino.shape);

    for (auto& obstacle : obstacles) {
        window.draw(obstacle.shape);
    }

    if (isGameOver) {
        window.draw(retryButton);
        window.draw(retryText);
    }

    if (isPaused) {
        window.draw(pauseText);
    }

    // Set the timer text
    std::ostringstream oss;
    oss << "Score: " << static_cast<int>(timer);
    timerText.setString(oss.str());
    window.draw(timerText);

    // Set the highscore text
    std::ostringstream highscoreStr;
    highscoreStr << "Highscore: " << static_cast<int>(highscore);
    highscoreText.setString(highscoreStr.str());
    window.draw(highscoreText);

    window.display();
}

void Game::update(float deltaTime) {
    if (isGameOver || isPaused) return;

    timer += deltaTime;

    dino.update(deltaTime);

    obstacleSpawnTimer += deltaTime;
    if (obstacleSpawnTimer > 1.5f) {
        float minHeight = 30;
        float maxHeight = 60;
        float height = minHeight + std::rand() % static_cast<int>(maxHeight - minHeight + 1);
        obstacles.emplace_back(WINDOW_WIDTH, GROUND_HEIGHT - height, 20, height);
        obstacleSpawnTimer = 0;
    }

    for (auto& obstacle : obstacles) {
        obstacle.update(deltaTime);
    }

    // Check for collision
    for (const auto& obstacle : obstacles) {
        if (dino.shape.getGlobalBounds().intersects(obstacle.shape.getGlobalBounds())) {
            isGameOver = true;
            highscore = std::max(highscore, timer); // Set highscore to max time survived
            break;
        }
    }
}

void Game::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();

        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
            if (!isGameOver) {
                isPaused = !isPaused;
            }
        }

        if (!isGameOver && !isPaused && event.type == sf::Event::KeyPressed && (event.key.code == sf::Keyboard::Space)) {
            dino.jump();
        }

        // If game is over, handle retry with space or left click
        if (isGameOver) {
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
                resetGame();
            }

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                sf::Vector2f worldPos = window.mapPixelToCoords(mousePos);
                if (retryButton.getGlobalBounds().contains(worldPos)) {
                    resetGame();
                }
            }
        }
    }
}

void Game::startGame() {
    sf::Clock clock;

    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();

        handleEvents();
        update(deltaTime);
        render();
    }
}
