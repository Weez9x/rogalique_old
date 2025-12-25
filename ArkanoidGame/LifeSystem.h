#pragma once

namespace Arkanoid
{
    class LifeSystem
    {
    private:
        int lives = 1;
        int maxLives = 5;

    public:
        LifeSystem() = default;
        explicit LifeSystem(int start) : lives(start) {}

        int getLives() const { return lives; }

        void addLife(int amount = 1)
        {
            lives += amount;
            if (lives > maxLives)
                lives = maxLives;
        }

        bool consumeLife()
        {
            if (lives > 0)
            {
                --lives;
                return true;
            }
            return false;
        }

        void reset(int startLives = 1)
        {
            lives = startLives;
        }
    };
}
