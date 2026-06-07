#include "RespawnComponent.h"

#include "GameObject.h"
#include "Logger.h"
#include "PlayerLivesComponent.h"
#include "GameProgress.h"
#include "GameStateManager.h"
#include "EnemyTagComponent.h"

#include <cassert>
#include <string>

namespace RogaliqueGame
{
bool RespawnComponent::IsEnemyObject() const
{
    const std::string name = gameObject->GetName();

    return gameObject->GetComponent<EnemyTagComponent>() != nullptr;
}
RespawnComponent::RespawnComponent(EngineGame::GameObject* gameObject) : Component(gameObject)
{
    transform = gameObject->GetComponent<EngineGame::TransformComponent>();
    rigidbody = gameObject->GetComponent<EngineGame::RigidbodyComponent>();
    health = gameObject->GetComponent<EngineGame::HealthComponent>();
    animation = gameObject->GetComponent<EngineGame::AnimationComponent>();
    spriteRenderer = gameObject->GetComponent<EngineGame::SpriteRendererComponent>();
    collider = gameObject->GetComponent<EngineGame::ColliderComponent>();

    if (transform == nullptr)
    {
        EngineGame::Logger::Instance()->Error("RespawnComponent requires TransformComponent");
    }

    if (health == nullptr)
    {
        EngineGame::Logger::Instance()->Error("RespawnComponent requires HealthComponent");
    }

    assert(transform != nullptr && "RespawnComponent requires TransformComponent");
    assert(health != nullptr && "RespawnComponent requires HealthComponent");

    if (transform != nullptr)
    {
        spawnPosition = transform->GetWorldPosition();
    }
}

void RespawnComponent::Update(float deltaTime)
{
    if (!GameStateManager::IsPlaying())
    {
        return;
    }

    if (transform == nullptr || health == nullptr)
    {
        return;
    }

    if (isInvulnerable)
    {
        UpdateInvulnerability(deltaTime);
    }

    if (health->IsDead() && !isWaitingRespawn)
    {
        if (!killCounted && IsEnemyObject())
        {
            // Count the kill before starting respawn; otherwise a dead enemy could be counted every frame.
            GameProgress::CurrentKills++;

            EngineGame::Logger::Instance()->Info("Enemy killed. Kills: " + std::to_string(GameProgress::CurrentKills) +
                                                 "/" + std::to_string(GameProgress::RequiredKills));

            killCounted = true;
        }

        auto lives = gameObject->GetComponent<PlayerLivesComponent>();

        if (lives != nullptr && !lives->HasLives())
        {
            // The GameOver screen keeps the dead player on screen instead of respawning them.
            EngineGame::Logger::Instance()->Error(gameObject->GetName() + " cannot respawn. Game over.");
            return;
        }

        StartRespawnWaiting();
        return;
    }

    if (isWaitingRespawn)
    {
        respawnTimer += deltaTime;

        if (respawnTimer >= respawnDelay)
        {
            Respawn();
        }

        return;
    }
}

void RespawnComponent::Render() {}

void RespawnComponent::SetSpawnPosition(const EngineGame::Vector2Df& position)
{
    spawnPosition = position;
}

void RespawnComponent::SetMaxHealth(float value)
{
    if (value <= 0.0f)
    {
        EngineGame::Logger::Instance()->Warning("RespawnComponent max health must be positive.");
        return;
    }

    maxHealth = value;
}

void RespawnComponent::StartRespawnWaiting()
{
    if (collider == nullptr)
    {
        collider = gameObject->GetComponent<EngineGame::ColliderComponent>();
    }

    if (collider != nullptr)
    {
        collider->SetEnabled(false);
        EngineGame::Logger::Instance()->Info(gameObject->GetName() + " collider disabled.");
    }
    else
    {
        EngineGame::Logger::Instance()->Warning(gameObject->GetName() + " has no collider in RespawnComponent.");
    }

    isWaitingRespawn = true;
    respawnTimer = 0.0f;

    if (rigidbody != nullptr)
    {
        rigidbody->SetLinearVelocity({0.f, 0.f});
    }

    if (animation != nullptr)
    {
        animation->Play("death");
    }

    EngineGame::Logger::Instance()->Info(gameObject->GetName() + " will respawn soon.");
}

void RespawnComponent::Respawn()
{
    if (collider == nullptr)
    {
        collider = gameObject->GetComponent<EngineGame::ColliderComponent>();
    }

    if (collider != nullptr)
    {
        collider->SetEnabled(true);
        EngineGame::Logger::Instance()->Info(gameObject->GetName() + " collider enabled.");
    }

    isWaitingRespawn = false;

    if (respawnPositionProvider)
    {
        // Enemies use a fresh random floor tile; the player keeps the fixed spawn point.
        spawnPosition = respawnPositionProvider();
    }

    transform->SetWorldPosition(spawnPosition);
    health->SetHealth(maxHealth);
    health->SetInvulnerable(true);
    killCounted = false;

    isInvulnerable = true;
    invulnerabilityTimer = 0.0f;
    blinkTimer = 0.0f;

    if (spriteRenderer != nullptr)
    {
        spriteRenderer->SetVisible(true);
    }

    if (animation != nullptr)
    {
        animation->Play("idle");
    }

    EngineGame::Logger::Instance()->Info(gameObject->GetName() + " respawned.");
}

void RespawnComponent::UpdateInvulnerability(float deltaTime)
{
    invulnerabilityTimer += deltaTime;
    blinkTimer += deltaTime;

    if (spriteRenderer != nullptr && blinkTimer >= blinkInterval)
    {
        // Blinking gives visible feedback while the object is invulnerable after respawn.
        blinkTimer = 0.0f;
        spriteRenderer->SetVisible(!spriteRenderer->IsVisible());
    }

    if (invulnerabilityTimer >= invulnerabilityTime)
    {
        isInvulnerable = false;
        health->SetInvulnerable(false);

        if (spriteRenderer != nullptr)
        {
            spriteRenderer->SetVisible(true);
        }
    }
}
void RespawnComponent::SetRespawnPositionProvider(std::function<EngineGame::Vector2Df()> provider)
{
    respawnPositionProvider = provider;
}
} // namespace RogaliqueGame
