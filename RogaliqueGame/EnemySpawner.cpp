#include "EnemySpawner.h"

#include "HealthComponent.h"
#include "Logger.h"
#include "TransformComponent.h"
#include "RespawnComponent.h"

#include <cmath>

namespace RogaliqueGame
{
EnemySpawner::EnemySpawner(EngineGame::GameObject* playerObject) : playerObject(playerObject)
{
    if (playerObject == nullptr)
    {
        EngineGame::Logger::Instance()->Warning("EnemySpawner created with null playerObject");
    }
}

void EnemySpawner::Spawn(EnemyType type, const EngineGame::Vector2Df& position)
{

    if (playerObject == nullptr)
    {
        EngineGame::Logger::Instance()->Warning("EnemySpawner cannot spawn enemy without playerObject");
        return;
    }

    std::unique_ptr<Enemy> enemy;

    switch (type)
    {
    case EnemyType::Slime:
        enemy = std::make_unique<Slime>(playerObject, position);
        EngineGame::Logger::Instance()->Info("Spawned Slime");
        break;

    case EnemyType::Orc:
        enemy = std::make_unique<Orc>(playerObject, position);
        EngineGame::Logger::Instance()->Info("Spawned Orc");
        break;

    default:
        EngineGame::Logger::Instance()->Warning("EnemySpawner received unknown enemy type");
        return;
    }

    if (levelBuilder != nullptr)
    {
        auto respawn = enemy->GetGameObject()->GetComponent<RespawnComponent>();

        if (respawn != nullptr)
        {
            // Respawn positions come from the current level so enemies never return to old-map coordinates.
            respawn->SetRespawnPositionProvider([this]() { return levelBuilder->GetRandomFloorPosition(); });
        }
    }

    enemies.push_back(std::move(enemy));
}

void EnemySpawner::SpawnMany(EnemyType type, int count, const EngineGame::Vector2Df& startPosition, float spacing)
{
    if (count <= 0)
    {
        EngineGame::Logger::Instance()->Warning("EnemySpawner SpawnMany count must be positive");
        return;
    }

    for (int i = 0; i < count; ++i)
    {
        EngineGame::Vector2Df position = {startPosition.x + i * spacing, startPosition.y};

        Spawn(type, position);
    }
}

void EnemySpawner::SetLevelBuilder(LevelBuilder* builder)
{
    levelBuilder = builder;

    if (levelBuilder == nullptr)
    {
        EngineGame::Logger::Instance()->Warning("EnemySpawner levelBuilder is null");
    }
}

EngineGame::GameObject* EnemySpawner::FindClosestEnemy(const EngineGame::Vector2Df& position, float maxDistance)
{
    EngineGame::GameObject* closestEnemy = nullptr;
    float closestDistance = maxDistance;

    for (const auto& enemy : enemies)
    {
        if (enemy == nullptr || enemy->GetGameObject() == nullptr)
        {
            continue;
        }

        EngineGame::GameObject* enemyObject = enemy->GetGameObject();

        // Dead enemies stay in the spawner list while their RespawnComponent handles the delay.
        auto health = enemyObject->GetComponent<EngineGame::HealthComponent>();
        if (health != nullptr && health->IsDead())
        {
            continue;
        }

        auto enemyTransform = enemyObject->GetComponent<EngineGame::TransformComponent>();
        if (enemyTransform == nullptr)
        {
            continue;
        }

        EngineGame::Vector2Df enemyPosition = enemyTransform->GetWorldPosition();

        float dx = enemyPosition.x - position.x;
        float dy = enemyPosition.y - position.y;
        float distance = std::sqrt(dx * dx + dy * dy);

        if (distance < closestDistance)
        {
            closestDistance = distance;
            closestEnemy = enemyObject;
        }
    }

    return closestEnemy;
}
} // namespace RogaliqueGame
