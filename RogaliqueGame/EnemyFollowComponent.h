#pragma once
#include "Component.h"
#include "RigidbodyComponent.h"
#include "TransformComponent.h"

namespace RogaliqueGame
{
	class EnemyFollowComponent : public EngineGame::Component
	{
	public:
		EnemyFollowComponent(EngineGame::GameObject* gameObject);

		void Update(float deltaTime) override;
		void Render() override;

		void SetTarget(EngineGame::GameObject* newTarget);

	private:
		EngineGame::RigidbodyComponent* rigidbody = nullptr;
		EngineGame::TransformComponent* transform = nullptr;
		EngineGame::GameObject* targetObject = nullptr;

		float moveSpeed = 2.5f;
		float detectionRadius = 500.0f;
	};
}