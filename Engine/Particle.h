#pragma once

#include "Vector.h"
#include <SFML/Graphics/Color.hpp>

namespace EngineGame
{
struct Particle
{
    Vector2Df position = {0.f, 0.f};
    Vector2Df velocity = {0.f, 0.f};

    float lifetime = 0.f;
    float maxLifetime = 0.f;
    float size = 3.f;

    sf::Color color = sf::Color::White;
};
} // namespace EngineGame