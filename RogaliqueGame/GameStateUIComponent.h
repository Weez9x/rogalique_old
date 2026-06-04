#pragma once

#include "Component.h"

#include <SFML/Graphics.hpp>

namespace RogaliqueGame
{
class GameStateUIComponent : public EngineGame::Component
{
public:
    GameStateUIComponent(EngineGame::GameObject* gameObject);

    void Update(float deltaTime) override;
    void Render() override;

private:
    sf::Font font;
    sf::Text text;
    sf::RectangleShape overlay;

    bool rPressedLastFrame = false;
    bool escPressedLastFrame = false;
    bool actionQueued = false;
};
} // namespace RogaliqueGame
