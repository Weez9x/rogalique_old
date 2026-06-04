#include "EnemyFollowComponent.h"
#include "GameStateManager.h"
#include "GameObject.h"
#include "Vector.h"
#include "Logger.h"
#include "HealthComponent.h"
#include "MeleeAttackComponent.h"
#include <cmath>
#include <cassert>

namespace RogaliqueGame
{
EnemyFollowComponent::EnemyFollowComponent(EngineGame::GameObject* gameObject) : Component(gameObject)
{
    rigidbody = gameObject->GetComponent<EngineGame::RigidbodyComponent>();
    transform = gameObject->GetComponent<EngineGame::TransformComponent>();
    animation = gameObject->GetComponent<EngineGame::AnimationComponent>();
    health = gameObject->GetComponent<EngineGame::HealthComponent>();
    spriteRenderer = gameObject->GetComponent<EngineGame::SpriteRendererComponent>();

    if (rigidbody == nullptr)
    {
        EngineGame::Logger::Instance()->Error("EnemyFollowComponent requires RigidbodyComponent");
    }

    if (transform == nullptr)
    {
        EngineGame::Logger::Instance()->Error("EnemyFollowComponent requires TransformComponent");
    }

    assert(rigidbody != nullptr && "EnemyFollowComponent requires RigidbodyComponent");
    assert(transform != nullptr && "EnemyFollowComponent requires TransformComponent");
}

void EnemyFollowComponent::SetTarget(EngineGame::GameObject* newTarget)
{
    targetObject = newTarget;

    if (targetObject == nullptr)
    {
        EngineGame::Logger::Instance()->Warning("EnemyFollowComponent target is null");
    }
}

void EnemyFollowComponent::Update(float deltaTime)
{
    if (!GameStateManager::IsPlaying())
    {
        if (rigidbody != nullptr)
        {
            rigidbody->SetLinearVelocity({0.f, 0.f});
        }

        return;
    }

    if (rigidbody == nullptr || transform == nullptr || targetObject == nullptr)
    {
        return;
    }

    if (health != nullptr && health->IsDead())
    {
        rigidbody->SetLinearVelocity({0.f, 0.f});

        if (animation != nullptr && !animation->IsCurrentAnimation("death"))
        {
            animation->Play("death");
        }

        return;
    }

    if (currentCooldown > 0.0f)
    {
        currentCooldown -= deltaTime;
    }

    if (isAttackActive)
    {
        attackTimer += deltaTime;

        if (!damageApplied && attackTimer >= damageMoment)
        {
            auto targetHealth = targetObject->GetComponent<EngineGame::HealthComponent>();

            if (targetHealth != nullptr && !targetHealth->IsDead())
            {
                auto attack = gameObject->GetComponent<MeleeAttackComponent>();

                if (attack != nullptr)
                {
                    attack->Attack(targetObject);
                    EngineGame::Logger::Instance()->Info("Enemy attack hit target");
                }
            }

            damageApplied = true;
        }

        if (attackTimer >= attackDuration)
        {
            isAttackActive = false;
        }

        return;
    }

    auto targetTransform = targetObject->GetComponent<EngineGame::TransformComponent>();

    if (targetTransform == nullptr)
    {
        EngineGame::Logger::Instance()->Warning("EnemyFollowComponent target has no TransformComponent");
        return;
    }

    auto targetHealth = targetObject->GetComponent<EngineGame::HealthComponent>();

    if (targetHealth != nullptr && targetHealth->IsDead())
    {
        rigidbody->SetLinearVelocity({0.f, 0.f});

        if (animation != nullptr)
        {
            animation->Play("idle");
        }

        return;
    }

    EngineGame::Vector2Df direction = {targetTransform->GetWorldPosition().x - transform->GetWorldPosition().x,
                                       targetTransform->GetWorldPosition().y - transform->GetWorldPosition().y};

    float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    if (spriteRenderer != nullptr)
    {
        if (direction.x < 0.0f)
        {
            spriteRenderer->FlipX(true);
        }
        else if (direction.x > 0.0f)
        {
            spriteRenderer->FlipX(false);
        }
    }

    if (distance > detectionRadius)
    {
        rigidbody->SetLinearVelocity({0.f, 0.f});

        if (animation != nullptr)
        {
            animation->Play("idle");
        }

        return;
    }

    if (distance < attackRange)
    {
        rigidbody->SetLinearVelocity({0.f, 0.f});

        if (currentCooldown <= 0.0f)
        {
            isAttackActive = true;
            damageApplied = false;
            attackTimer = 0.0f;
            currentCooldown = attackCooldown;

            if (animation != nullptr)
            {
                animation->Play("attack");
            }

            EngineGame::Logger::Instance()->Info("Enemy attack started");
        }

        return;
    }

    if (distance > 0.001f)
    {
        direction.x /= distance;
        direction.y /= distance;
    }

    if (animation != nullptr)
    {
        animation->Play("walk");
    }

    rigidbody->SetLinearVelocity(direction * moveSpeed);
}

void EnemyFollowComponent::Render() {}
} // namespace RogaliqueGame
