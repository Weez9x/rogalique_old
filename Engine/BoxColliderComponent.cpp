#include "pch.h"
#include "BoxColliderComponent.h"
#include "GameObject.h"
#include "PhysicsSystem.h"
#include "Logger.h"

namespace EngineGame
{
BoxColliderComponent::BoxColliderComponent(GameObject* gameObject) : ColliderComponent(gameObject)
{
    transform = gameObject->GetComponent<TransformComponent>();

    if (transform == nullptr)
    {
        gameObject->RemoveComponent(this);
        Logger::Instance()->Error("BoxColliderComponent requires TransformComponent");
        return;
    }

    PhysicsSystem::Instance()->Subscribe(this);
}

BoxColliderComponent::~BoxColliderComponent()
{
    PhysicsSystem::Instance()->Unsubscribe(this);
}

void BoxColliderComponent::Update(float deltaTime)
{
    Vector2Df position = transform->GetWorldPosition();

    bounds.left = position.x + offset.x - size.x * 0.5f;
    bounds.top = position.y + offset.y - size.y * 0.5f;
    bounds.width = size.x;
    bounds.height = size.y;
}

void BoxColliderComponent::Render()
{
    if (!IsDebugVisible())
    {
        return;
    }
    sf::RectangleShape rectangle(sf::Vector2f(bounds.width, bounds.height));
    rectangle.setPosition(bounds.left, bounds.top);
    rectangle.setFillColor(sf::Color::Transparent);
    rectangle.setOutlineColor(sf::Color::Green);
    rectangle.setOutlineThickness(2.f);

    RenderSystem::Instance()->Render(rectangle);
}

void BoxColliderComponent::SetSize(float width, float height)
{
    size = {width, height};
}

void BoxColliderComponent::SetOffset(float x, float y)
{
    offset = {x, y};
}
bool BoxColliderComponent::IsDebugVisible() const
{
    return isDebugVisible;
}
} // namespace EngineGame