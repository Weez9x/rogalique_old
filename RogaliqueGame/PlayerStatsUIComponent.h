#pragma once

#include "Component.h"
#include "HealthComponent.h"
#include "PlayerLivesComponent.h"
#include <SFML/Graphics.hpp>

namespace RogaliqueGame
{
class PlayerStatsUIComponent : public EngineGame::Component
{
public:
    PlayerStatsUIComponent(EngineGame::GameObject* gameObject);

    void Update(float deltaTime) override;
    void Render() override;

private:
    // Cached component links keep the HUD cheap to update every frame.
    EngineGame::HealthComponent* health = nullptr;
    PlayerLivesComponent* lives = nullptr;

    sf::Font font;
    sf::Text text;
};
} // namespace RogaliqueGame
