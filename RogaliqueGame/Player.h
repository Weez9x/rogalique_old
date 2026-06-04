#pragma once
#include "GameObject.h"
#include "Character.h"
#include "EnemySpawner.h"
#include "GameSettings.h"

namespace RogaliqueGame
{
class Player : public Character
{
public:
    Player();
    void SetEnemySpawner(EnemySpawner* spawner);
    EngineGame::Vector2Df GetPosition() const;

private:
};
} // namespace RogaliqueGame