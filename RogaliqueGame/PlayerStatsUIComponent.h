#pragma once

#include "Component.h"
#include "HealthComponent.h"
#include <SFML/Graphics.hpp>

namespace RogaliqueGame
{
	class PlayerStatsUIComponent : public EngineGame::Component
	{
	public:
		PlayerStatsUIComponent(EngineGame::GameObject* gameObject);

		void Update(float deltaTime) override;
		void Render() override;

	private:
		EngineGame::HealthComponent* health = nullptr;

		sf::Font font;
		sf::Text text;
	};
}