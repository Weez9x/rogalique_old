#pragma once

#include "Enemy.h"

namespace RogaliqueGame
{
class Orc : public Enemy
{
public:
    // Heavier enemy variant with different stats and animation frames.
    Orc(EngineGame::GameObject* playerObject, const EngineGame::Vector2Df& spawnPosition);
};
} // namespace RogaliqueGame
