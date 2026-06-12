#pragma once

#include "Component.h"
#include "TransformComponent.h"

#include <SFML/Graphics.hpp>

namespace EngineGame
{
class LightAuraComponent : public Component
{
public:
    LightAuraComponent(GameObject* gameObject);

    void Update(float deltaTime) override;
    void Render() override;

    void SetActive(bool value);
    bool IsActive() const;

    void SetColor(sf::Color color);
    void SetRadius(float value);
    void SetPulse(float speed, float strength);

private:
    TransformComponent* transform = nullptr;

    bool isActive = false;

    sf::Color color = sf::Color(80, 255, 120, 80);

    float baseRadius = 45.f;
    float pulseSpeed = 5.f;
    float pulseStrength = 8.f;

    float pulseTimer = 0.f;
};
} // namespace EngineGame