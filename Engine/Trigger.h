#pragma once

namespace EngineGame
{
class ColliderComponent;
// Trigger is a lightweight overlap event for one trigger collider and one solid collider.
struct Trigger
{
public:
    ColliderComponent* GetFirst() const;
    ColliderComponent* GetSecond() const;
    Trigger(ColliderComponent* newFirst, ColliderComponent* newSecond) : first(newFirst), second(newSecond) {};

private:
    ColliderComponent* first;
    ColliderComponent* second;
};
} // namespace EngineGame
