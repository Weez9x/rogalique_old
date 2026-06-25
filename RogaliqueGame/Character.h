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
    // Game-specific wrappers keep the EngineGame object pointer they configure.
    EngineGame::GameObject* gameObject = nullptr;
};
} // namespace RogaliqueGame
