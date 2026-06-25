#include "GameStateManager.h"

namespace RogaliqueGame
{
GameState GameStateManager::currentState = GameState::Playing;

void GameStateManager::SetState(GameState newState)
{
    if (currentState == newState)
    {
        return;
    }

    currentState = newState;
}

GameState GameStateManager::GetState()
{
    return currentState;
}

bool GameStateManager::IsPlaying()
{
    return currentState == GameState::Playing;
}

bool GameStateManager::IsEndScreen()
{
    return currentState == GameState::Win || currentState == GameState::GameOver;
}

void GameStateManager::Reset()
{
    SetState(GameState::Playing);
}
} // namespace RogaliqueGame
