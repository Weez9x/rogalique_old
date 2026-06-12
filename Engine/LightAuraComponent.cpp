#include "pch.h"
#include "LightAuraComponent.h"

#include "GameObject.h"
#include "RenderSystem.h"
#include "Logger.h"

#include <cmath>

namespace EngineGame
{
LightAuraComponent::LightAuraComponent(GameObject* gameObject) : Component(gameObject)
{
    transform = gameObject->GetComponent<TransformComponent>();

    if (transform == nullptr)
    {
        Logger::Instance()->Warning("LightAuraComponent requires TransformComponent");
    }
}

void LightAuraComponent::Update(float deltaTime)
{
    if (!isActive)
    {
        return;
    }

    pulseTimer += deltaTime;
}

void LightAuraComponent::Render()
{
    if (!isActive || transform == nullptr)
    {
        return;
    }

    float pulse = (std::sin(pulseTimer * pulseSpeed) + 1.f) * 0.5f;

    float radius = baseRadius + pulse * pulseStrength;

    sf::Color currentColor = color;
    currentColor.a = static_cast<sf::Uint8>(color.a * (0.6f + pulse * 0.4f));

    sf::CircleShape aura;
    aura.setRadius(radius);
    aura.setOrigin(radius, radius);
    aura.setFillColor(currentColor);

    auto position = transform->GetWorldPosition();
    aura.setPosition(position.x, position.y);

    RenderSystem::Instance()->GetMainWindow().draw(aura);
}

void LightAuraComponent::SetActive(bool value)
{
    isActive = value;

    if (!isActive)
    {
        pulseTimer = 0.f;
    }
}

bool LightAuraComponent::IsActive() const
{
    return isActive;
}

void LightAuraComponent::SetColor(sf::Color newColor)
{
    color = newColor;
}

void LightAuraComponent::SetRadius(float value)
{
    if (value <= 0.f)
    {
        Logger::Instance()->Warning("LightAuraComponent radius must be positive.");
        return;
    }

    baseRadius = value;
}

void LightAuraComponent::SetPulse(float speed, float strength)
{
    if (speed < 0.f)
    {
        speed = 0.f;
    }

    if (strength < 0.f)
    {
        strength = 0.f;
    }

    pulseSpeed = speed;
    pulseStrength = strength;
}
} // namespace EngineGame