#include "GameStateGameOver.h"
#include "GameSettings.h"
#include <cassert>

namespace Arkanoid
{
	GameStateGameOver::GameStateGameOver() {}

	void GameStateGameOver::onEnter()
	{
		if (!font.loadFromFile(FONTS_PATH + "Roboto-Regular.ttf"))
		{
			// fallback
		}

		title.setFont(font);
		title.setString("GAME OVER");
		title.setCharacterSize(64);
		title.setFillColor(sf::Color::Yellow);
		title.setPosition(SCREEN_WIDTH / 2.f, 150.f);
		title.setOrigin(title.getLocalBounds().width / 2.f, title.getLocalBounds().height / 2.f);

		hint.setFont(font);
		hint.setString("Press Space to restart\nPress Esc to return to menu");
		hint.setCharacterSize(20);
		hint.setFillColor(sf::Color::White);
		hint.setPosition(SCREEN_WIDTH / 2.f, 300.f);
		hint.setOrigin(hint.getLocalBounds().width / 2.f, hint.getLocalBounds().height / 2.f);
	}

	void GameStateGameOver::handleEvent(const sf::Event& event)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Space)
			{
				requestRestart = true;
			}
			else if (event.key.code == sf::Keyboard::Escape)
			{
				requestMenu = true;
			}
		}
	}

	void GameStateGameOver::update(float /*dt*/) {}

	void GameStateGameOver::draw(sf::RenderWindow& window)
	{
		window.draw(title);
		window.draw(hint);
	}
}
