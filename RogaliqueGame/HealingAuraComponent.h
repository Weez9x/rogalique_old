#pragma once

#include "LightAuraComponent.h"

    namespace RogaliqueGame
{
    class HealingAuraComponent : public EngineGame::LightAuraComponent
    {
    public:
        HealingAuraComponent(EngineGame::GameObject* gameObject) : EngineGame::LightAuraComponent(gameObject) {}
    };
}