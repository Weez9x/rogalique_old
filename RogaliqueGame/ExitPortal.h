#pragma once

#include "GameObject.h"

namespace RogaliqueGame
{
class ExitPortal
{
public:
    ExitPortal(const EngineGame::Vector2Df& position);

private:
    EngineGame::GameObject* gameObject = nullptr;
};
} // namespace RogaliqueGame