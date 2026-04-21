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
		// музыка
		resources->LoadMusic("main_theme",MUSIC_PATH + "Music_test_1.ogg");
		levelBuilder = std::make_unique<LevelBuilder>();
		levelBuilder->BuildLevel();

		player = std::make_unique<Player>();
		enemy = std::make_unique<Enemy>(player->GetGameObject());

		EngineGame::GameObject* musicObject =EngineGame::GameWorld::Instance()->CreateGameObject("MusicPlayer");

		auto audio = musicObject->AddComponent<EngineGame::AudioComponent>();

		audio->SetMusic(resources->GetMusicShared("main_theme"));
		audio->PlayMusic(true);
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