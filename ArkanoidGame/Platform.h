#pragma once
#include "GameObject.h"
#include "GameSettings.h"
#include <SFML/Window/Keyboard.hpp>

namespace Arkanoid
{
    class Platform : public GameObject
    {
    private:
        float speed;

    public:
        Platform(float x, float y);

        void update(float dt) override;

        void reset()
        {
            shape.setSize({ PLATFORM_WIDTH, PLATFORM_HEIGHT });
            shape.setOrigin(PLATFORM_WIDTH / 2.f, PLATFORM_HEIGHT / 2.f);
            shape.setPosition(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT - 50.f);
        }

        void setWidth(float newWidth)
        {
            sf::Vector2f pos = shape.getPosition();
            shape.setSize({ newWidth, PLATFORM_HEIGHT });
            shape.setOrigin(newWidth / 2.f, PLATFORM_HEIGHT / 2.f);
            shape.setPosition(pos);
        }

        float getWidth() const { return shape.getSize().x; }
    };
}
