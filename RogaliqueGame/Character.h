#pragma once

#include "GameObject.h"

namespace RogaliqueGame
{
class Character
{
public:
    virtual ~Character() = default;

    EngineGame::GameObject* GetGameObject() const;

protected:
    EngineGame::GameObject* gameObject = nullptr;
};
} // namespace RogaliqueGame