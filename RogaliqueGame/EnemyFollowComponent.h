#pragma once
#include "Component.h"
#include "RigidbodyComponent.h"
#include "TransformComponent.h"
#include "AnimationComponent.h"
#include "HealthComponent.h"
#include "SpriteRendererComponent.h"

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

    float moveSpeed = 1.5f;
    float detectionRadius = 250.0f;
    float attackCooldown = 1.0f;
    float currentCooldown = 0.0f;
    float attackRange = 95.0f;

    EngineGame::AnimationComponent* animation = nullptr;
    EngineGame::HealthComponent* health = nullptr;
    EngineGame::SpriteRendererComponent* spriteRenderer = nullptr;

    bool isAttackActive = false;
    bool damageApplied = false;

    float attackDuration = 0.45f;
    float attackTimer = 0.0f;
    float damageMoment = 0.22f;
};
} // namespace RogaliqueGame