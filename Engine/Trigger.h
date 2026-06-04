#pragma once

namespace EngineGame
{
class ColliderComponent;
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