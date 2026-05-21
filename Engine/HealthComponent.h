#pragma once

#include "Component.h"

namespace EngineGame
{
	class HealthComponent : public Component
	{
	public:
		HealthComponent(GameObject* gameObject);

		void Update(float deltaTime) override;
		void Render() override;

		void SetHealth(float newHealth);
		void SetArmor(float newArmor);

		float GetHealth() const;
		float GetArmor() const;

		void TakeDamage(float damage);

		bool IsDead() const;

		bool isDeadLogged = false;

		void SetInvulnerable(bool value);
		bool IsInvulnerable() const;

	private:
		float health = 100.0f;
		float armor = 0.0f;
		bool isInvulnerable = false;
	};
}