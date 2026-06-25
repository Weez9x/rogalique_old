#pragma once

namespace EngineGame
{
class GameObject;

class Component
{
public:
    Component(GameObject* gameObject);
    virtual ~Component();

    // Components are updated and rendered by their owning GameObject each frame.
    virtual void Update(float deltaTime) = 0;
    virtual void Render() = 0;

    GameObject* GetGameObject();

protected:
    GameObject* gameObject;
};
} // namespace EngineGame
