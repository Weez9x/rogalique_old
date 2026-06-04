#include "pch.h"
#include "HealthComponent.h"
#include "Logger.h"
#include "GameObject.h"

#include <algorithm>
#include <cassert>

namespace EngineGame
{
HealthComponent::HealthComponent(GameObject* gameObject) : Component(gameObject) {}

void HealthComponent::Update(float deltaTime) {}

void HealthComponent::Render() {}

void HealthComponent::SetHealth(float newHealth)
{
    if (newHealth < 0.0f)
    {
        Logger::Instance()->Warning("HealthComponent: health cannot be negative. Clamped to 0.");
        newHealth = 0.0f;
    }

    health = newHealth;
    isDeadLogged = false;
}

void HealthComponent::SetArmor(float newArmor)
{
    if (newArmor < 0.0f)
    {
        Logger::Instance()->Warning("HealthComponent: armor cannot be negative. Clamped to 0.");
        newArmor = 0.0f;
    }

    armor = newArmor;
}

float HealthComponent::GetHealth() const
{
    return health;
}

float HealthComponent::GetArmor() const
{
    return armor;
}

void HealthComponent::TakeDamage(float damage)
{
    if (damage < 0.0f)
    {
        Logger::Instance()->Warning("HealthComponent: negative damage ignored.");
        return;
    }

    if (isInvulnerable)
    {
        // Respawn systems can temporarily ignore all incoming damage.
        Logger::Instance()->Info(gameObject->GetName() + " ignored damage: invulnerable.");
        return;
    }

    float finalDamage = damage - armor;

    // Armor can fully absorb weak hits but never turns damage into healing.
    if (finalDamage < 0.0f)
    {
        finalDamage = 0.0f;
    }

    health -= finalDamage;

    if (health < 0.0f)
    {
        health = 0.0f;
    }

    Logger::Instance()->Info("Damage taken. Damage: " + std::to_string(damage) + ", armor: " + std::to_string(armor) +
                             ", final: " + std::to_string(finalDamage) + ", health: " + std::to_string(health));

    if (IsDead() && !isDeadLogged)
    {
        Logger::Instance()->Info(gameObject->GetName() + " died.");
        isDeadLogged = true;
    }
}

bool HealthComponent::IsDead() const
{
    return health <= 0.0f;
}
void HealthComponent::SetInvulnerable(bool value)
{
    isInvulnerable = value;

    if (isInvulnerable)
    {
        Logger::Instance()->Info(gameObject->GetName() + " became invulnerable.");
    }
    else
    {
        Logger::Instance()->Info(gameObject->GetName() + " is vulnerable again.");
    }
}
bool HealthComponent::IsInvulnerable() const
{
    return isInvulnerable;
}
} // namespace EngineGame
