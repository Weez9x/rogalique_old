#pragma once

#include "Component.h"
#include "TransformComponent.h"
#include "HealthComponent.h"

#include <SFML/Graphics.hpp>

namespace RogaliqueGame
{
	class HealthBarComponent : public EngineGame::Component
	{
	public:
		HealthBarComponent(EngineGame::GameObject* gameObject);

		void Update(float deltaTime) override;
		void Render() override;

		void SetMaxHealth(float value);
		void SetOffset(float x, float y);
		void SetSize(float width, float height);

	private:
		EngineGame::TransformComponent* transform = nullptr;
		EngineGame::HealthComponent* health = nullptr;

		float maxHealth = 100.0f;

		EngineGame::Vector2Df offset = { 0.f, -70.f };
		EngineGame::Vector2Df size = { 70.f, 8.f };

		sf::RectangleShape background;
		sf::RectangleShape fill;
	};
}