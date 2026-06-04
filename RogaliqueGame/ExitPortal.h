#pragma once

#include "GameObject.h"

namespace RogaliqueGame
{
class ExitPortal
{
public:
    // ExitPortal is a small prefab: visual tile, trigger collider, and portal logic.
    ExitPortal(const EngineGame::Vector2Df& position);

private:
    EngineGame::GameObject* gameObject = nullptr;
};
} // namespace RogaliqueGame
