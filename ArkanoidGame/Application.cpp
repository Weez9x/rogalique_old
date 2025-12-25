#include "Application.h"
#include "GameSettings.h"
#include "Brick.h"

namespace Arkanoid
{
	Application::Application()
		: window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Arkanoid")
	{
		window.setFramerateLimit(60);
		game.init();
	}
	Application::~Application()
	{
		Arkanoid::Brick::unloadTextures();
	}

	void Application::run()
	{
		sf::Clock clock;
		while (window.isOpen() && running)
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
				{
					window.close();
					running = false;
				}

				// Event to Game
				game.handleEvent(event);
			}
			//EndGame
			if (game.isQuitRequested())
			{
				window.close();
				break;
			}

			float dt = clock.restart().asSeconds();

			game.update(dt);

			window.clear(sf::Color::Black);
			game.draw(window);
			window.display();
		}
	}
}

