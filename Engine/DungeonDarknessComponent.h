#pragma once

#include "Component.h"
#include "TransformComponent.h"

#include <SFML/Graphics.hpp>

namespace EngineGame
{
class DungeonDarknessComponent : public Component
{
public:
    DungeonDarknessComponent(GameObject* gameObject);

    void Update(float deltaTime) override;
    void Render() override;

    void SetTarget(TransformComponent* newTarget);
    void SetLightRadius(float radius);
    void SetDarknessColor(sf::Color color);

private:
    TransformComponent* target = nullptr;

    sf::RenderTexture darknessTexture;
    sf::Sprite darknessSprite;

    float lightRadius = 160.f;
    sf::Color darknessColor = sf::Color(0, 0, 0, 165);

    unsigned int textureWidth = 0;
    unsigned int textureHeight = 0;

    void EnsureTextureSize();
};
} // namespace EngineGame