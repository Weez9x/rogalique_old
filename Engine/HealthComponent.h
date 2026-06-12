#pragma once

#include "Component.h"

namespace EngineGame
{
class HealthComponent : public Component
{
public:
    HealthComponent(GameObject* gameObject);

    void Update(float deltaTime) override;
    void Render() override;

    void SetHealth(float newHealth);
    void SetArmor(float newArmor);

    float GetHealth() const;
    float GetArmor() const;

    // Armor reduces incoming damage before health is clamped to zero.
    void TakeDamage(float damage);

    bool IsDead() const;

    void SetInvulnerable(bool value);
    bool IsInvulnerable() const;

    void Heal(float amount);
    void SettingMaxHealth(float value);
    float GetMaxHealth() const;


private:
    float maxHealth = 100.f;
    float health = 100.0f;
    float armor = 0.0f;
    bool isInvulnerable = false;
    // Prevents repeated death log spam while health remains zero.
    bool isDeadLogged = false;
};
} // namespace EngineGame
