#include "BonusFactory.h"
#include "FireballBonus.h"
#include "GhostBallBonus.h"
#include "PlatformSizeBonus.h"
#include "LifeBonus.h"
#include "GameSettings.h"
#include <cstdlib>

namespace Arkanoid
{
    std::unique_ptr<Bonus> BonusFactory::createBonus(BonusType type, float x, float y)
    {
        switch (type)
        {
        case BonusType::Fireball:
            return std::make_unique<FireballBonus>(x, y);
        case BonusType::GhostBall:
            return std::make_unique<GhostBallBonus>(x, y);
        case BonusType::PlatformIncrease:
            return std::make_unique<PlatformSizeBonus>(x, y, true);
        case BonusType::PlatformDecrease:
            return std::make_unique<PlatformSizeBonus>(x, y, false);
        case BonusType::Life:
            return std::make_unique<LifeBonus>(x, y);
        }
        return nullptr;
    }

    std::unique_ptr<Bonus> BonusFactory::createRandomBonus(float x, float y)
    {
        int r = std::rand() % 100;

        BonusType type;
        if (r < 25) type = BonusType::Fireball;
        else if (r < 50) type = BonusType::GhostBall;
        else if (r < 70) type = BonusType::PlatformIncrease;
        else if (r < 90) type = BonusType::PlatformDecrease;
        else type = BonusType::Life;

        return createBonus(type, x, y);
    }
}
