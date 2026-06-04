#pragma once

#include "Enemy.h"

namespace RogaliqueGame
{
class Slime : public Enemy
{
public:
    Slime(EngineGame::GameObject* playerObject, const EngineGame::Vector2Df& spawnPosition);
};
} // namespace RogaliqueGame