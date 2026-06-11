#include "Player.h"
#include "GameWorld.h"
#include "TransformComponent.h"
#include "SpriteRendererComponent.h"
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
#include "CameraComponent.h"
#include "RenderSystem.h"
#include "GameSettings.h"
#include "PlayerLivesComponent.h"
#include "PlayerTagComponent.h"
#include "CameraShakeComponent.h"
#include "ParticleEmitterComponent.h"
#include "SoundComponent.h"
#include "FootstepSoundComponent.h"
#include "AttackSoundComponent.h"
#include "DamageSoundComponent.h"

namespace RogaliqueGame
{
Player::Player()
{
    gameObject = EngineGame::GameWorld::Instance()->CreateGameObject("Player");
    gameObject->AddComponent<PlayerTagComponent>();

    // The player is assembled as a prefab from engine components plus game-specific behavior.
    auto transform = gameObject->GetComponent<EngineGame::TransformComponent>();
    transform->SetWorldPosition(PLAYER_START_X, PLAYER_START_Y);

    auto spriteRenderer = gameObject->AddComponent<EngineGame::SpriteRendererComponent>();
    spriteRenderer->SetTexture(*EngineGame::ResourceSystem::Instance()->GetTextureMapElementShared("player", 0));
    spriteRenderer->SetPixelSize(CHARACTER_SPRITE_SIZE, CHARACTER_SPRITE_SIZE);
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
    gameObject->AddComponent<PlayerLivesComponent>();
    health->SetHealth(PLAYER_MAX_HEALTH);
    health->SetArmor(PLAYER_ARMOR);
    gameObject->AddComponent<PlayerStatsUIComponent>();
    EngineGame::Logger::Instance()->Info("Player health initialized");

    // Respawn keeps the same player object alive until lives are exhausted.
    auto respawn = gameObject->AddComponent<RespawnComponent>();
    respawn->SetSpawnPosition({PLAYER_START_X, PLAYER_START_Y});
    respawn->SetMaxHealth(PLAYER_MAX_HEALTH);

    auto attack = gameObject->AddComponent<MeleeAttackComponent>();
    attack->SetDamage(PLAYER_DAMAGE);

    // PlayerAttackComponent handles input and delegates actual damage to MeleeAttackComponent.
    gameObject->AddComponent<PlayerAttackComponent>();

    auto collider = gameObject->AddComponent<EngineGame::BoxColliderComponent>();
    collider->SetSize(70.f, 70.f);
    collider->SetOffset(0.f, 0.f);

    gameObject->AddComponent<PlayerMovementComponent>();

    auto camera = gameObject->AddComponent<EngineGame::CameraComponent>();
    camera->SetWindow(&EngineGame::RenderSystem::Instance()->GetMainWindow());
    camera->SetBaseResolution(SCREEN_WIDTH, SCREEN_HEIGHT);
    camera->ZoomBy(1.0f);
    
    gameObject->AddComponent<EngineGame::CameraShakeComponent>();

    auto particles = gameObject->AddComponent<EngineGame::ParticleEmitterComponent>();
    particles->SetDamageColor(sf::Color::Red);

    auto attackSound = gameObject->AddComponent<AttackSoundComponent>();
    attackSound->AddSound(EngineGame::ResourceSystem::Instance()->GetSoundShared("player_attack_1"));
    attackSound->AddSound(EngineGame::ResourceSystem::Instance()->GetSoundShared("player_attack_2"));
    attackSound->AddSound(EngineGame::ResourceSystem::Instance()->GetSoundShared("player_attack_3"));
    attackSound->SetVolume(50.f);

    auto footstepSound = gameObject->AddComponent<FootstepSoundComponent>();
    footstepSound->AddSound(EngineGame::ResourceSystem::Instance()->GetSoundShared("player_step_1"));
    footstepSound->AddSound(EngineGame::ResourceSystem::Instance()->GetSoundShared("player_step_2"));
    footstepSound->SetVolume(60.f);

    auto damageSound = gameObject->AddComponent<DamageSoundComponent>();
    damageSound->AddSound(EngineGame::ResourceSystem::Instance()->GetSoundShared("player_damage"));
}

void Player::SetEnemySpawner(EnemySpawner* spawner)
{
    auto attackComponent = gameObject->GetComponent<PlayerAttackComponent>();

    if (attackComponent == nullptr)
    {
        EngineGame::Logger::Instance()->Warning("Player has no PlayerAttackComponent");
        return;
    }

    attackComponent->SetEnemySpawner(spawner);
}
} // namespace RogaliqueGame
