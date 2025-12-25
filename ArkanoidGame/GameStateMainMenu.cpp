#include "GameStateMainMenu.h"
#include "GameSettings.h"
#include <cassert>

namespace Arkanoid
{
	GameStateMainMenu::GameStateMainMenu()
	{
	}

	void GameStateMainMenu::onEnter()
	{
		if (!font.loadFromFile(FONTS_PATH + "Roboto-Regular.ttf"))
		{
			// fallback if not found
		}

		title.setFont(font);
		title.setString("ARKANOID");
		title.setCharacterSize(64);
		title.setFillColor(sf::Color::Red);
		title.setPosition(SCREEN_WIDTH / 2.f, 150.f);
		title.setOrigin(title.getLocalBounds().width / 2.f, title.getLocalBounds().height / 2.f);

		hint.setFont(font);
		hint.setString("Press Enter to start\nEsc to exit");
		hint.setCharacterSize(20);
		hint.setFillColor(sf::Color::White);
		hint.setPosition(SCREEN_WIDTH / 2.f, 300.f);
		hint.setOrigin(hint.getLocalBounds().width / 2.f, hint.getLocalBounds().height / 2.f);
	}

	void GameStateMainMenu::handleEvent(const sf::Event& event)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Enter)
			{
				requestStart = true;
			}
			else if (event.key.code == sf::Keyboard::Escape)
			{
				
			}
		}
	}

	void GameStateMainMenu::update(float /*dt*/)
	{
	}

	void GameStateMainMenu::draw(sf::RenderWindow& window)
	{
		window.draw(title);
		window.draw(hint);
	}
}
