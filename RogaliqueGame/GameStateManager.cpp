#include "GameStateManager.h"

namespace RogaliqueGame
{
GameState GameStateManager::currentState = GameState::Playing;

void GameStateManager::SetState(GameState newState)
{
    currentState = newState;
}

GameState GameStateManager::GetState()
{
    return currentState;
}
} // namespace RogaliqueGame