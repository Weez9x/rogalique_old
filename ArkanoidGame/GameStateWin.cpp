#include "GameStateWin.h"
#include "GameSettings.h"

namespace Arkanoid
{
	GameStateWin::GameStateWin() {}

	void GameStateWin::onEnter()
	{
		font.loadFromFile(FONTS_PATH + "Roboto-Regular.ttf");

		title.setFont(font);
		title.setString("YOU WIN!");
		title.setCharacterSize(64);
		title.setFillColor(sf::Color::Green);
		title.setPosition(SCREEN_WIDTH / 2.f, 150.f);
		title.setOrigin(title.getLocalBounds().width / 2.f, title.getLocalBounds().height / 2.f);

		hint.setFont(font);
		hint.setString("Press Y to play again\nPress N to return to menu");
		hint.setCharacterSize(22);
		hint.setFillColor(sf::Color::White);
		hint.setPosition(SCREEN_WIDTH / 2.f, 300.f);
		hint.setOrigin(hint.getLocalBounds().width / 2.f, hint.getLocalBounds().height / 2.f);
	}

	void GameStateWin::handleEvent(const sf::Event& event)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Y)
				requestRestart = true;
			else if (event.key.code == sf::Keyboard::N)
				requestMenu = true;
		}
	}

	void GameStateWin::update(float /*dt*/) {}
	void GameStateWin::draw(sf::RenderWindow& window)
	{
		window.draw(title);
		window.draw(hint);
	}
}
