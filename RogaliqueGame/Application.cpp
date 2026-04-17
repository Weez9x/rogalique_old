#include "Application.h"
#include "GameSettings.h"

namespace RogaliqueGame
{
	void Application::CreateScene()
	{
		scene = std::make_unique<GameScene>();
		scene->Start();
	}
	void Application::run()
	{
		sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "RogaliqueGame");
        window.setFramerateLimit(60);

        EngineGame::RenderSystem::Instance()->SetMainWindow(&window);

        Application::CreateScene();

        EngineGame::Engine::Instance()->Run();
	
	}
}

