#include "Player.h"
#include "GameWorld.h"
#include "TransformComponent.h"
#include "SpriteRendererComponent.h"
#include "SpriteColliderComponent.h"
#include "InputComponent.h"
#include "RigidbodyComponent.h"
#include "ResourceSystem.h"
#include "PlayerMovementComponent.h"
#include "HealthComponent.h"
#include "Logger.h"
#include "MeleeAttackComponent.h"
#include "PlayerAttackComponent.h"
#include "BoxColliderComponent.h"
#include "AnimationComponent.h"
#include "PlayerStatsUIComponent.h"
#include "RespawnComponent.h"

namespace RogaliqueGame
{
Player::Player()
{
    gameObject = EngineGame::GameWorld::Instance()->CreateGameObject("Player");

    auto transform = gameObject->GetComponent<EngineGame::TransformComponent>();
    transform->SetWorldPosition(400.f, 300.f);

    auto spriteRenderer = gameObject->AddComponent<EngineGame::SpriteRendererComponent>();
    spriteRenderer->SetTexture(*EngineGame::ResourceSystem::Instance()->GetTextureMapElementShared("player", 0));
    spriteRenderer->SetPixelSize(576.f, 576.f);
    spriteRenderer->FlipY(true);

    auto animation = gameObject->AddComponent<EngineGame::AnimationComponent>();

    animation->AddAnimation("walk", "player", {10, 11, 12, 13, 14, 15, 16, 17}, 0.06f, true);
    animation->AddAnimation("idle", "player", {0, 1, 2, 3, 4, 5}, 0.12f, true);
    animation->AddAnimation("attack", "player", {40, 41, 42, 43, 44, 45, 46, 47}, 0.04f, false);
    animation->AddAnimation("death", "player", {70, 71, 72, 73, 74, 75, 76, 77, 78, 79}, 0.12f, false);

    animation->Play("idle");

    gameObject->AddComponent<EngineGame::InputComponent>();

    auto rigidbody = gameObject->AddComponent<EngineGame::RigidbodyComponent>();
    rigidbody->SetLinearDamping(6.0f);

    auto health = gameObject->AddComponent<EngineGame::HealthComponent>();
    health->SetHealth(100.0f);
    health->SetArmor(5.0f);
    gameObject->AddComponent<PlayerStatsUIComponent>();
    EngineGame::Logger::Instance()->Info("Player health initialized");
    auto respawn = gameObject->AddComponent<RespawnComponent>();
    respawn->SetSpawnPosition({400.f, 300.f});
    respawn->SetMaxHealth(100.0f);

    auto attack = gameObject->AddComponent<MeleeAttackComponent>();
    attack->SetDamage(20.0f);

    gameObject->AddComponent<PlayerAttackComponent>();

    auto collider = gameObject->AddComponent<EngineGame::BoxColliderComponent>();
    collider->SetSize(70.f, 70.f);
    collider->SetOffset(0.f, 0.f);

    gameObject->AddComponent<PlayerMovementComponent>();
}

EngineGame::GameObject* Player::GetGameObject() const
{
    return gameObject;
}
void Player::SetAttackTarget(EngineGame::GameObject* target)
{
    auto attackComponent = gameObject->GetComponent<PlayerAttackComponent>();

    if (attackComponent == nullptr)
    {
        EngineGame::Logger::Instance()->Warning("Player has no PlayerAttackComponent");
        return;
    }

    attackComponent->SetTarget(target);
}
} // namespace RogaliqueGame