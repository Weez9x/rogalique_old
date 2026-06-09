#pragma once

#include "Component.h"
#include "Particle.h"
#include <vector>
#include <SFML/Graphics.hpp>

namespace EngineGame
{
class ParticleEmitterComponent : public Component
{
public:
    ParticleEmitterComponent(GameObject* gameObject);

    void Update(float deltaTime) override;
    void Render() override;

    void Emit(const Vector2Df& position, int count, sf::Color color);
    void SetDamageColor(sf::Color color);
    sf::Color GetDamageColor() const;

private:
    std::vector<Particle> particles;
    sf::Color damageColor = sf::Color::Red;
    float RandomRange(float min, float max) const;
};
} // namespace EngineGame