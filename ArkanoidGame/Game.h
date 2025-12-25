#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "GameState.h"

namespace Arkanoid
{
	enum class StateType
	{
		None,
		MainMenu,
		Playing,
		GameOver,
		GameWin
	};

	class Game
	{
	private:
		std::unique_ptr<GameState> currentState;
		StateType currentType = StateType::None;

		void changeStateInternal(StateType newType);

	public:
		Game();
		~Game() = default;

		void init();

		void handleEvent(const sf::Event& event);
		void update(float dt);
		void draw(sf::RenderWindow& window);

		bool isQuitRequested() const { return currentType == StateType::None; }
	};
}
