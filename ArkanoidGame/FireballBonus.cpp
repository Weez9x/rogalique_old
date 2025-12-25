#include "FireballBonus.h"
#include "BonusEffectManager.h"
#include "Ball.h"
#include "Platform.h"
#include "GameStatePlaying.h"

namespace Arkanoid
{
    void FireballBonus::applyEffect(BonusEffectManager& mgr, Ball& ball, Platform&, GameStatePlaying&)
    {
        ball.enableFireball();

        mgr.addEffect("Fireball", duration, [&ball]()
            {
                ball.disableFireball();
            });

        deactivate();
    }
}
