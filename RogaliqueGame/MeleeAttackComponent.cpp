#include "MeleeAttackComponent.h"

#include "GameObject.h"
#include "HealthComponent.h"
#include "Logger.h"

namespace RogaliqueGame
{
	MeleeAttackComponent::MeleeAttackComponent(EngineGame::GameObject* gameObject)
		: Component(gameObject)
	{
	}

	void MeleeAttackComponent::Update(float deltaTime)
	{
	}

	void MeleeAttackComponent::Render()
	{
	}

	void MeleeAttackComponent::SetDamage(float newDamage)
	{
		if (newDamage < 0.0f)
		{
			EngineGame::Logger::Instance()->Warning("MeleeAttackComponent: negative damage clamped to 0.");
			newDamage = 0.0f;
		}

		damage = newDamage;
	}

	void MeleeAttackComponent::Attack(EngineGame::GameObject* target)
	{
		if (target == nullptr)
		{
			EngineGame::Logger::Instance()->Warning("Attack target is null");
			return;
		}

		auto health = target->GetComponent<EngineGame::HealthComponent>();

		if (health == nullptr)
		{
			EngineGame::Logger::Instance()->Warning("Attack target has no HealthComponent");
			return;
		}

		if (health->IsDead())
		{
			EngineGame::Logger::Instance()->Info("Attack ignored: target already dead");
			return;
		}

		health->TakeDamage(damage);

		EngineGame::Logger::Instance()->Info("Attack dealt damage: " + std::to_string(damage));
	}
}