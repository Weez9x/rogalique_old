#pragma once
#include "Bonus.h"
#include "GameSettings.h"

namespace Arkanoid
{
    class GhostBallBonus : public Bonus
    {
    public:
        GhostBallBonus(float x, float y)
            : Bonus(TEXTURES_PATH + std::string("bonus ghost.png"), x, y, 0.f)
        {
            duration = randomDuration();
        }

        void applyEffect(BonusEffectManager& mgr, Ball& ball, Platform&, GameStatePlaying&) override;
    };
}
