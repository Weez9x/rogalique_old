#pragma once

#include "Component.h"
#include "EnemySpawner.h"
#include "MeleeAttackComponent.h"
#include "TransformComponent.h"
#include "GameSettings.h"

namespace RogaliqueGame
{
class PlayerAttackComponent : public EngineGame::Component
{
public:
    PlayerAttackComponent(EngineGame::GameObject* gameObject);

    void Update(float deltaTime) override;
    void Render() override;

    void SetEnemySpawner(EnemySpawner* spawner);
    void TryDealDamage();

private:
    EngineGame::TransformComponent* transform = nullptr;
    MeleeAttackComponent* meleeAttack = nullptr;
    EnemySpawner* enemySpawner = nullptr;

    float attackRange = PLAYER_ATTACK_RANGE;
    float attackCooldown = PLAYER_ATTACK_COOLDOWN;
    float currentCooldown = 0.0f;

    bool isAttackActive = false;
    bool damageApplied = false;

    // Damage is applied mid-animation so the hit lines up with the sword swing.
    float attackDuration = PLAYER_ATTACK_DURATION;
    float attackTimer = 0.0f;

    float damageMoment = PLAYER_DAMAGE_MOMENT;
};
} // namespace RogaliqueGame
