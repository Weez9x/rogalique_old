#pragma once
#include "GameObject.h"

namespace RogaliqueGame
{
class Player
{
public:
    Player();
    EngineGame::GameObject* GetGameObject() const;
    void SetAttackTarget(EngineGame::GameObject* target);

private:
    EngineGame::GameObject* gameObject = nullptr;
};
} // namespace RogaliqueGame