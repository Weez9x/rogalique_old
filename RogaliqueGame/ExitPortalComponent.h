#pragma once

#include "Component.h"
#include "BoxColliderComponent.h"
#include "SpriteRendererComponent.h"

namespace RogaliqueGame
{
class ExitPortalComponent : public EngineGame::Component
{
public:
    ExitPortalComponent(EngineGame::GameObject* gameObject);

    void Update(float deltaTime) override;
    void Render() override;

private:
    // The portal opens only after the current level's kill target is reached.
    void TryOpen();
    void OnTriggerEnter(EngineGame::Trigger trigger);

private:
    EngineGame::SpriteRendererComponent* spriteRenderer = nullptr;
    EngineGame::BoxColliderComponent* collider = nullptr;

    bool isOpened = false;
};
} // namespace RogaliqueGame
