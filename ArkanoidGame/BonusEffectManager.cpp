#include "BonusEffectManager.h"

namespace Arkanoid
{
    void BonusEffectManager::addEffect(const std::string& name, float durationSec, std::function<void()> revert)
    {
        ActiveEffect eff;
        eff.name = name;
        eff.duration = durationSec;
        eff.revert = std::move(revert);
        eff.clock.restart();
        effects.emplace_back(std::move(eff));
    }

    void BonusEffectManager::update(float, Ball&, Platform&, GameStatePlaying&)
    {
        for (size_t i = 0; i < effects.size();)
        {
            float elapsed = effects[i].clock.getElapsedTime().asSeconds();
            if (elapsed >= effects[i].duration)
            {
                if (effects[i].revert)
                    effects[i].revert();
                effects.erase(effects.begin() + i);
            }
            else
            {
                ++i;
            }
        }
    }

    void BonusEffectManager::clearAll()
    {
        for (auto& e : effects)
        {
            if (e.revert)
                e.revert();
        }
        effects.clear();
    }

    std::string BonusEffectManager::getActiveBonusName() const
    {
        if (effects.empty()) return "None";
        return effects.back().name;
    }

    float BonusEffectManager::getRemainingTime() const
    {
        if (effects.empty()) return 0.f;
        const auto& e = effects.back();
        float elapsed = e.clock.getElapsedTime().asSeconds();
        float rem = e.duration - elapsed;
        return rem > 0.f ? rem : 0.f;
    }
}
