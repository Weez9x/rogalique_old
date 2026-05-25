#pragma once
#include "GameObject.h"
#include "Vector.h"

namespace RogaliqueGame
{
class FloorTile
{
public:
    FloorTile(const EngineGame::Vector2Df& position, int width, int height, int tileIndex);

    EngineGame::GameObject* GetGameObject() const;

private:
    EngineGame::GameObject* gameObject = nullptr;
};
} // namespace RogaliqueGame