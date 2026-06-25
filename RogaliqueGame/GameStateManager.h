#pragma once

#include "GameState.h"

namespace RogaliqueGame
{
class GameStateManager
{
public:
    // Lightweight global state gate for gameplay systems and end-screen UI.
    static void SetState(GameState newState);
    static GameState GetState();
    static bool IsPlaying();
    static bool IsEndScreen();
    static void Reset();

private:
    static GameState currentState;
};
} // namespace RogaliqueGame
