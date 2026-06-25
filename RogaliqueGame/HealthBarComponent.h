#pragma once

#include "Component.h"
#include "TransformComponent.h"
#include "HealthComponent.h"
#include "GameSettings.h"

#include <SFML/Graphics.hpp>

namespace RogaliqueGame
{
class HealthBarComponent : public EngineGame::Component
{
public:
    HealthBarComponent(EngineGame::GameObject* gameObject);

    void Update(float deltaTime) override;
    void Render() override;

    void SetMaxHealth(float value);
    void SetOffset(float x, float y);
    void SetSize(float width, float height);

private:
    EngineGame::TransformComponent* transform = nullptr;
    EngineGame::HealthComponent* health = nullptr;

    // Max health is set per enemy type so the bar can display normalized health.
    float maxHealth = PLAYER_MAX_HEALTH;

    EngineGame::Vector2Df offset = {DEFAULT_HEALTH_BAR_OFFSET_X, DEFAULT_HEALTH_BAR_OFFSET_Y};
    EngineGame::Vector2Df size = {DEFAULT_HEALTH_BAR_WIDTH, DEFAULT_HEALTH_BAR_HEIGHT};

    sf::RectangleShape background;
    sf::RectangleShape fill;
};
} // namespace RogaliqueGame
