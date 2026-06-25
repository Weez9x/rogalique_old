#pragma once

#include "Component.h"
#include "HealthComponent.h"
#include "ParticleEmitterComponent.h"
#include "TransformComponent.h"

namespace RogaliqueGame
{
class PlayerRegenerationComponent : public EngineGame::Component
{
public:
    PlayerRegenerationComponent(EngineGame::GameObject* gameObject);

    void Update(float deltaTime) override;
    void Render() override;

    void NotifyCombatAction();

private:
    EngineGame::HealthComponent* health = nullptr;
    EngineGame::ParticleEmitterComponent* particles = nullptr;
    EngineGame::TransformComponent* transform = nullptr;

    float noCombatTimer = 0.f;
    float regenDelay = 10.f;
    float healPerSecond = 3.f;

    float healTickTimer = 0.f;
    float healTickInterval = 1.5f;
    float healAmountPerTick = 1.f;

    float healEffectTimer = 0.f;
    float healEffectInterval = 0.5f;

    float lastHealth = 0.f;
};
} // namespace RogaliqueGame