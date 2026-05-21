#include "RespawnComponent.h"

#include "GameObject.h"
#include "Logger.h"

#include <cassert>

namespace RogaliqueGame
{
	RespawnComponent::RespawnComponent(EngineGame::GameObject* gameObject)
		: Component(gameObject)
	{
		transform = gameObject->GetComponent<EngineGame::TransformComponent>();
		rigidbody = gameObject->GetComponent<EngineGame::RigidbodyComponent>();
		health = gameObject->GetComponent<EngineGame::HealthComponent>();
		animation = gameObject->GetComponent<EngineGame::AnimationComponent>();
		spriteRenderer = gameObject->GetComponent<EngineGame::SpriteRendererComponent>();

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

	void RespawnComponent::Render()
	{
	}

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
		isWaitingRespawn = true;
		respawnTimer = 0.0f;

		if (rigidbody != nullptr)
		{
			rigidbody->SetLinearVelocity({ 0.f, 0.f });
		}

		if (animation != nullptr)
		{
			animation->Play("death");
		}

		EngineGame::Logger::Instance()->Info(gameObject->GetName() + " will respawn soon.");
	}

	void RespawnComponent::Respawn()
	{
		isWaitingRespawn = false;

		transform->SetWorldPosition(spawnPosition);
		health->SetHealth(maxHealth);
		health->SetInvulnerable(true);

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
}