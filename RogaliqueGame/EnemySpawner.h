#pragma once

#include <memory>
#include <vector>

#include "Enemy.h"
#include "Orc.h"
#include "Slime.h"
#include "Vector.h"
#include "LevelBuilder.h"

namespace RogaliqueGame
{
enum class EnemyType
{
    Slime,
    Orc
};

class EnemySpawner
{
public:
    EnemySpawner(EngineGame::GameObject* playerObject);

    // Owns enemy wrappers and gives combat systems a single place to find valid targets.
    void Spawn(EnemyType type, const EngineGame::Vector2Df& position);

    void SpawnMany(EnemyType type, int count, const EngineGame::Vector2Df& startPosition, float spacing);

    void SetLevelBuilder(LevelBuilder* builder);

    EngineGame::GameObject* FindClosestEnemy(const EngineGame::Vector2Df& position, float maxDistance);

private:
    EngineGame::GameObject* playerObject = nullptr;
    std::vector<std::unique_ptr<Enemy>> enemies;
    LevelBuilder* levelBuilder = nullptr;
};
} // namespace RogaliqueGame
