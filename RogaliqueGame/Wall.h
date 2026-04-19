#pragma once

#include "GameObject.h"
#include "Vector.h"

namespace RogaliqueGame
{
	class Wall
	{
	public:
		Wall(const EngineGame::Vector2Df& position, int width, int height);

		EngineGame::GameObject* GetGameObject() const;

	private:
		EngineGame::GameObject* gameObject = nullptr;
	};
}