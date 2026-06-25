#pragma once

#include <memory>

#include "EnemySpawner.h"
#include "ExitPortal.h"
#include "GameState.h"
#include "LevelBuilder.h"
#include "Player.h"
#include "Scene.h"

namespace RogaliqueGame
{
class GameScene : public EngineGame::Scene
{
public:
    void Start() override;
    void Restart() override;
    void Stop() override;

    // Called from UI after the frame finishes, because rebuilding clears GameWorld.
    static void RestartLevel();
    static void NextLevel();

private:
    std::unique_ptr<LevelBuilder> levelBuilder;
    std::unique_ptr<Player> player;
    std::unique_ptr<EnemySpawner> enemySpawner;
    std::unique_ptr<ExitPortal> exitPortal;

    static GameScene* currentScene;
};
} // namespace RogaliqueGame
