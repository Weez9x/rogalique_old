#include "EnemyFollowComponent.h"
#include "GameObject.h"
#include "Vector.h"
#include <cmath>

namespace RogaliqueGame
{
	EnemyFollowComponent::EnemyFollowComponent(EngineGame::GameObject* gameObject)
		: Component(gameObject)
	{
		rigidbody = gameObject->GetComponent<EngineGame::RigidbodyComponent>();
		transform = gameObject->GetComponent<EngineGame::TransformComponent>();
	}

	void EnemyFollowComponent::SetTarget(EngineGame::GameObject* newTarget)
	{
		targetObject = newTarget;
	}

	void EnemyFollowComponent::Update(float deltaTime)
	{
		if (rigidbody == nullptr || transform == nullptr || targetObject == nullptr)
		{
			return;
		}

		auto targetTransform = targetObject->GetComponent<EngineGame::TransformComponent>();
		if (targetTransform == nullptr)
		{
			return;
		}

		EngineGame::Vector2Df direction =
		{
			targetTransform->GetWorldPosition().x - transform->GetWorldPosition().x,
			targetTransform->GetWorldPosition().y - transform->GetWorldPosition().y
		};

		float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

		if (distance > detectionRadius)
		{
			rigidbody->SetLinearVelocity({ 0.f, 0.f });
			return;
		}

		if (distance > 0.001f)
		{
			direction.x /= distance;
			direction.y /= distance;
		}

		rigidbody->SetLinearVelocity(direction * (moveSpeed - 1));
	}

	void EnemyFollowComponent::Render()
	{
	}
}