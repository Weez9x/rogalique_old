#include "GameScene.h"
#include "GameSettings.h"
#include "ResourceSystem.h"
#include "Logger.h"
#include <stdexcept>
#include "AudioComponent.h"
#include "GameWorld.h"

namespace RogaliqueGame
{
	void GameScene::Start()
	{
		try
		{
			EngineGame::Logger::Instance()->Info("GameScene Start");

			auto resources = EngineGame::ResourceSystem::Instance();

			resources->LoadTexture("test", TEXTURES_PATH + "test.png");
			resources->LoadTextureMap("floor", TEXTURES_PATH + "Floor.png", { 16, 16 }, 49, false);
			resources->LoadTextureMap("walls", TEXTURES_PATH + "Wall.png", { 16, 16 }, 48, false);
			resources->LoadTextureMap("player", TEXTURES_PATH + "Human_Soldier_Sword_Shield-Sheet.png", { 96, 96 }, 80, false);
			resources->LoadTextureMap("enemy", TEXTURES_PATH + "Monster_Slime-Sheet.png", { 96, 96 }, 80, false);
			resources->LoadMusic("main_theme", MUSIC_PATH + "Music_test_1.ogg");

			EngineGame::Logger::Instance()->Info("Resources loaded");

			levelBuilder = std::make_unique<LevelBuilder>();
			levelBuilder->BuildLevel();
			EngineGame::Logger::Instance()->Info("Level built");

			player = std::make_unique<Player>();
			EngineGame::Logger::Instance()->Info("Player created");

			enemy = std::make_unique<Enemy>(player->GetGameObject());
			EngineGame::Logger::Instance()->Info("Enemy created");

			player->SetAttackTarget(enemy->GetGameObject());
			EngineGame::Logger::Instance()->Info("Player attack target set");

			EngineGame::GameObject* musicObject = EngineGame::GameWorld::Instance()->CreateGameObject("MusicPlayer");

			auto audio = musicObject->AddComponent<EngineGame::AudioComponent>();
			audio->SetMusic(resources->GetMusicShared("main_theme"));
			audio->PlayMusic(true);

			EngineGame::Logger::Instance()->Info("Music started");
		}
		catch (const std::exception& e)
		{
			EngineGame::Logger::Instance()->Error(std::string("Exception in GameScene::Start: ") + e.what());
		}
		
	}

	void GameScene::Restart()
	{
	}

	void GameScene::Stop()
	{
	}
}