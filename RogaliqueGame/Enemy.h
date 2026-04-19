#pragma once
#include"GameObject.h"

namespace RogaliqueGame
{
	class Enemy
	{
	public:
		Enemy(EngineGame::GameObject* playerObject);
		EngineGame::GameObject* GetGameObject() const;

	private:
		EngineGame::GameObject* gameObject = nullptr;

	};
}