#include "PlatformSizeBonus.h"
#include "BonusEffectManager.h"
#include "Platform.h"
#include "Ball.h"
#include "GameStatePlaying.h"

namespace Arkanoid
{
    void PlatformSizeBonus::applyEffect(BonusEffectManager& mgr, Ball&, Platform& platform, GameStatePlaying&)
    {
        float oldWidth = platform.getWidth();
        float factor = increase ? 1.5f : 0.7f;
        platform.setWidth(oldWidth * factor);

        mgr.addEffect(increase ? "Big Platform" : "Small Platform", duration,
            [&platform, oldWidth]()
            {
                platform.setWidth(oldWidth);
            });

        deactivate();
    }
}
