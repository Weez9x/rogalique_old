#include "GameStatePlaying.h"
#include "GameSettings.h"
#include <cstdlib>
#include <cmath>

namespace RogaliqueGame
{
    GameStatePlaying::GameStatePlaying()
    {
     
    }

    void GameStatePlaying::onEnter()
    {
        font.loadFromFile(FONTS_PATH + "Roboto-Regular.ttf");

        infoText.setFont(font);
        infoText.setCharacterSize(18);
        infoText.setFillColor(sf::Color::White);
        infoText.setPosition(10.f, 10.f);
        infoText.setString("ESC - to menu");

        livesText.setFont(font);
        livesText.setCharacterSize(18);
        livesText.setFillColor(sf::Color::White);
        livesText.setPosition(150.f, 10.f);

        scoreText.setFont(font);
        scoreText.setCharacterSize(18);
        scoreText.setFillColor(sf::Color::White);
        scoreText.setPosition(250.f, 10.f);

        bonusText.setFont(font);
        bonusText.setCharacterSize(18);
        bonusText.setFillColor(sf::Color::Cyan);
        bonusText.setPosition(500.f, 10.f);
    }

    void GameStatePlaying::handleEvent(const sf::Event& event)
    {
        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Escape)
                requestToMainMenu = true;
        }
    }

    void GameStatePlaying::update(float dt)
    {
        if (isGameOver || isWin) return;
    }

    void GameStatePlaying::draw(sf::RenderWindow& window)
    {

    }
}
