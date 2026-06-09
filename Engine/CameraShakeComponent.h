#pragma once
#include "Component.h"
#include "Vector.h"

namespace EngineGame
{
class CameraShakeComponent : public Component
{
public:
    CameraShakeComponent(GameObject* gameObject);

    void Shake(float duration, float strength);
    void Update(float deltaTime) override;
    void Render() override;
    Vector2Df GetOffset() const;

private:
    float shakeTimer = 0.f;
    float shakeDuration = 0.f;
    float shakeStrength = 0.f;
    Vector2Df shakeOffset = {0.f, 0.f};
};
} // namespace EngineGame
