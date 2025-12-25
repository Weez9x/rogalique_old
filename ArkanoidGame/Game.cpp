#include "Game.h"
#include "GameStateMainMenu.h"
#include "GameStatePlaying.h"
#include "GameStateGameOver.h"
#include "GameStateWin.h"

namespace Arkanoid
{
	Game::Game()
	{
	
	}

	void Game::init()
	{
		changeStateInternal(StateType::MainMenu);
	}

	void Game::changeStateInternal(StateType newType)
	{
		currentState.reset();
		currentType = newType;

		switch (newType)
		{
		case StateType::MainMenu:
			currentState = std::make_unique<GameStateMainMenu>();
			break;
		case StateType::Playing:
			currentState = std::make_unique<GameStatePlaying>();
			break;
		case StateType::GameOver:
			currentState = std::make_unique<GameStateGameOver>();
			break;
		case StateType::GameWin:
			currentState = std::make_unique<GameStateWin>();
			break;
		default:
			currentState = nullptr;
			currentType = StateType::None;
			break;
		}

		if (currentState)
			currentState->onEnter();
	}

	void Game::handleEvent(const sf::Event& event)
	{
		// Global shortcuts
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape && currentType == StateType::MainMenu)
			{
				// Exit from the game
				changeStateInternal(StateType::None);
				return;
			}
		}

		if (!currentState) return;

		// Event to current state
		currentState->handleEvent(event);

		if (currentType == StateType::MainMenu)
		{
			auto* menu = dynamic_cast<GameStateMainMenu*>(currentState.get());
			if (menu && menu->shouldStart())
			{
				changeStateInternal(StateType::Playing);
			}
		}
		else if (currentType == StateType::Playing)
		{
			auto* play = dynamic_cast<GameStatePlaying*>(currentState.get());
			if (play)
			{
				if (play->gameOver())
				{
					changeStateInternal(StateType::GameOver);
				}
				else if (play->shouldGoToMainMenu())
				{
					changeStateInternal(StateType::MainMenu);
				}
			}
		}
		else if (currentType == StateType::GameOver)
		{
			auto* go = dynamic_cast<GameStateGameOver*>(currentState.get());
			if (go)
			{
				if (go->shouldRestart())
				{
					changeStateInternal(StateType::Playing);
				}
				else if (go->shouldGoMenu())
				{
					changeStateInternal(StateType::MainMenu);
				}
			}
		}
		else if (currentType == StateType::GameWin)
		{
			auto* win = dynamic_cast<GameStateWin*>(currentState.get());
			if (win)
			{
				if (win->shouldRestart())
					changeStateInternal(StateType::Playing);
				else if (win->shouldGoMenu())
					changeStateInternal(StateType::MainMenu);
			}
		}

	}

	void Game::update(float dt)
	{
		if (!currentState) return;
		currentState->update(dt);

		if (currentType == StateType::Playing)
		{
			auto* play = dynamic_cast<GameStatePlaying*>(currentState.get());
			if (play && play->gameOver())
			{
				changeStateInternal(StateType::GameOver);
			}
		}
		if (currentType == StateType::Playing)
		{
			auto* play = dynamic_cast<GameStatePlaying*>(currentState.get());
			if (play)
			{
				if (play->gameOver())
					changeStateInternal(StateType::GameOver);
				else if (play->gameWin())
					changeStateInternal(StateType::GameWin);
			}
		}

	}

	void Game::draw(sf::RenderWindow& window)
	{
		if (!currentState) return;
		currentState->draw(window);
	}
}
