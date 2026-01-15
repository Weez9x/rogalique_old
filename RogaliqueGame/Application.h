#pragma once
#include <SFML/Graphics.hpp>
#include "Game.h"

namespace RogaliqueGame
{
	class Application
	{
	private:
		sf::RenderWindow window;
		Game game;
		bool running = true;

	public:
		Application();
		~Application();
		void run();
	};
}
