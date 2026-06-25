#include "pch.h"
#include "Engine.h"
#include <iostream>
#include "GameWorld.h"
#include "RenderSystem.h"

namespace EngineGame
{
Engine* Engine::Instance()
{
    static Engine instance;
    return &instance;
}

Engine::Engine()
{
    unsigned int seed = (unsigned int)time(nullptr);
    srand(seed);
}

void Engine::Run()
{
    sf::Clock gameClock;
    sf::Event event;

    while (RenderSystem::Instance()->GetMainWindow().isOpen())
    {
        sf::Time dt = gameClock.restart();
        float deltaTime = dt.asSeconds();

        // SFML window events are handled before gameplay so close requests stop the frame early.
        while (RenderSystem::Instance()->GetMainWindow().pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                RenderSystem::Instance()->GetMainWindow().close();
            }
        }

        if (!RenderSystem::Instance()->GetMainWindow().isOpen())
        {
            break;
        }

        RenderSystem::Instance()->GetMainWindow().clear();

        // Frame order: gameplay, fixed physics, drawing, then delayed destruction/actions.
        GameWorld::Instance()->Update(deltaTime);
        GameWorld::Instance()->FixedUpdate(deltaTime);
        GameWorld::Instance()->Render();
        GameWorld::Instance()->LateUpdate();

        RenderSystem::Instance()->GetMainWindow().display();
    }
}
} // namespace EngineGame
