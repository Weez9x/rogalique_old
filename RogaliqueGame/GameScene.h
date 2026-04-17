#pragma once
#include "Scene.h"

namespace RogaliqueGame
{
	class GameScene : public EngineGame::Scene
	{
	public:
		void Start() override;
		void Restart() override;
		void Stop() override;
	};
}