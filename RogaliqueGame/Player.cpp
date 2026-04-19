#include "Player.h"
#include "GameWorld.h"
#include "TransformComponent.h"
#include "SpriteColliderComponent.h"
#include "InputComponent.h"
#include "RigidbodyComponent.h"
#include "ResourceSystem.h"
#include "PlayerMovementComponent.h"

namespace RogaliqueGame
{
	Player::Player()
	{
		//create player
		gameObject = EngineGame::GameWorld::Instance()->CreateGameObject("Player");
		// add transform component
		auto transform = gameObject->GetComponent<EngineGame::TransformComponent>();
		transform->SetWorldPosition(400.f, 300.f);
		//add sprite component
		auto spriteRenderer = gameObject->AddComponent<EngineGame::SpriteRendererComponent>();
		spriteRenderer->SetTexture(*EngineGame::ResourceSystem::Instance()->GetTextureMapElementShared("player", 0));
		spriteRenderer->SetPixelSize(100, -100);
		//add input component
		gameObject->AddComponent<EngineGame::InputComponent>();
		//
		auto rigidbody = gameObject->AddComponent<EngineGame::RigidbodyComponent>();
		rigidbody->SetLinearDamping(6.0f);

		gameObject->AddComponent<EngineGame::SpriteColliderComponent>();

		gameObject->AddComponent<PlayerMovementComponent>();
	}

	EngineGame::GameObject* Player::GetGameObject() const
	{
		return gameObject;
	}
}