#pragma once
#include <memory>
#include "Scene.h"
#include "Player.h"
#include <vector>
#include "Wall.h"
#include "Enemy.h"
#include "LevelBuilder.h"
#include "AudioComponent.h"
#include "GameWorld.h"

namespace RogaliqueGame
{
	class GameScene : public EngineGame::Scene
	{
	public:
		void Start() override;
		void Restart() override;
		void Stop() override;

	private:
		std::unique_ptr<LevelBuilder> levelBuilder;
		std::unique_ptr<Player> player;
		std::unique_ptr<Enemy> enemy;
	};
}