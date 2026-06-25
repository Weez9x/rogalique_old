#include "HealthBarComponent.h"

#include "GameObject.h"
#include "RenderSystem.h"
#include "Logger.h"

#include <cassert>
#include <algorithm>

namespace RogaliqueGame
{
HealthBarComponent::HealthBarComponent(EngineGame::GameObject* gameObject) : Component(gameObject)
{
    transform = gameObject->GetComponent<EngineGame::TransformComponent>();
    health = gameObject->GetComponent<EngineGame::HealthComponent>();

    if (transform == nullptr)
    {
        EngineGame::Logger::Instance()->Error("HealthBarComponent requires TransformComponent");
    }

    if (health == nullptr)
    {
        EngineGame::Logger::Instance()->Error("HealthBarComponent requires HealthComponent");
    }

    assert(transform != nullptr && "HealthBarComponent requires TransformComponent");
    assert(health != nullptr && "HealthBarComponent requires HealthComponent");

    background.setFillColor(sf::Color(40, 40, 40));
    fill.setFillColor(sf::Color::Red);
}

void HealthBarComponent::Update(float deltaTime)
{
    if (transform == nullptr || health == nullptr)
    {
        return;
    }

    float healthPercent = health->GetHealth() / maxHealth;
    healthPercent = std::clamp(healthPercent, 0.0f, 1.0f);

    // The bar is rendered in world space so it follows the enemy under the camera.
    EngineGame::Vector2Df position = transform->GetWorldPosition();

    background.setSize(sf::Vector2f(size.x, size.y));
    background.setOrigin(size.x * 0.5f, size.y * 0.5f);
    background.setPosition(position.x + offset.x, position.y + offset.y);

    fill.setSize(sf::Vector2f(size.x * healthPercent, size.y));
    fill.setOrigin(size.x * 0.5f, size.y * 0.5f);
    fill.setPosition(position.x + offset.x, position.y + offset.y);
}

void HealthBarComponent::Render()
{
    EngineGame::RenderSystem::Instance()->Render(background);
    EngineGame::RenderSystem::Instance()->Render(fill);
}

void HealthBarComponent::SetMaxHealth(float value)
{
    if (value <= 0.0f)
    {
        EngineGame::Logger::Instance()->Warning("HealthBarComponent max health must be positive.");
        return;
    }

    maxHealth = value;
}

void HealthBarComponent::SetOffset(float x, float y)
{
    offset = {x, y};
}

void HealthBarComponent::SetSize(float width, float height)
{
    size = {width, height};
}
} // namespace RogaliqueGame
