#pragma once
#include <memory>
#include "Scene.h"
#include "Player.h"
#include <vector>
#include "Wall.h"
#include "Enemy.h"

namespace RogaliqueGame
{
	class GameScene : public EngineGame::Scene
	{
	public:
		void Start() override;
		void Restart() override;
		void Stop() override;

	private:
		std::unique_ptr<Player> player;
		std::vector<std::unique_ptr<Wall>> walls;
		std::unique_ptr<Enemy> enemy;
	};
}