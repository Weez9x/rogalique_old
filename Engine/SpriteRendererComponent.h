#pragma once

#include "TransformComponent.h"
#include "Vector.h"
#include <SFML/Graphics.hpp>
#include <memory>

namespace EngineGame
{
class SpriteRendererComponent : public Component
{
public:
    SpriteRendererComponent(GameObject* gameObject);
    ~SpriteRendererComponent();

    void Update(float deltaTime) override;
    void Render() override;

    const sf::Sprite* GetSprite() const;
    void SetTexture(const sf::Texture& newTexture);
    void SetPixelSize(int newWidth, int newHeight);

    void FlipX(bool flip);
    void FlipY(bool flip);

    void SetVisible(bool visible);
    bool IsVisible() const;

    bool IsFlippedX() const;

private:
    // Local scale stores pixel sizing and flips; Transform scale is applied during Render.
    Vector2Df scale;
    sf::Sprite* sprite;
    TransformComponent* transform;

    bool isFlipX = false;
    bool isFlipY = false;

    bool isVisible = true;

    bool isFlippedX = false;
};
} // namespace EngineGame
