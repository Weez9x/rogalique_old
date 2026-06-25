#include "pch.h"
#include "PhysicsSystem.h"

namespace EngineGame
{
PhysicsSystem* PhysicsSystem::Instance()
{
    static PhysicsSystem physicsSystem;
    return &physicsSystem;
}

float PhysicsSystem::GetFixedDeltaTime() const
{
    return fixedDeltaTime;
}

void PhysicsSystem::Update()
{
    for (int i = 0; i < colliders.size(); i++)
    {
        if (!colliders[i]->IsEnabled())
        {
            continue;
        }
        auto body = colliders[i]->GetGameObject()->GetComponent<RigidbodyComponent>();

        if (body == nullptr)
        {
            continue;
        }

        if (body->GetKinematic())
        {
            continue;
        }

        for (int j = 0; j < colliders.size(); j++)
        {
            if (j == i)
            {
                continue;
            }

            if (!colliders[j]->IsEnabled())
            {
                continue;
            }

            sf::FloatRect intersection;
            if (colliders[i]->bounds.intersects(colliders[j]->bounds, intersection))
            {
                if (colliders[i]->isTrigger != colliders[j]->isTrigger)
                {
                    // Trigger pairs are remembered so OnTriggerEnter fires once per overlap.
                    if (triggersEnteredPair.find(colliders[i]) == triggersEnteredPair.end() &&
                        triggersEnteredPair.find(colliders[j]) == triggersEnteredPair.end())
                    {
                        auto trigger = new Trigger(colliders[i], colliders[j]);
                        colliders[i]->OnTriggerEnter(*trigger);
                        colliders[j]->OnTriggerEnter(*trigger);

                        triggersEnteredPair.emplace(colliders[i], colliders[j]);
                    }
                }
                else if (!colliders[i]->isTrigger)
                {
                    // Non-trigger collisions resolve by pushing the moving collider out on the shallowest axis.
                    float intersectionWidth = intersection.width;
                    float intersectionHeight = intersection.height;
                    Vector2Df intersectionPosition = {intersection.left - 0.5f * intersectionWidth,
                                                      intersection.top - 0.5f * intersectionHeight};

                    Vector2Df aPosition = {colliders[i]->bounds.left, colliders[i]->bounds.top};
                    auto aTransform = colliders[i]->GetGameObject()->GetComponent<TransformComponent>();

                    if (intersectionWidth > intersectionHeight)
                    {
                        if (intersectionPosition.y > aPosition.y)
                        {
                            aTransform->MoveBy({0, -intersectionHeight});
                        }
                        else
                        {
                            aTransform->MoveBy({0, intersectionHeight});
                        }
                    }
                    else
                    {
                        if (intersectionPosition.x > aPosition.x)
                        {
                            aTransform->MoveBy({-intersectionWidth, 0.f});
                        }
                        else
                        {
                            aTransform->MoveBy({intersectionWidth, 0.f});
                        }
                    }

                    Collision collision(colliders[i], colliders[j], intersection);
                    colliders[i]->OnCollision(collision);
                    colliders[j]->OnCollision(collision);
                }
            }
        }
    }

    for (auto triggeredPair = triggersEnteredPair.cbegin(), nextTriggeredPair = triggeredPair;
         triggeredPair != triggersEnteredPair.cend(); triggeredPair = nextTriggeredPair)
    {
        ++nextTriggeredPair;
        // Exit fires when either collider is disabled or the pair no longer overlaps.
        if (!triggeredPair->first->IsEnabled() || !triggeredPair->second->IsEnabled() ||
            !triggeredPair->first->bounds.intersects(triggeredPair->second->bounds))
        {
            Trigger trigger(triggeredPair->first, triggeredPair->second);
            triggeredPair->first->OnTriggerExit(trigger);
            triggeredPair->second->OnTriggerExit(trigger);

            triggersEnteredPair.erase(triggeredPair);
        }
    }
}

void PhysicsSystem::Subscribe(ColliderComponent* collider)
{
    colliders.push_back(collider);
}
void PhysicsSystem::Unsubscribe(ColliderComponent* collider)
{
    colliders.erase(std::remove_if(colliders.begin(), colliders.end(),
                                   [collider](ColliderComponent* obj) { return obj == collider; }),
                    colliders.end());

    // Remove stale trigger pairs when an object is destroyed during a scene rebuild.
    for (auto triggeredPair = triggersEnteredPair.cbegin(), nextTriggeredPair = triggeredPair;
         triggeredPair != triggersEnteredPair.cend(); triggeredPair = nextTriggeredPair)
    {
        ++nextTriggeredPair;

        if (triggeredPair->first == collider || triggeredPair->second == collider)
        {
            triggersEnteredPair.erase(triggeredPair);
        }
    }
}
} // namespace EngineGame
