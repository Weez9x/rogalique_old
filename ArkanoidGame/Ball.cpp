#include "Ball.h"
#include "GameSettings.h"

namespace Arkanoid
{
    Ball::Ball(float x, float y)
    {
        shape.setSize({ BALL_RADIUS * 2.f, BALL_RADIUS * 2.f });
        shape.setOrigin(BALL_RADIUS, BALL_RADIUS);
        shape.setPosition(x, y);
        setTexture(TEXTURES_PATH + "ball.png");

        baseSpeed = BALL_SPEED;
        velocity = { baseSpeed, -baseSpeed };
    }

    void Ball::update(float dt, const sf::FloatRect& platformBounds)
    {
        if (!active) return;

        auto pos = shape.getPosition();
        pos += velocity * dt;
        shape.setPosition(pos);

        if (pos.x - BALL_RADIUS <= 0.f)
        {
            pos.x = BALL_RADIUS;
            reflectX();
            shape.setPosition(pos);
        }
        else if (pos.x + BALL_RADIUS >= SCREEN_WIDTH)
        {
            pos.x = SCREEN_WIDTH - BALL_RADIUS;
            reflectX();
            shape.setPosition(pos);
        }

        if (pos.y - BALL_RADIUS <= 0.f)
        {
            pos.y = BALL_RADIUS;
            reflectY();
            shape.setPosition(pos);
        }

        if (pos.y - BALL_RADIUS > SCREEN_HEIGHT)
        {
            isLost = true;
        }

        sf::FloatRect ballBounds = getBounds();
        if (ballBounds.intersects(platformBounds))
        {
            float platformCenter = platformBounds.left + platformBounds.width / 2.f;
            float ballCenter = ballBounds.left + ballBounds.width / 2.f;
            float hitFactor = (ballCenter - platformCenter) / (platformBounds.width / 2.f);

            const float MAX_ANGLE = 75.f * 3.14159265f / 180.f;
            float angle = hitFactor * MAX_ANGLE;

            float speed = getSpeed();
            if (speed < 1.f) speed = baseSpeed;

            velocity.x = speed * std::sin(angle);
            velocity.y = -speed * std::cos(angle);

            shape.move(0.f, -2.f);
        }
    }

    void Ball::reset()
    {
        isLost = false;
        active = true;
        shape.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f);

        baseSpeed = BALL_SPEED;
        velocity = { baseSpeed, -baseSpeed };

        fireballMode = false;
        ghostMode = false;
        setTexture(TEXTURES_PATH + "ball.png");
    }

    void Ball::reflectX()
    {
        velocity.x *= -1.f;
        normalizeSpeed();
    }

    void Ball::reflectY()
    {
        velocity.y *= -1.f;
        normalizeSpeed();
    }

    void Ball::enableFireball()
    {
        fireballMode = true;
        setTexture(TEXTURES_PATH + "ball bonus fire.png");
        velocity.x *= 1.4f;
        velocity.y *= 1.4f;
    }

    void Ball::disableFireball()
    {
        fireballMode = false;
        setTexture(TEXTURES_PATH + "ball.png");
        normalizeSpeed();
    }

    void Ball::enableGhost()
    {
        ghostMode = true;
        setTexture(TEXTURES_PATH + "ball bonus ghos.png"); // файл так и называется
    }

    void Ball::disableGhost()
    {
        ghostMode = false;
        setTexture(TEXTURES_PATH + "ball.png");
    }
}
