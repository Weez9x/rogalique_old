#pragma once

#include "Component.h"
#include "TransformComponent.h"

namespace EngineGame
{
class FollowTransformComponent : public Component
{
public:
    FollowTransformComponent(GameObject* gameObject);

    void Update(float deltaTime) override;
    void Render() override;

    void SetTarget(TransformComponent* newTarget);

private:
    TransformComponent* transform = nullptr;
    TransformComponent* target = nullptr;
};
} // namespace EngineGame