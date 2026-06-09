#include "PlayerLivesComponent.h"

#include "GameObject.h"
#include "Logger.h"
#include "GameScene.h"
#include "GameState.h"
#include "GameStateManager.h"
#include "CameraShakeComponent.h"

#include <cassert>

namespace RogaliqueGame
{
PlayerLivesComponent::PlayerLivesComponent(EngineGame::GameObject* gameObject) : Component(gameObject)
{
    health = gameObject->GetComponent<EngineGame::HealthComponent>();

    if (health == nullptr)
    {
        EngineGame::Logger::Instance()->Error("PlayerLivesComponent requires HealthComponent");
    }

    assert(health != nullptr && "PlayerLivesComponent requires HealthComponent");
}

void PlayerLivesComponent::Update(float deltaTime)
{
    if (health == nullptr)
    {
        return;
    }

    if (health->IsDead() && !deathHandled)
    {
        LoseLife();
        deathHandled = true;
    }

    if (!health->IsDead())
    {
        deathHandled = false;
    }
}

void PlayerLivesComponent::Render() {}

int PlayerLivesComponent::GetLives() const
{
    return lives;
}

bool PlayerLivesComponent::HasLives() const
{
    return lives > 0;
}

void PlayerLivesComponent::LoseLife()
{
    if (lives <= 0)
    {
        return;
    }

    lives--;

    EngineGame::Logger::Instance()->Info("Player lost life. Lives left: " + std::to_string(lives));

    if (lives <= 0)
    {
        // GameOver is a state transition only; the overlay handles player input from here.
        GameStateManager::SetState(GameState::GameOver);
        auto cameraShake = gameObject->GetComponent<EngineGame::CameraShakeComponent>();
        if (cameraShake != nullptr)
        {
            cameraShake->Shake(5.f, 40.f);
        }
        EngineGame::Logger::Instance()->Error("GAME OVER");
    }
}
} // namespace RogaliqueGame
