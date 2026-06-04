#include "PlayerMovementComponent.h"
#include "GameObject.h"
#include "GameStateManager.h"
#include "Vector.h"
#include "Logger.h"

#include <cmath>
#include <cassert>

namespace RogaliqueGame
{
PlayerMovementComponent::PlayerMovementComponent(EngineGame::GameObject* gameObject) : Component(gameObject)
{
    input = gameObject->GetComponent<EngineGame::InputComponent>();
    rigidbody = gameObject->GetComponent<EngineGame::RigidbodyComponent>();
    animation = gameObject->GetComponent<EngineGame::AnimationComponent>();
    spriteRenderer = gameObject->GetComponent<EngineGame::SpriteRendererComponent>();
    health = gameObject->GetComponent<EngineGame::HealthComponent>();

    if (input == nullptr)
    {
        EngineGame::Logger::Instance()->Error("PlayerMovementComponent requires InputComponent");
    }

    if (rigidbody == nullptr)
    {
        EngineGame::Logger::Instance()->Error("PlayerMovementComponent requires RigidbodyComponent");
    }

    assert(input != nullptr && "PlayerMovementComponent requires InputComponent");
    assert(rigidbody != nullptr && "PlayerMovementComponent requires RigidbodyComponent");
}

void PlayerMovementComponent::Update(float deltaTime)
{
    if (!GameStateManager::IsPlaying())
    {
        if (rigidbody != nullptr)
        {
            rigidbody->SetLinearVelocity({0.f, 0.f});
        }

        return;
    }

    if (health != nullptr && health->IsDead())
    {
        rigidbody->SetLinearVelocity({0.f, 0.f});

        if (animation != nullptr && !animation->IsCurrentAnimation("death"))
        {
            animation->Play("death");
        }

        return;
    }

    if (input == nullptr || rigidbody == nullptr)
    {
        return;
    }

    EngineGame::Vector2Df direction = {input->GetHorizontalAxis(), input->GetVerticalAxis()};

    bool isMoving = direction.x != 0.0f || direction.y != 0.0f;

    bool canChangeAnimation = true;

    if (animation != nullptr)
    {
        if (animation->IsCurrentAnimation("death") || animation->IsPlaying("attack"))
        {
            canChangeAnimation = false;
        }
    }

    if (spriteRenderer != nullptr && canChangeAnimation)
    {
        if (direction.x < 0.0f)
        {
            spriteRenderer->FlipX(true);
        }
        else if (direction.x > 0.0f)
        {
            spriteRenderer->FlipX(false);
        }
    }

    if (animation != nullptr && canChangeAnimation)
    {
        if (isMoving)
        {
            animation->Play("walk");
        }
        else
        {
            animation->Play("idle");
        }
    }

    if (direction.x != 0.0f || direction.y != 0.0f)
    {
        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        direction.x /= length;
        direction.y /= length;
    }

    rigidbody->SetLinearVelocity(direction * moveSpeed);
}

void PlayerMovementComponent::Render() {}
} // namespace RogaliqueGame
