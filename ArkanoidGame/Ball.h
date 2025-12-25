#pragma once
#include "GameObject.h"
#include "GameSettings.h"
#include <cmath>

namespace Arkanoid
{
    class Ball : public GameObject
    {
    private:
        sf::Vector2f velocity;
        bool isLost = false;
        float baseSpeed = BALL_SPEED;

        bool fireballMode = false;
        bool ghostMode = false;

    public:
        Ball(float x, float y);

        void update(float dt, const sf::FloatRect& platformBounds);
        void reset();

        void reflectX();
        void reflectY();

        bool lost() const { return isLost; }

        const sf::Vector2f& getVelocity() const { return velocity; }
        void setVelocity(float vx, float vy) { velocity = { vx, vy }; }
        float getSpeed() const
        {
            return std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y);
        }

        void normalizeSpeed()
        {
            float len = getSpeed();
            if (len > 0.0001f)
            {
                float k = baseSpeed / len;
                velocity.x *= k;
                velocity.y *= k;
            }
        }

        // Fireball
        void enableFireball();
        void disableFireball();
        bool isFireball() const { return fireballMode; }
        // Ghost
        void enableGhost();
        void disableGhost();
        bool isGhost() const { return ghostMode; }
    };
}
