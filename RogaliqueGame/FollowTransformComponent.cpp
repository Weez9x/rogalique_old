#include "pch.h"
#include "FollowTransformComponent.h"

#include "GameObject.h"
#include "Logger.h"

namespace EngineGame
{
FollowTransformComponent::FollowTransformComponent(GameObject* gameObject) : Component(gameObject)
{
    transform = gameObject->GetComponent<TransformComponent>();

    if (transform == nullptr)
    {
        Logger::Instance()->Warning("FollowTransformComponent requires TransformComponent");
    }
}

void FollowTransformComponent::Update(float deltaTime)
{
    if (transform == nullptr || target == nullptr)
    {
        return;
    }

    transform->SetWorldPosition(target->GetWorldPosition());
}

void FollowTransformComponent::Render() {}

void FollowTransformComponent::SetTarget(TransformComponent* newTarget)
{
    target = newTarget;
}
} // namespace EngineGame