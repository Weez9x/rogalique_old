#pragma once

#include "SoundComponent.h"

namespace RogaliqueGame
{
class DamageSoundComponent : public EngineGame::SoundComponent
{
public:
    DamageSoundComponent(EngineGame::GameObject* gameObject) : EngineGame::SoundComponent(gameObject) {}
};
} // namespace RogaliqueGame