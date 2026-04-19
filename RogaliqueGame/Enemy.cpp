#include "Enemy.h"
#include "GameWorld.h"
#include "TransformComponent.h"
#include "SpriteRendererComponent.h"
#include "RigidbodyComponent.h"
#include "SpriteColliderComponent.h"
#include "ResourceSystem.h"
#include "EnemyFollowComponent.h"

namespace RogaliqueGame
{
	Enemy::Enemy(EngineGame::GameObject* playerObject)
	{
		gameObject = EngineGame::GameWorld::Instance()->CreateGameObject("Enemy");

		auto transform = gameObject->GetComponent<EngineGame::TransformComponent>();
		transform->SetWorldPosition(600.f, 300.f);

		auto spriteRenderer = gameObject->AddComponent<EngineGame::SpriteRendererComponent>();
		spriteRenderer->SetTexture(*EngineGame::ResourceSystem::Instance()->GetTextureShared("test"));
		spriteRenderer->SetPixelSize(80, 80);

		auto rigidbody = gameObject->AddComponent<EngineGame::RigidbodyComponent>();
		rigidbody->SetLinearDamping(6.0f);

		gameObject->AddComponent<EngineGame::SpriteColliderComponent>();

		auto followComponent = gameObject->AddComponent<EnemyFollowComponent>();
		followComponent->SetTarget(playerObject);
	}

	EngineGame::GameObject* Enemy::GetGameObject() const
	{
		return gameObject;
	}
}