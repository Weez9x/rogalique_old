#pragma once

#include "Component.h"
#include "TransformComponent.h"
#include "MeleeAttackComponent.h"

namespace RogaliqueGame
{
	class PlayerAttackComponent : public EngineGame::Component
	{
	public:
		PlayerAttackComponent(EngineGame::GameObject* gameObject);

		void Update(float deltaTime) override;
		void Render() override;

		void SetTarget(EngineGame::GameObject* newTarget);
		void TryDealDamage();

	private:
		EngineGame::TransformComponent* transform = nullptr;
		MeleeAttackComponent* meleeAttack = nullptr;
		EngineGame::GameObject* target = nullptr;

		float attackRange = 120.0f;
		float attackCooldown = 0.5f;
		float currentCooldown = 0.0f;

		bool isAttackActive = false;
		bool damageApplied = false;

		float attackDuration = 0.45f;
		float attackTimer = 0.0f;

		float damageMoment = 0.22f;
	};
}