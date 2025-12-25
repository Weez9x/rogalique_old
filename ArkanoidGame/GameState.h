#pragma once
#include <SFML/Graphics.hpp>

namespace Arkanoid
{
	// Абстрактный интерфейс игрового состояния
	class GameState
	{
	public:
		virtual ~GameState() = default;

		virtual void onEnter() {}

		virtual void handleEvent(const sf::Event& event) = 0;

		virtual void update(float dt) = 0;

		virtual void draw(sf::RenderWindow& window) = 0;

		virtual bool isExclusive() const { return true; }
	};
}
