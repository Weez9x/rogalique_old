#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <cstdlib>

namespace Arkanoid
{
    class BonusEffectManager;
    class Ball;
    class Platform;
    class GameStatePlaying;

    class Bonus
    {
    protected:
        sf::Sprite sprite;
        sf::Texture texture;
        bool active = true;
        float fallSpeed = 150.f;
        float duration = 0.f; // секунды

    public:
        Bonus(const std::string& textureFile, float x, float y, float durationSec)
            : duration(durationSec)
        {
            texture.loadFromFile(textureFile);
            sprite.setTexture(texture);
			sprite.setScale(0.5f, 0.5f);
            sprite.setOrigin(
                sprite.getLocalBounds().width / 2.f,
                sprite.getLocalBounds().height / 2.f
            );
            sprite.setPosition(x, y);
        }

        virtual ~Bonus() = default;

        virtual void update(float dt)
        {
            if (!active) return;
            sprite.move(0.f, fallSpeed * dt);
        }

        virtual void draw(sf::RenderWindow& window)
        {
            if (active)
                window.draw(sprite);
        }

        bool isActive() const { return active; }
        void deactivate() { active = false; }

        sf::FloatRect getBounds() const { return sprite.getGlobalBounds(); }

        virtual void applyEffect(BonusEffectManager& mgr, Ball& ball, Platform& platform, GameStatePlaying& state) = 0;

    protected:
        float randomDuration(float minSec = 5.f, float maxSec = 10.f)
        {
            float r = static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX);
            return minSec + r * (maxSec - minSec);
        }
    };
}
