#pragma once
#include "Bonus.h"
#include "GameSettings.h"

namespace Arkanoid
{
    class PlatformSizeBonus : public Bonus
    {
    private:
        bool increase = true;

    public:
        PlatformSizeBonus(float x, float y, bool inc)
            : Bonus(TEXTURES_PATH + std::string("bonus platform.png"), x, y, 0.f)
            , increase(inc)
        {
            duration = randomDuration();
        }

        void applyEffect(BonusEffectManager& mgr, Ball&, Platform& platform, GameStatePlaying&) override;
    };
}
