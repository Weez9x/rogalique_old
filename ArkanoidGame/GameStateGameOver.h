#pragma once
#include <SFML/Graphics.hpp>
#include "GameState.h"

namespace Arkanoid
{
	class GameStateGameOver : public GameState
	{
	private:
		sf::Font font;
		sf::Text title;
		sf::Text hint;
		bool requestRestart = false;
		bool requestMenu = false;

	public:
		GameStateGameOver();
		~GameStateGameOver() override = default;

		void onEnter() override;
		void handleEvent(const sf::Event& event) override;
		void update(float dt) override;
		void draw(sf::RenderWindow& window) override;

		bool shouldRestart() const { return requestRestart; }
		bool shouldGoMenu() const { return requestMenu; }
	};
}
