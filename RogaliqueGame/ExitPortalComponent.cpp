#include "ExitPortalComponent.h"

#include "GameObject.h"
#include "GameProgress.h"
#include "GameScene.h"
#include "GameSettings.h"
#include "GameState.h"
#include "Logger.h"
#include "ResourceSystem.h"
#include "Trigger.h"
#include "GameStateManager.h"

namespace RogaliqueGame
{
ExitPortalComponent::ExitPortalComponent(EngineGame::GameObject* gameObject) : Component(gameObject)
{
    spriteRenderer = gameObject->GetComponent<EngineGame::SpriteRendererComponent>();
    collider = gameObject->GetComponent<EngineGame::BoxColliderComponent>();

    if (spriteRenderer == nullptr)
    {
        EngineGame::Logger::Instance()->Error("ExitPortalComponent requires SpriteRendererComponent");
    }

    if (collider == nullptr)
    {
        EngineGame::Logger::Instance()->Error("ExitPortalComponent requires BoxColliderComponent");
        return;
    }

    collider->SubscribeTriggerEnter([this](EngineGame::Trigger trigger) { OnTriggerEnter(trigger); });
}

void ExitPortalComponent::Update(float deltaTime)
{
    TryOpen();
}

void ExitPortalComponent::Render() {}

void ExitPortalComponent::TryOpen()
{
    if (isOpened)
    {
        return;
    }

    if (GameProgress::CurrentKills >= GameProgress::RequiredKills)
    {
        isOpened = true;

        if (spriteRenderer != nullptr)
        {
            spriteRenderer->SetTexture(
                *EngineGame::ResourceSystem::Instance()->GetTextureMapElementShared("floor", PORTAL_OPEN_TILE));
        }

        EngineGame::Logger::Instance()->Info("Portal opened!");
    }
}

void ExitPortalComponent::OnTriggerEnter(EngineGame::Trigger trigger)
{
    auto first = trigger.GetFirst();
    auto second = trigger.GetSecond();

    if (first == nullptr || second == nullptr)
    {
        return;
    }

    if (first->GetGameObject()->GetName() != "Player" && second->GetGameObject()->GetName() != "Player")
    {
        return;
    }

    TryOpen();

    if (!isOpened)
    {
        EngineGame::Logger::Instance()->Info("Portal is closed. Kill more enemies.");
        return;
    }

    GameStateManager::SetState(GameState::Win);
    EngineGame::Logger::Instance()->Info("YOU WIN");
}
} // namespace RogaliqueGame