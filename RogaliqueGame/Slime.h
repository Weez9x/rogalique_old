#pragma once

#include "Enemy.h"

namespace RogaliqueGame
{
class Slime : public Enemy
{
public:
    // Fast lightweight enemy that uses the shared follow/attack/respawn components.
    Slime(EngineGame::GameObject* playerObject, const EngineGame::Vector2Df& spawnPosition);
};
} // namespace RogaliqueGame
