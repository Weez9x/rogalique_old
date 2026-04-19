#include "GameSettings.h"
#include "GameScene.h"
#include "ResourceSystem.h"
//#include "Player.h"

namespace RogaliqueGame
{
	void GameScene::Start()
	{
		EngineGame::ResourceSystem::Instance()->LoadTexture("test", "Resources/Textures/test.png");
		auto resources = EngineGame::ResourceSystem::Instance();

		// пол
		resources->LoadTextureMap("floor",TEXTURES_PATH + "Floor.png",{ 16, 16 }, 49, false);

		// стены
		resources->LoadTextureMap("walls", TEXTURES_PATH + "Wall.png", { 16, 16 }, 48, false);

		// игрок
		resources->LoadTextureMap("player", TEXTURES_PATH + "Player.png", { 48, 63 }, 4, false);

		player = std::make_unique<Player>();
		enemy = std::make_unique<Enemy>(player->GetGameObject());

		walls.push_back(std::make_unique<Wall>(EngineGame::Vector2Df(400.f, 50.f), 700, 40));   // верх
		walls.push_back(std::make_unique<Wall>(EngineGame::Vector2Df(400.f, 550.f), 700, 40));  // низ
		walls.push_back(std::make_unique<Wall>(EngineGame::Vector2Df(50.f, 300.f), 40, 500));   // лево
		walls.push_back(std::make_unique<Wall>(EngineGame::Vector2Df(750.f, 300.f), 40, 500));  // право

	}
	void GameScene::Restart()
	{
		//Пока пусто
	}
	void GameScene::Stop()
	{
		//Пока пусто
	}
}