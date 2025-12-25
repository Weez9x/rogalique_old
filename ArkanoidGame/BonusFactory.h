#pragma once
#include <memory>
#include "Bonus.h"

namespace Arkanoid
{
    enum class BonusType
    {
        Fireball,
        GhostBall,
        PlatformIncrease,
        PlatformDecrease,
        Life
    };

    class BonusFactory
    {
    public:
        static std::unique_ptr<Bonus> createBonus(BonusType type, float x, float y);

        static std::unique_ptr<Bonus> createRandomBonus(float x, float y);
    };
}
