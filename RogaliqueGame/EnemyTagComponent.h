#pragma once
#include "Component.h"

namespace RogaliqueGame
{
class EnemyTagComponent : public EngineGame::Component
{
public:
    EnemyTagComponent(EngineGame::GameObject* gameObject);
    ~EnemyTagComponent() override = default;
    void Update(float deltaTime) override;
    void Render() override;
};
}