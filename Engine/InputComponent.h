#pragma once

#include "Component.h"
#include <SFML/Window.hpp>

namespace EngineGame
{
class InputComponent : public Component
{
public:
    InputComponent(GameObject* gameObject);

    void Update(float deltaTime) override;
    void Render() override;

    float GetHorizontalAxis() const;
    float GetVerticalAxis() const;

private:
    // Axes are reset and rebuilt from keyboard state every frame.
    float horizontalAxis = 0.f;
    float verticalAxis = 0.f;
};
} // namespace EngineGame
