#include "GhostBallBonus.h"
#include "BonusEffectManager.h"
#include "Ball.h"
#include "Platform.h"
#include "GameStatePlaying.h"

namespace Arkanoid
{
    void GhostBallBonus::applyEffect(BonusEffectManager& mgr, Ball& ball, Platform&, GameStatePlaying&)
    {
        ball.enableGhost();

        mgr.addEffect("Ghost", duration, [&ball]()
            {
                ball.disableGhost();
            });

        deactivate();
    }
}
