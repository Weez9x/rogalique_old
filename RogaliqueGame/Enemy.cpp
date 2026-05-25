#include "Enemy.h"
#include "GameWorld.h"
#include "TransformComponent.h"
#include "SpriteRendererComponent.h"
#include "SpriteColliderComponent.h"
#include "AnimationComponent.h"
#include "RigidbodyComponent.h"
#include "ResourceSystem.h"
#include "EnemyFollowComponent.h"
#include "HealthComponent.h"
#include "Logger.h"
#include "MeleeAttackComponent.h"
#include "BoxColliderComponent.h"
#include "RespawnComponent.h"
#include "HealthBarComponent.h"

namespace RogaliqueGame
{
Enemy::Enemy(EngineGame::GameObject* playerObject)
{
    gameObject = EngineGame::GameWorld::Instance()->CreateGameObject("Enemy");

    auto transform = gameObject->GetComponent<EngineGame::TransformComponent>();
    transform->SetWorldPosition(600.f, 300.f);

    auto spriteRenderer = gameObject->AddComponent<EngineGame::SpriteRendererComponent>();
    spriteRenderer->SetTexture(*EngineGame::ResourceSystem::Instance()->GetTextureMapElementShared("enemy", 0));
    spriteRenderer->SetPixelSize(576.f, 576.f);
    spriteRenderer->FlipY(true);

    auto animation = gameObject->AddComponent<EngineGame::AnimationComponent>();
    animation->AddAnimation("idle", "enemy", {0, 1, 2, 3, 4, 5}, 0.12f, true);
    animation->AddAnimation("walk", "enemy", {10, 11, 12, 13, 14, 15, 16, 17}, 0.06f, true);
    animation->AddAnimation("attack", "enemy", {40, 41, 42, 43, 44, 45, 46, 47}, 0.04f, false);
    animation->AddAnimation("death", "enemy", {70, 71, 72, 73, 74, 75, 76, 77, 78, 79}, 0.12f, false);
    animation->Play("idle");

    auto rigidbody = gameObject->AddComponent<EngineGame::RigidbodyComponent>();
    rigidbody->SetLinearDamping(6.0f);

    auto health = gameObject->AddComponent<EngineGame::HealthComponent>();
    health->SetHealth(50.0f);
    health->SetArmor(2.0f);
    EngineGame::Logger::Instance()->Info("Enemy health initialized");
    auto healthBar = gameObject->AddComponent<HealthBarComponent>();
    healthBar->SetMaxHealth(50.0f);
    healthBar->SetOffset(0.f, -30.f);
    healthBar->SetSize(70.f, 8.f);
    auto respawn = gameObject->AddComponent<RespawnComponent>();
    respawn->SetSpawnPosition({600.f, 300.f});
    respawn->SetMaxHealth(50.0f);

    auto attack = gameObject->AddComponent<MeleeAttackComponent>();
    attack->SetDamage(10.0f);

    auto collider = gameObject->AddComponent<EngineGame::BoxColliderComponent>();
    collider->SetSize(70.f, 50.f);
    collider->SetOffset(0.f, 25.f);

    auto followComponent = gameObject->AddComponent<EnemyFollowComponent>();
    followComponent->SetTarget(playerObject);
}

EngineGame::GameObject* Enemy::GetGameObject() const
{
    return gameObject;
}
} // namespace RogaliqueGame