#pragma once

#include "Component.h"
#include "HealthComponent.h"
#include "GameSettings.h"

namespace RogaliqueGame
{
class PlayerLivesComponent : public EngineGame::Component
{
public:
    PlayerLivesComponent(EngineGame::GameObject* gameObject);

    void Update(float deltaTime) override;
    void Render() override;

    int GetLives() const;
    bool HasLives() const;

    void LoseLife();

private:
    EngineGame::HealthComponent* health = nullptr;

    int lives = PLAYER_LIVES;
    bool deathHandled = false;
};
} // namespace RogaliqueGame