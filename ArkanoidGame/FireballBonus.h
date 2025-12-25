#pragma once
#include "Bonus.h"
#include "GameSettings.h"

namespace Arkanoid
{
    class FireballBonus : public Bonus
    {
    public:
        FireballBonus(float x, float y)
            : Bonus(TEXTURES_PATH + std::string("bonus fire.png"), x, y, 0.f)
        {
            duration = randomDuration();
        }

        void applyEffect(BonusEffectManager& mgr, Ball& ball, Platform&, GameStatePlaying&) override;
    };
}
