#include "ExitPortal.h"

#include "BoxColliderComponent.h"
#include "ExitPortalComponent.h"
#include "GameSettings.h"
#include "GameWorld.h"
#include "ResourceSystem.h"
#include "RigidbodyComponent.h"
#include "SpriteRendererComponent.h"
#include "TransformComponent.h"

namespace RogaliqueGame
{
ExitPortal::ExitPortal(const EngineGame::Vector2Df& position)
{
    gameObject = EngineGame::GameWorld::Instance()->CreateGameObject("ExitPortal");

    auto transform = gameObject->GetComponent<EngineGame::TransformComponent>();
    transform->SetWorldPosition(position);

    auto rigidbody = gameObject->AddComponent<EngineGame::RigidbodyComponent>();
    rigidbody->SetKinematic(true);

    auto spriteRenderer = gameObject->AddComponent<EngineGame::SpriteRendererComponent>();
    spriteRenderer->SetTexture(
        *EngineGame::ResourceSystem::Instance()->GetTextureMapElementShared("floor", PORTAL_CLOSED_TILE));
    spriteRenderer->SetPixelSize(TILE_SIZE, TILE_SIZE);
    spriteRenderer->FlipY(true);

    auto collider = gameObject->AddComponent<EngineGame::BoxColliderComponent>();
    collider->SetSize(80.f, 80.f);
    collider->SetTrigger(true);

    gameObject->AddComponent<ExitPortalComponent>();
}
} // namespace RogaliqueGame