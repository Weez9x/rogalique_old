#pragma once

#include "Component.h"
#include "TransformComponent.h"
#include "RigidbodyComponent.h"
#include "HealthComponent.h"
#include "AnimationComponent.h"
#include "SpriteRendererComponent.h"
#include "Vector.h"
#include "ColliderComponent.h"
#include "GameSettings.h"
#include <functional>

namespace RogaliqueGame
{
class RespawnComponent : public EngineGame::Component
{
public:
    RespawnComponent(EngineGame::GameObject* gameObject);

    void Update(float deltaTime) override;
    void Render() override;

    void SetSpawnPosition(const EngineGame::Vector2Df& position);
    void SetMaxHealth(float value);
    // Optional provider lets enemies respawn on the current generated level.
    void SetRespawnPositionProvider(std::function<EngineGame::Vector2Df()> provider);

private:
    void StartRespawnWaiting();
    void Respawn();
    void UpdateInvulnerability(float deltaTime);

private:
    EngineGame::TransformComponent* transform = nullptr;
    EngineGame::RigidbodyComponent* rigidbody = nullptr;
    EngineGame::HealthComponent* health = nullptr;
    EngineGame::AnimationComponent* animation = nullptr;
    EngineGame::SpriteRendererComponent* spriteRenderer = nullptr;
    EngineGame::ColliderComponent* collider = nullptr;

    EngineGame::Vector2Df spawnPosition = {0.f, 0.f};

    std::function<EngineGame::Vector2Df()> respawnPositionProvider;

    float maxHealth = PLAYER_MAX_HEALTH;

    float respawnDelay = RESPAWN_DELAY;
    float respawnTimer = 0.0f;
    bool isWaitingRespawn = false;

    float invulnerabilityTime = INVULNERABILITY_TIME;
    float invulnerabilityTimer = 0.0f;
    bool isInvulnerable = false;

    float blinkInterval = BLINK_INTERVAL;
    float blinkTimer = 0.0f;

    // Enemy kills are counted once per death, before the enemy can respawn.
    bool killCounted = false;
    bool IsEnemyObject() const;
};
} // namespace RogaliqueGame
