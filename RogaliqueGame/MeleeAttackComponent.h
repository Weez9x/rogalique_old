#pragma once

#include "Component.h"

namespace EngineGame
{
	class HealthComponent;
}

namespace RogaliqueGame
{
	class MeleeAttackComponent : public EngineGame::Component
	{
	public:
		MeleeAttackComponent(EngineGame::GameObject* gameObject);

		void Update(float deltaTime) override;
		void Render() override;

		void SetDamage(float newDamage);
		void Attack(EngineGame::GameObject* target);

	private:
		float damage = 10.0f;

	};
}