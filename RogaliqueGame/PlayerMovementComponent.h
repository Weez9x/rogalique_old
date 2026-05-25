#pragma once

#include "Component.h"
#include "InputComponent.h"
#include "RigidbodyComponent.h"
#include "AnimationComponent.h"
#include "SpriteRendererComponent.h"
#include "HealthComponent.h"

namespace RogaliqueGame
{
class PlayerMovementComponent : public EngineGame::Component
{
public:
    PlayerMovementComponent(EngineGame::GameObject* gameObject);

    void Update(float deltaTime) override;
    void Render() override;

private:
    EngineGame::InputComponent* input = nullptr;
    EngineGame::RigidbodyComponent* rigidbody = nullptr;
    EngineGame::AnimationComponent* animation = nullptr;
    EngineGame::SpriteRendererComponent* spriteRenderer = nullptr;
    EngineGame::HealthComponent* health = nullptr;

    float moveSpeed = 4.0f;
};
} // namespace RogaliqueGame