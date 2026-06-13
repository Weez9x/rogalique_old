#pragma once

#include "Component.h"

#include <SFML/Graphics.hpp>

namespace RogaliqueGame
{
class DebugFPSComponent : public EngineGame::Component
{
public:
    DebugFPSComponent(EngineGame::GameObject* gameObject);

    void Update(float deltaTime) override;
    void Render() override;

private:
    sf::Font font;
    sf::Text fpsText;

    bool isVisible = false;
    float fpsTimer = 0.f;
    int frameCounter = 0;
    int currentFPS = 0;
};
} // namespace RogaliqueGame