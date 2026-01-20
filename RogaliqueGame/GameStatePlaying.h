#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "GameState.h"

namespace RogaliqueGame
{
    class GameStatePlaying : public GameState
    {
    private:

        sf::Font font;
        sf::Text infoText;
        sf::Text livesText;
        sf::Text scoreText;
        sf::Text bonusText;

        bool isGameOver = false;
        bool isWin = false;
        bool requestToMainMenu = false;

    public:
        GameStatePlaying();
        ~GameStatePlaying() override = default;

        void onEnter() override;
        void handleEvent(const sf::Event& event) override;
        void update(float dt) override;
        void draw(sf::RenderWindow& window) override;

        bool gameOver() const { return isGameOver; }
        bool gameWin() const { return isWin; }
        bool shouldGoToMainMenu() const { return requestToMainMenu; }
    };
}
