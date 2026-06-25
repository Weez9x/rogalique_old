#pragma once

#include "SoundComponent.h"

namespace RogaliqueGame
{
class AttackSoundComponent : public EngineGame::SoundComponent
{
public:
    AttackSoundComponent(EngineGame::GameObject* gameObject) : EngineGame::SoundComponent(gameObject) {}
};
} // namespace RogaliqueGame    