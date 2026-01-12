#include "LifeBonus.h"
#include "GameStatePlaying.h"
#include "LifeSystem.h"

namespace RogaliqueGame
{
    void LifeBonus::applyEffect(BonusEffectManager&, Ball&, Platform&, GameStatePlaying& state)
    {
        state.getLifeSystem().addLife(1);
        deactivate();
    }
}
