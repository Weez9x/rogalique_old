#include "PlayerRegenerationComponent.h"
#include "LightAuraComponent.h"
#include "HealingAuraComponent.h"

#include "GameObject.h"
#include "Logger.h"

namespace RogaliqueGame
{
PlayerRegenerationComponent::PlayerRegenerationComponent(EngineGame::GameObject* gameObject) : Component(gameObject)
{
    health = gameObject->GetComponent<EngineGame::HealthComponent>();
    particles = gameObject->GetComponent<EngineGame::ParticleEmitterComponent>();
    transform = gameObject->GetComponent<EngineGame::TransformComponent>();

    if (health == nullptr)
    {
        EngineGame::Logger::Instance()->Warning("PlayerRegenerationComponent requires HealthComponent");
    }

    if (health != nullptr)
    {
        lastHealth = health->GetHealth();
    }
}

void PlayerRegenerationComponent::Update(float deltaTime)
{
    auto aura = gameObject->GetComponent<HealingAuraComponent>();   
    if (health->GetHealth() >= health->GetMaxHealth())
    {
        if (aura != nullptr)
        {
            aura->SetActive(false);
        }
        return;
    }

    if (health == nullptr || health->IsDead())
    {
        if (aura != nullptr)
        {
            aura->SetActive(false);
        }
        return;
    }

    float currentHealth = health->GetHealth();

    // If health has decreased, the player has received damage, and the rest timer is reset.
    if (currentHealth < lastHealth)
    {
        if (aura != nullptr)
        {
            aura->SetActive(false);
        }
        noCombatTimer = 0.f;
    }

    lastHealth = currentHealth;

    noCombatTimer += deltaTime;

    if (noCombatTimer < regenDelay)
    {
        return;
    }

    healTickTimer -= deltaTime;

    if (healTickTimer <= 0.f)
    {
        health->Heal(healAmountPerTick);

        if (particles != nullptr && transform != nullptr)
        {
            particles->EmitHeal(transform->GetWorldPosition());
        }
        aura->SetActive(true);
        healTickTimer = healTickInterval;
    }

    if (healEffectTimer <= 0.f)
    {
        if (particles != nullptr && transform != nullptr)
        {
            particles->EmitHeal(transform->GetWorldPosition());
        }

        healEffectTimer = healEffectInterval;
    }

    lastHealth = health->GetHealth();
}

void PlayerRegenerationComponent::Render() {}

void PlayerRegenerationComponent::NotifyCombatAction()
{
    auto aura = gameObject->GetComponent<HealingAuraComponent>();
    if (aura != nullptr)
    {
        aura->SetActive(false);
    }
    noCombatTimer = 0.f;
    healEffectTimer = 0.f;
}
} // namespace RogaliqueGame