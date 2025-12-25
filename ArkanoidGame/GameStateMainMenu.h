#pragma once
#include <SFML/Graphics.hpp>
#include "GameState.h"

namespace Arkanoid
{
	class GameStateMainMenu : public GameState
	{
	private:
		sf::Font font;
		sf::Text title;
		sf::Text hint;
		bool requestStart = false;

	public:
		GameStateMainMenu();
		~GameStateMainMenu() override = default;

		void onEnter() override;
		void handleEvent(const sf::Event& event) override;
		void update(float dt) override;
		void draw(sf::RenderWindow& window) override;

		bool shouldStart() const { return requestStart; }
	};
}
