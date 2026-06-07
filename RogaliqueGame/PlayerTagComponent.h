#pragma once
#include "Component.h"

namespace RogaliqueGame
{
	class PlayerTagComponent : public EngineGame::Component
{
		public:
		PlayerTagComponent(EngineGame::GameObject* gameObject);
		~PlayerTagComponent() override = default;
		void Update(float deltaTime) override;
		void Render() override;
};
}