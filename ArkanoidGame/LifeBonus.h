#pragma once
#include "Bonus.h"
#include "GameSettings.h"

namespace Arkanoid
{
    class LifeBonus : public Bonus
    {
    public:
        LifeBonus(float x, float y)
            : Bonus(TEXTURES_PATH + std::string("bonus life.png"), x, y, 0.f)
        {
        }

        void applyEffect(BonusEffectManager&, Ball&, Platform&, GameStatePlaying& state) override;
    };
}
