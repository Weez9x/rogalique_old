#include "pch.h"
#include "DebugFPSComponent.h"

#include "RenderSystem.h"
#include "Logger.h"

namespace RogaliqueGame
{
DebugFPSComponent::DebugFPSComponent(EngineGame::GameObject* gameObject) : Component(gameObject)
{
    if (!font.loadFromFile("Resources/Fonts/ARCADEPI.ttf"))
    {
        EngineGame::Logger::Instance()->Warning("DebugFPSComponent: failed to load font");
    }

    fpsText.setFont(font);
    fpsText.setCharacterSize(20);
    fpsText.setFillColor(sf::Color::White);
    fpsText.setPosition(10.f, 10.f);
}

void DebugFPSComponent::Update(float deltaTime)
{
    fpsTimer += deltaTime;
    frameCounter++;

    if (fpsTimer >= 1.f)
    {
        currentFPS = frameCounter;

        frameCounter = 0;
        fpsTimer = 0.f;

        fpsText.setString("FPS: " + std::to_string(currentFPS));
    }
}

void DebugFPSComponent::Render()
{
    if (isVisible)
    {
        auto& window = EngineGame::RenderSystem::Instance()->GetMainWindow();

        sf::View oldView = window.getView();

        window.setView(window.getDefaultView());

        window.draw(fpsText);

        window.setView(oldView);
    }
}
} // namespace RogaliqueGame