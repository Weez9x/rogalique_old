#include "GameScene.h"

#include "AudioComponent.h"
#include "GameProgress.h"
#include "GameSettings.h"
#include "GameStateManager.h"
#include "GameStateUIComponent.h"
#include "GameWorld.h"
#include "Logger.h"
#include "ResourceSystem.h"
#include "GameResourceLoader.h"

#include <stdexcept>

namespace RogaliqueGame
{
GameScene* GameScene::currentScene = nullptr;

void GameScene::Start()
{
    currentScene = this;
    GameStateManager::Reset();

    try
    {
        EngineGame::Logger::Instance()->Info("GameScene Start");

        auto resources = EngineGame::ResourceSystem::Instance();
        GameResourceLoader::LoadAll();

        levelBuilder = std::make_unique<LevelBuilder>();
        levelBuilder->BuildLevel();

        EngineGame::Logger::Instance()->Info("Level built");

        EngineGame::Vector2Df exitPosition =
            levelBuilder->GetRandomFloorPositionFarFrom({PLAYER_START_X, PLAYER_START_Y}, 1000.f);

        exitPortal = std::make_unique<ExitPortal>(exitPosition);

        EngineGame::Logger::Instance()->Info("Exit created");

        player = std::make_unique<Player>();

        EngineGame::Logger::Instance()->Info("Player created");

        enemySpawner = std::make_unique<EnemySpawner>(player->GetGameObject());
        enemySpawner->SetLevelBuilder(levelBuilder.get());

        EngineGame::Logger::Instance()->Info("EnemySpawner created");

        int slimeCount = START_SLIME_COUNT + GameProgress::CurrentLevel;
        int orcCount = START_ORC_COUNT + GameProgress::CurrentLevel / 2;

        for (int i = 0; i < slimeCount; ++i)
        {
            enemySpawner->Spawn(EnemyType::Slime,
                                levelBuilder->GetRandomFloorPositionFarFrom({PLAYER_START_X, PLAYER_START_Y},
                                                                            ENEMY_SPAWN_DISTANCE_FROM_PLAYER));
        }

        for (int i = 0; i < orcCount; ++i)
        {
            enemySpawner->Spawn(EnemyType::Orc,
                                levelBuilder->GetRandomFloorPositionFarFrom({PLAYER_START_X, PLAYER_START_Y},
                                                                            ENEMY_SPAWN_DISTANCE_FROM_PLAYER));
        }

        player->SetEnemySpawner(enemySpawner.get());

        EngineGame::Logger::Instance()->Info("Enemies spawned");
        EngineGame::Logger::Instance()->Info("Player enemy spawner set");

        auto gameStateUIObject = EngineGame::GameWorld::Instance()->CreateGameObject("GameStateUI");

        // This UI owns Win/GameOver overlays and their keyboard actions.
        gameStateUIObject->AddComponent<GameStateUIComponent>();

        EngineGame::GameObject* musicObject = EngineGame::GameWorld::Instance()->CreateGameObject("MusicPlayer");

        auto audio = musicObject->AddComponent<EngineGame::AudioComponent>();
        audio->SetMusic(resources->GetMusicShared("main_theme"));
        audio->SetVolume(50.f);
        audio->PlayMusic(true);

        EngineGame::Logger::Instance()->Info("Music started");
    }
    catch (const std::exception& e)
    {
        EngineGame::Logger::Instance()->Error(std::string("Exception in GameScene::Start: ") + e.what());
    }
}

void GameScene::RestartLevel()
{
    if (currentScene == nullptr)
    {
        return;
    }

    EngineGame::Logger::Instance()->Info("Restarting level...");

    EngineGame::GameWorld::Instance()->Clear();

    // Full restart starts a new run from level 1.
    GameProgress::Reset();

    GameStateManager::Reset();

    currentScene->Start();
}

void GameScene::NextLevel()
{
    if (currentScene == nullptr)
    {
        return;
    }

    EngineGame::Logger::Instance()->Info("Loading next level...");

    EngineGame::GameWorld::Instance()->Clear();

    // Level transition keeps the run alive and scales the kill requirement.
    GameProgress::NextLevel();

    GameStateManager::Reset();

    currentScene->Start();
}

void GameScene::Restart()
{
    RestartLevel();
}

void GameScene::Stop() {}
} // namespace RogaliqueGame
