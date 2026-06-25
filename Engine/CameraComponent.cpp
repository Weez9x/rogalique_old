#include "pch.h"
#include "CameraComponent.h"
#include "TransformComponent.h"
#include "CameraShakeComponent.h"

namespace EngineGame
{
CameraComponent::CameraComponent(GameObject* gameObject) : Component(gameObject)
{
    view = sf::View(sf::FloatRect(0, 0, 800, 600));
    transform = gameObject->GetComponent<TransformComponent>();
}

void CameraComponent::Update(float deltaTime)
{
    // Camera position and rotation come from the same Transform system as gameplay objects.
    auto position = transform->GetWorldPosition();
    auto rotation = transform->GetWorldRotation();

    auto shake = gameObject->GetComponent<CameraShakeComponent>();
    if (shake != nullptr)
    {
        auto offset = shake->GetOffset();

        position.x += offset.x;
        position.y += offset.y;
    }

    view.setCenter(Convert<sf::Vector2f, Vector2Df>(position));
    view.setRotation(rotation);

    if (window != nullptr)
    {
        window->setView(view);
    }
}
void CameraComponent::Render()
{
    if (window == nullptr)
    {
        std::cout << "NULL window render." << std::endl;
    }
}

void CameraComponent::SetBaseResolution(int width, int height)
{
    view.reset(sf::FloatRect(0, 0, width, height));
}
void CameraComponent::SetWindow(sf::RenderWindow* newWindow)
{
    window = newWindow;
}
void CameraComponent::ZoomBy(float newZoom)
{
    if (newZoom <= 0)
    {
        std::cout << "Not allowed zoom lesser or equal than zero." << std::endl;
        return;
    }
    view.zoom(newZoom);
}
} // namespace EngineGame
