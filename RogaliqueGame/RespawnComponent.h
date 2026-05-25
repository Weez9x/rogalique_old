#pragma once

#include "Component.h"
#include "TransformComponent.h"
#include "RigidbodyComponent.h"
#include "HealthComponent.h"
#include "AnimationComponent.h"
#include "SpriteRendererComponent.h"
#include "Vector.h"

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

    EngineGame::Vector2Df spawnPosition = {0.f, 0.f};

    float maxHealth = 100.0f;

    float respawnDelay = 1.0f;
    float respawnTimer = 0.0f;
    bool isWaitingRespawn = false;

    float invulnerabilityTime = 5.0f;
    float invulnerabilityTimer = 0.0f;
    bool isInvulnerable = false;

    float blinkInterval = 0.12f;
    float blinkTimer = 0.0f;
};
} // namespace RogaliqueGame