#include "pch.h"
#include "ParticleEmitterComponent.h"
#include "RenderSystem.h"

namespace EngineGame
{
ParticleEmitterComponent::ParticleEmitterComponent(GameObject* gameObject) : Component(gameObject) {}

void ParticleEmitterComponent::Update(float deltaTime)
{
    for (auto& particle : particles)
    {
        particle.lifetime -= deltaTime;

        particle.velocity.x += particle.acceleration.x * deltaTime;
        particle.velocity.y += particle.acceleration.y * deltaTime;

        particle.position.x += particle.velocity.x * deltaTime;
        particle.position.y += particle.velocity.y * deltaTime;
    }
    particles.erase(
        std::remove_if(particles.begin(), particles.end(), [](const Particle& p) { return p.lifetime <= 0.f; }),
        particles.end());
}

void ParticleEmitterComponent::Render()
{
    auto& window = RenderSystem::Instance()->GetMainWindow();

    for (const auto& particle : particles)
    {
        sf::RectangleShape shape;
        shape.setSize({particle.size, particle.size});
        shape.setPosition(particle.position.x, particle.position.y);
        sf::Color color = particle.color;

        float alpha = particle.lifetime / particle.maxLifetime;
        if (alpha < 0.f)
        {
            alpha = 0.f;
        }
        if (alpha > 1.f)
        {
            alpha = 1.f;
        }

        color.a = static_cast<sf::Uint8>(color.a * alpha);

        shape.setFillColor(color);

        window.draw(shape);
    }
}

void ParticleEmitterComponent::Emit(const Vector2Df& position, int count, sf::Color color)
{
    for (int i = 0; i < count; i++)
    {
        Particle particle;
        particle.position = position;
        particle.velocity = {RandomRange(-100.f, 100.f), RandomRange(-100.f, 100.f)};
        particle.lifetime = 1.f;
        particle.maxLifetime = 0.4f;
        particle.size = RandomRange(2.f, 5.f);
        particle.color = color;

        particles.push_back(particle);
    }
}

void ParticleEmitterComponent::SetDamageColor(sf::Color color)
{
    damageColor = color;
}

void ParticleEmitterComponent::EmitDamage(const Vector2Df& position)
{
    Emit(position, 12, damageColor);
}

void ParticleEmitterComponent::EmitDust(const Vector2Df& position)
{
    for (int i = 0; i < 5; ++i)
    {
        Particle particle;
        particle.position = position;
        particle.velocity = {RandomRange(-30.f, 30.f), RandomRange(-80.f, -30.f)};
        particle.acceleration = {0.f, 180.f};
        particle.lifetime = 0.4f;
        particle.maxLifetime = 0.4f;
        particle.size = RandomRange(2.f, 5.f);
        particle.color = sf::Color(161, 150, 100);
        particle.position.x += RandomRange(-15.f, 15.f);

        particles.push_back(particle);
    }
}

void ParticleEmitterComponent::EmitHeal(const Vector2Df& position)
{
    Emit(position, 16, sf::Color(80, 255, 120, 180));
}

sf::Color ParticleEmitterComponent::GetDamageColor() const
{
    return damageColor;
}

float ParticleEmitterComponent::RandomRange(float min, float max) const
{
    float random = ((float)rand()) / (float)RAND_MAX;
    float range = max - min;
    return min + random * range;
}

} // namespace EngineGame