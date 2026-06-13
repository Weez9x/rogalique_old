#include "pch.h"
#include "DungeonDarknessComponent.h"

#include "RenderSystem.h"
#include "Logger.h"

namespace EngineGame
{
DungeonDarknessComponent::DungeonDarknessComponent(GameObject* gameObject) : Component(gameObject)
{
    EnsureTextureSize();
}

void DungeonDarknessComponent::Update(float deltaTime) {}

void DungeonDarknessComponent::Render()
{
    auto& window = RenderSystem::Instance()->GetMainWindow();

    if (target == nullptr)
    {
        return;
    }

    EnsureTextureSize();

    darknessTexture.clear(darknessColor);

    auto worldPosition = target->GetWorldPosition();

    sf::Vector2i pixelPosition = window.mapCoordsToPixel(sf::Vector2f(worldPosition.x, worldPosition.y));

    const int steps = 16;

    for (int i = 0; i < steps; ++i)
    {
        float t = static_cast<float>(i) / static_cast<float>(steps - 1);

        float radius = lightRadius * (1.f - t * 0.85f);

        sf::Uint8 alpha = static_cast<sf::Uint8>(darknessColor.a * (1-t));

        sf::CircleShape lightCircle(radius);
        lightCircle.setOrigin(radius, radius);
        lightCircle.setPosition(static_cast<float>(pixelPosition.x), static_cast<float>(pixelPosition.y));

        lightCircle.setFillColor(sf::Color(0, 0, 0, alpha));

        darknessTexture.draw(lightCircle, sf::BlendNone);
    }

    darknessTexture.display();

    darknessSprite.setTexture(darknessTexture.getTexture(), true);
    darknessSprite.setPosition(0.f, 0.f);

    sf::View oldView = window.getView();

    window.setView(window.getDefaultView());
    window.draw(darknessSprite);
    window.setView(oldView);
}

void DungeonDarknessComponent::SetTarget(TransformComponent* newTarget)
{
    target = newTarget;

    if (target == nullptr)
    {
        Logger::Instance()->Warning("DungeonDarknessComponent target is null");
    }
}

void DungeonDarknessComponent::SetLightRadius(float radius)
{
    if (radius <= 0.f)
    {
        Logger::Instance()->Warning("DungeonDarknessComponent light radius must be positive.");
        return;
    }

    lightRadius = radius;
}

void DungeonDarknessComponent::SetDarknessColor(sf::Color color)
{
    darknessColor = color;
}

void DungeonDarknessComponent::EnsureTextureSize()
{
    auto& window = RenderSystem::Instance()->GetMainWindow();

    auto size = window.getSize();

    if (size.x == textureWidth && size.y == textureHeight)
    {
        return;
    }

    textureWidth = size.x;
    textureHeight = size.y;

    if (!darknessTexture.create(textureWidth, textureHeight))
    {
        Logger::Instance()->Error("DungeonDarknessComponent failed to create render texture.");
    }
}
} // namespace EngineGame