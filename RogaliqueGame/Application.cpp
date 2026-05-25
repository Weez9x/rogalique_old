#include "Application.h"
#include "GameSettings.h"
#include "Logger.h"

namespace RogaliqueGame
{
void Application::CreateScene()
{
    scene = std::make_unique<GameScene>();
    scene->Start();
}

void Application::run()
{
    EngineGame::Logger::Instance()->AddSink(std::make_shared<EngineGame::ConsoleSink>());
    EngineGame::Logger::Instance()->AddSink(std::make_shared<EngineGame::FileSink>("game.log"));
    EngineGame::Logger::Instance()->Info("Application started");

    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "RogaliqueGame");
    window.setFramerateLimit(60);

    EngineGame::Logger::Instance()->Info("Window created");

    EngineGame::RenderSystem::Instance()->SetMainWindow(&window);

    CreateScene();

    EngineGame::Logger::Instance()->Info("Engine run started");
    EngineGame::Engine::Instance()->Run();
}
} // namespace RogaliqueGame
