#pragma once
#include "Component.h"
#include "RigidbodyComponent.h"
#include "TransformComponent.h"
#include "AnimationComponent.h"
#include "HealthComponent.h"
#include "SpriteRendererComponent.h"
#include "GameSettings.h"

namespace RogaliqueGame
{
class EnemyFollowComponent : public EngineGame::Component
{
public:
    EnemyFollowComponent(EngineGame::GameObject* gameObject);

    void Update(float deltaTime) override;
    void Render() override;

    void SetTarget(EngineGame::GameObject* newTarget);

private:
    EngineGame::RigidbodyComponent* rigidbody = nullptr;
    EngineGame::TransformComponent* transform = nullptr;
    EngineGame::GameObject* targetObject = nullptr;

    float moveSpeed = ENEMY_MOVE_SPEED;
    float detectionRadius = ENEMY_DETECTION_RADIUS;
    float attackCooldown = ENEMY_ATTACK_COOLDOWN;
    float currentCooldown = 0.0f;
    float attackRange = ENEMY_ATTACK_RANGE;

    EngineGame::AnimationComponent* animation = nullptr;
    EngineGame::HealthComponent* health = nullptr;
    EngineGame::SpriteRendererComponent* spriteRenderer = nullptr;

    bool isAttackActive = false;
    bool damageApplied = false;

    float attackDuration = ENEMY_ATTACK_DURATION;
    float attackTimer = 0.0f;
    float damageMoment = ENEMY_DAMAGE_MOMENT;
};
} // namespace RogaliqueGame