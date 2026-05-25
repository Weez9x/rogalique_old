#include "AnimationComponent.h"
#include "PlayerAttackComponent.h"
#include "GameObject.h"
#include "Logger.h"
#include "HealthComponent.h"
#include <SFML/Window/Keyboard.hpp>
#include <cmath>
#include <cassert>

namespace RogaliqueGame
{
PlayerAttackComponent::PlayerAttackComponent(EngineGame::GameObject* gameObject) : Component(gameObject)
{
    transform = gameObject->GetComponent<EngineGame::TransformComponent>();
    meleeAttack = gameObject->GetComponent<MeleeAttackComponent>();

    if (transform == nullptr)
    {
        EngineGame::Logger::Instance()->Error("PlayerAttackComponent requires TransformComponent");
    }

    if (meleeAttack == nullptr)
    {
        EngineGame::Logger::Instance()->Error("PlayerAttackComponent requires MeleeAttackComponent");
    }

    assert(transform != nullptr && "PlayerAttackComponent requires TransformComponent");
    assert(meleeAttack != nullptr && "PlayerAttackComponent requires MeleeAttackComponent");
}

void PlayerAttackComponent::SetTarget(EngineGame::GameObject* newTarget)
{
    target = newTarget;

    if (target == nullptr)
    {
        EngineGame::Logger::Instance()->Warning("PlayerAttackComponent target is null");
    }
}

void PlayerAttackComponent::TryDealDamage()
{
    if (target == nullptr)
    {
        return;
    }

    auto targetTransform = target->GetComponent<EngineGame::TransformComponent>();
    if (targetTransform == nullptr)
    {
        EngineGame::Logger::Instance()->Warning("PlayerAttackComponent target has no TransformComponent");
        return;
    }

    auto targetHealth = target->GetComponent<EngineGame::HealthComponent>();
    if (targetHealth != nullptr && targetHealth->IsDead())
    {
        return;
    }

    EngineGame::Vector2Df direction = {targetTransform->GetWorldPosition().x - transform->GetWorldPosition().x,
                                       targetTransform->GetWorldPosition().y - transform->GetWorldPosition().y};

    float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    if (distance > attackRange)
    {
        EngineGame::Logger::Instance()->Info("Player attack missed: target out of range");
        return;
    }
    meleeAttack->Attack(target);

    EngineGame::Logger::Instance()->Info("Player attack hit target");
}

void PlayerAttackComponent::Update(float deltaTime)
{
    if (transform == nullptr || meleeAttack == nullptr || target == nullptr)
    {
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
            TryDealDamage();
            damageApplied = true;
        }

        if (attackTimer >= attackDuration)
        {
            isAttackActive = false;
        }

        return;
    }

    auto animation = gameObject->GetComponent<EngineGame::AnimationComponent>();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && currentCooldown <= 0.0f)
    {
        isAttackActive = true;
        damageApplied = false;
        attackTimer = 0.0f;
        currentCooldown = attackCooldown;

        if (animation != nullptr)
        {
            animation->Play("attack");
        }

        EngineGame::Logger::Instance()->Info("Player attack started");
    }

    return;
}

void PlayerAttackComponent::Render() {}
} // namespace RogaliqueGame