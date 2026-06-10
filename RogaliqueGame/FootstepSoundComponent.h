#pragma once

#include "SoundComponent.h"

namespace RogaliqueGame
{
class FootstepSoundComponent : public EngineGame::SoundComponent
{
public:
    FootstepSoundComponent(EngineGame::GameObject* gameObject) : EngineGame::SoundComponent(gameObject) {}
};
} // namespace RogaliqueGame