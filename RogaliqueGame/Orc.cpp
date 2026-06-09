#include "Orc.h"
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
#include "EnemyTagComponent.h"
#include "ParticleEmitterComponent.h"

namespace RogaliqueGame
{
Orc::Orc(EngineGame::GameObject* playerObject, const EngineGame::Vector2Df& spawnPosition)
{
    gameObject = EngineGame::GameWorld::Instance()->CreateGameObject("Orc");
    gameObject->AddComponent<EnemyTagComponent>();

    // Orc uses the same enemy behavior stack as slime, but with heavier stats.
    auto transform = gameObject->GetComponent<EngineGame::TransformComponent>();
    transform->SetWorldPosition(spawnPosition.x, spawnPosition.y);

    auto spriteRenderer = gameObject->AddComponent<EngineGame::SpriteRendererComponent>();
    spriteRenderer->SetTexture(*EngineGame::ResourceSystem::Instance()->GetTextureMapElementShared("orc", 0));
    spriteRenderer->SetPixelSize(CHARACTER_SPRITE_SIZE, CHARACTER_SPRITE_SIZE);
    spriteRenderer->FlipY(true);

    auto animation = gameObject->AddComponent<EngineGame::AnimationComponent>();
    animation->AddAnimation("idle", "orc", {0, 1, 2, 3, 4, 5}, 0.12f, true);
    animation->AddAnimation("walk", "orc", {8, 9, 10, 11, 12, 13, 14, 15}, 0.06f, true);
    animation->AddAnimation("attack", "orc", {16, 17, 18, 19, 20, 21}, 0.08f, false);
    animation->AddAnimation("death", "orc", {40, 41, 42, 43}, 0.12f, false);
    animation->Play("idle");

    auto rigidbody = gameObject->AddComponent<EngineGame::RigidbodyComponent>();
    rigidbody->SetLinearDamping(6.0f);

    auto health = gameObject->AddComponent<EngineGame::HealthComponent>();
    health->SetHealth(ORC_MAX_HEALTH);
    health->SetArmor(ORC_ARMOR);
    EngineGame::Logger::Instance()->Info("Enemy health initialized");
    auto healthBar = gameObject->AddComponent<HealthBarComponent>();
    healthBar->SetMaxHealth(ORC_MAX_HEALTH);
    healthBar->SetOffset(0.f, -70.f);
    healthBar->SetSize(70.f, 8.f);
    auto respawn = gameObject->AddComponent<RespawnComponent>();
    respawn->SetSpawnPosition(spawnPosition);
    respawn->SetMaxHealth(ORC_MAX_HEALTH);

    auto attack = gameObject->AddComponent<MeleeAttackComponent>();
    attack->SetDamage(ORC_DAMAGE);

    auto collider = gameObject->AddComponent<EngineGame::BoxColliderComponent>();
    collider->SetSize(60.f, 70.f);
    collider->SetOffset(0.f, 0.f);

    auto followComponent = gameObject->AddComponent<EnemyFollowComponent>();
    followComponent->SetTarget(playerObject);

    auto particles = gameObject->AddComponent<EngineGame::ParticleEmitterComponent>();
    particles->SetDamageColor(sf::Color(90, 0, 0));
}

} // namespace RogaliqueGame
