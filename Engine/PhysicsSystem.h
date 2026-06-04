#pragma once

#include <map>
#include <iostream>
#include "ColliderComponent.h"
#include "RigidbodyComponent.h"
#include "Vector.h"

namespace EngineGame
{
class PhysicsSystem
{
public:
    static PhysicsSystem* Instance();

    void Update();

    float GetFixedDeltaTime() const;
    // Colliders subscribe themselves so physics can stay independent from GameWorld ownership.
    void Subscribe(ColliderComponent* collider);
    void Unsubscribe(ColliderComponent* collider);

private:
    PhysicsSystem() {}
    ~PhysicsSystem() {}

    PhysicsSystem(PhysicsSystem const&) = delete;
    PhysicsSystem& operator=(PhysicsSystem const&) = delete;

    std::vector<ColliderComponent*> colliders;
    // Tracks active trigger pairs to fire enter only once and exit when separated.
    std::map<ColliderComponent*, ColliderComponent*> triggersEnteredPair;

    float fixedDeltaTime = 0.02f;
};
} // namespace EngineGame
