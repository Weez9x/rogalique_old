#pragma once
#include <vector>
#include <string>
#include <functional>
#include <SFML/System/Clock.hpp>

namespace Arkanoid
{
    class Ball;
    class Platform;
    class GameStatePlaying;

    class BonusEffectManager
    {
    private:
        struct ActiveEffect
        {
            std::string name;
            float duration = 0.f;
            sf::Clock clock;
            std::function<void()> revert;
        };

        std::vector<ActiveEffect> effects;

    public:
        void addEffect(const std::string& name, float durationSec, std::function<void()> revert);

        void update(float dt, Ball&, Platform&, GameStatePlaying&);

        void clearAll();

        bool hasActiveBonus() const { return !effects.empty(); }

        std::string getActiveBonusName() const;

        float getRemainingTime() const;
    };
}
