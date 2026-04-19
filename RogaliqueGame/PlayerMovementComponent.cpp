#include "PlayerMovementComponent.h"
#include "GameObject.h"
#include "Vector.h"
#include <cmath>

namespace RogaliqueGame
{
	PlayerMovementComponent::PlayerMovementComponent(EngineGame::GameObject* gameObject)
		: Component(gameObject)
	{
		input = gameObject->GetComponent<EngineGame::InputComponent>();
		rigidbody = gameObject->GetComponent<EngineGame::RigidbodyComponent>();
	}

	void PlayerMovementComponent::Update(float deltaTime)
	{
		if (input == nullptr || rigidbody == nullptr)
		{
			return;
		}

		EngineGame::Vector2Df direction =
		{
			input->GetHorizontalAxis(),
			input->GetVerticalAxis()
		};

		if (direction.x != 0.0f || direction.y != 0.0f)
		{
			float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
			direction.x /= length;
			direction.y /= length;
		}

		rigidbody->SetLinearVelocity(direction * moveSpeed);
	}

	void PlayerMovementComponent::Render()
	{
	}
}