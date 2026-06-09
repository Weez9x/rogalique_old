#include "pch.h"
#include "CameraShakeComponent.h"
#include <random>

namespace EngineGame
{
CameraShakeComponent::CameraShakeComponent(GameObject* gameObject) : Component(gameObject) {}
void CameraShakeComponent::Shake(float duration, float strength)
{
    if (duration <= 0.f || strength <= 0.f)
    {
        return;
    }
    shakeTimer = duration;
    shakeStrength = strength;
    shakeDuration = duration;
}
void CameraShakeComponent::Update(float deltaTime)
{
    if (shakeTimer <= 0.f)
    {
        shakeOffset = {0.f, 0.f};
        return;
    }
    else
    {
        shakeTimer -= deltaTime;
        if (shakeTimer <= 0.f)
        {
            shakeTimer = 0.f;
            shakeOffset = {0.f, 0.f};
            return;
        }
        float progress = shakeTimer / shakeDuration;
        float currentStrength = shakeStrength * progress;

        float x = ((float)rand() / RAND_MAX) * 2.f - 1.f;
        float y = ((float)rand() / RAND_MAX) * 2.f - 1.f;

        x *= currentStrength;
        y *= currentStrength;

        shakeOffset = {x, y};
    }
}
void CameraShakeComponent::Render() {}
Vector2Df CameraShakeComponent::GetOffset() const
{
    return shakeOffset;
}
} // namespace EngineGame