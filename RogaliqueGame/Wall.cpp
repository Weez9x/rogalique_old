#include "Wall.h"
#include "GameWorld.h"
#include "TransformComponent.h"
#include "SpriteRendererComponent.h"
#include "RigidbodyComponent.h"
#include "SpriteColliderComponent.h"
#include "ResourceSystem.h"

namespace RogaliqueGame
{
	Wall::Wall(const EngineGame::Vector2Df& position, int width, int height)
	{
		gameObject = EngineGame::GameWorld::Instance()->CreateGameObject("Wall");

		auto transform = gameObject->GetComponent<EngineGame::TransformComponent>();
		transform->SetWorldPosition(position.x, position.y);

		auto spriteRenderer = gameObject->AddComponent<EngineGame::SpriteRendererComponent>();
		spriteRenderer->SetTexture(*EngineGame::ResourceSystem::Instance()->GetTextureMapElementShared("walls", 0));
		spriteRenderer->SetPixelSize(128, 128);

		auto rigidbody = gameObject->AddComponent<EngineGame::RigidbodyComponent>();
		rigidbody->SetKinematic(true);

		gameObject->AddComponent<EngineGame::SpriteColliderComponent>();
	}

	EngineGame::GameObject* Wall::GetGameObject() const
	{
		return gameObject;
	}
}