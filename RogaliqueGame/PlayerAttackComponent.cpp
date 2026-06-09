#include "PlayerAttackComponent.h"

#include "AnimationComponent.h"
#include "GameObject.h"
#include "Logger.h"
#include "GameStateManager.h"
#include "CameraShakeComponent.h"

#include <SFML/Window/Keyboard.hpp>
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

void PlayerAttackComponent::SetEnemySpawner(EnemySpawner* spawner)
{
    enemySpawner = spawner;

    if (enemySpawner == nullptr)
    {
        EngineGame::Logger::Instance()->Warning("PlayerAttackComponent enemySpawner is null");
    }
}

void PlayerAttackComponent::TryDealDamage()
{
    if (enemySpawner == nullptr)
    {
        EngineGame::Logger::Instance()->Info("Player attack missed: no enemy spawner");
        return;
    }

    EngineGame::GameObject* target = enemySpawner->FindClosestEnemy(transform->GetWorldPosition(), attackRange);

    if (target == nullptr)
    {
        EngineGame::Logger::Instance()->Info("Player attack missed: no enemy in range");
        return;
    }
    meleeAttack->Attack(target);
    auto cameraShake = gameObject->GetComponent<EngineGame::CameraShakeComponent>();
    if (cameraShake != nullptr)
    {
        cameraShake->Shake(0.5f, 3.f);
    }

    EngineGame::Logger::Instance()->Info("Player attack hit closest enemy");
}

void PlayerAttackComponent::Update(float deltaTime)
{
    if (!GameStateManager::IsPlaying())
    {
        return;
    }
    if (transform == nullptr || meleeAttack == nullptr)
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

        // Apply damage once at the animation impact frame, not every update during the swing.
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
        // The attack stays active for several frames so animation and damage timing can diverge.
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
}

void PlayerAttackComponent::Render() {}
} // namespace RogaliqueGame
