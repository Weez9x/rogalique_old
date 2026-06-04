#include "FloorTile.h"
#include "GameWorld.h"
#include "TransformComponent.h"
#include "SpriteRendererComponent.h"
#include "ResourceSystem.h"

namespace RogaliqueGame
{
FloorTile::FloorTile(const EngineGame::Vector2Df& position, int width, int height, int tileIndex)
{
    gameObject = EngineGame::GameWorld::Instance()->CreateGameObject("FloorTile");

    auto transform = gameObject->GetComponent<EngineGame::TransformComponent>();
    transform->SetWorldPosition(position.x, position.y);

    auto spriteRenderer = gameObject->AddComponent<EngineGame::SpriteRendererComponent>();
    spriteRenderer->SetTexture(*EngineGame::ResourceSystem::Instance()->GetTextureMapElementShared("floor", tileIndex));
    spriteRenderer->SetPixelSize(width, height);
    spriteRenderer->FlipY(true);
}

EngineGame::GameObject* FloorTile::GetGameObject() const
{
    return gameObject;
}
} // namespace RogaliqueGame