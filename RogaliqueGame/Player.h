#pragma once
#include "GameObject.h"

namespace RogaliqueGame
{
	class Player
	{
	public:
		Player();
		EngineGame::GameObject* GetGameObject() const;
	
	private:
		EngineGame::GameObject* gameObject = nullptr;
	};
}