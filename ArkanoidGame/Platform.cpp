#include "Platform.h"

namespace Arkanoid
{
    Platform::Platform(float x, float y)
        : speed(PLATFORM_SPEED)
    {
        shape.setSize({ PLATFORM_WIDTH, PLATFORM_HEIGHT });
        shape.setOrigin(PLATFORM_WIDTH / 2.f, PLATFORM_HEIGHT / 2.f);
        shape.setPosition(x, y);
        setTexture(TEXTURES_PATH + "platform.png");
    }

    void Platform::update(float dt)
    {
        if (!active) return;

        float dir = 0.f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            dir -= 1.f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            dir += 1.f;

        auto pos = shape.getPosition();
        pos.x += dir * speed * dt;

        float halfW = shape.getSize().x / 2.f;

        if (pos.x - halfW < 0.f)
            pos.x = halfW;
        if (pos.x + halfW > SCREEN_WIDTH)
            pos.x = SCREEN_WIDTH - halfW;

        shape.setPosition(pos);
    }
}
