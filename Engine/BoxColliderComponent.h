#pragma once

#include "ColliderComponent.h"
#include "TransformComponent.h"
#include "RenderSystem.h"
#include "Vector.h"

namespace EngineGame
{
class BoxColliderComponent : public ColliderComponent
{
public:
    BoxColliderComponent(GameObject* gameObject);
    ~BoxColliderComponent();

    void Update(float deltaTime) override;
    void Render() override;

    void SetSize(float width, float height);
    void SetOffset(float x, float y);
    bool IsDebugVisible() const;

private:
    TransformComponent* transform = nullptr;
    bool isDebugVisible = true;
    // Size and offset are local to the owning transform.
    Vector2Df size = {32.f, 48.f};
    Vector2Df offset = {0.f, 0.f};
};
} // namespace EngineGame
