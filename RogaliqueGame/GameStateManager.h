#pragma once

#include "GameState.h"

namespace RogaliqueGame
{
class GameStateManager
{
public:
    static void SetState(GameState newState);
    static GameState GetState();

private:
    static GameState currentState;
};
} // namespace RogaliqueGame