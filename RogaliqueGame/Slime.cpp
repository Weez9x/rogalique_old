#include "Slime.h"
#include "GameWorld.h"
#include "TransformComponent.h"
#include "SpriteRendererComponent.h"
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
Slime::Slime(EngineGame::GameObject* playerObject, const EngineGame::Vector2Df& spawnPosition)
{
    gameObject = EngineGame::GameWorld::Instance()->CreateGameObject("Slime");

    // Slime uses the shared enemy behavior stack with lighter stats.
    auto transform = gameObject->GetComponent<EngineGame::TransformComponent>();
    transform->SetWorldPosition(spawnPosition.x, spawnPosition.y);

    auto spriteRenderer = gameObject->AddComponent<EngineGame::SpriteRendererComponent>();
    spriteRenderer->SetTexture(*EngineGame::ResourceSystem::Instance()->GetTextureMapElementShared("slime", 0));
    spriteRenderer->SetPixelSize(CHARACTER_SPRITE_SIZE, CHARACTER_SPRITE_SIZE);
    spriteRenderer->FlipY(true);

    auto animation = gameObject->AddComponent<EngineGame::AnimationComponent>();
    animation->AddAnimation("idle", "slime", {0, 1, 2, 3, 4, 5}, 0.12f, true);
    animation->AddAnimation("walk", "slime", {10, 11, 12, 13, 14, 15, 16, 17}, 0.06f, true);
    animation->AddAnimation("attack", "slime", {40, 41, 42, 43, 44, 45, 46, 47}, 0.04f, false);
    animation->AddAnimation("death", "slime", {70, 71, 72, 73, 74, 75, 76, 77, 78, 79}, 0.12f, false);
    animation->Play("idle");

    auto rigidbody = gameObject->AddComponent<EngineGame::RigidbodyComponent>();
    rigidbody->SetLinearDamping(6.0f);

    auto health = gameObject->AddComponent<EngineGame::HealthComponent>();
    health->SetHealth(SLIME_MAX_HEALTH);
    health->SetArmor(SLIME_ARMOR);
    EngineGame::Logger::Instance()->Info("Enemy health initialized");
    auto healthBar = gameObject->AddComponent<HealthBarComponent>();
    healthBar->SetMaxHealth(SLIME_MAX_HEALTH);
    healthBar->SetOffset(0.f, -30.f);
    healthBar->SetSize(70.f, 8.f);
    auto respawn = gameObject->AddComponent<RespawnComponent>();
    respawn->SetSpawnPosition(spawnPosition);
    respawn->SetMaxHealth(SLIME_MAX_HEALTH);

    auto attack = gameObject->AddComponent<MeleeAttackComponent>();
    attack->SetDamage(SLIME_DAMAGE);

    auto collider = gameObject->AddComponent<EngineGame::BoxColliderComponent>();
    collider->SetSize(70.f, 50.f);
    collider->SetOffset(0.f, 25.f);

    auto followComponent = gameObject->AddComponent<EnemyFollowComponent>();
    followComponent->SetTarget(playerObject);
}

} // namespace RogaliqueGame
