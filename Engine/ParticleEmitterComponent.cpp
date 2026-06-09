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
        shape.setFillColor(particle.color);
        shape.setPosition(particle.position.x, particle.position.y);

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
        float alpha = particle.lifetime / particle.maxLifetime;
        color.a = static_cast<sf::Uint8>(alpha * 255);

        particles.push_back(particle);
    }
}

void ParticleEmitterComponent::SetDamageColor(sf::Color color)
{
    damageColor = color;
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