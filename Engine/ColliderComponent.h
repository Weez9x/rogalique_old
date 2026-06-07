#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <functional>
#include "Component.h"
#include "Collision.h"
#include "Trigger.h"
#include "PhysicsSystem.h"

namespace EngineGame
{
class ColliderComponent : public Component
{
public:
    ColliderComponent(GameObject* gameObject);

    virtual void Update(float deltaTime) = 0;
    virtual void Render() = 0;

    // Triggers notify overlap events but do not resolve physical blocking.
    void SetTrigger(bool newIsTrigger);

    void SubscribeCollision(std::function<void(Collision)> onCollisionAction);
    void UnsubscribeCollision(std::function<void(Collision)> onCollisionAction);

    void SubscribeTriggerEnter(std::function<void(Trigger)> onTriggerEnterAction);
    void UnsubscribeTriggerEnter(std::function<void(Trigger)> onTriggerEnterAction);

    void SubscribeTriggerExit(std::function<void(Trigger)> onTriggerExitAction);
    void UnsubscribeTriggerExit(std::function<void(Trigger)> onTriggerExitAction);

    friend class PhysicsSystem;

    void SetEnabled(bool value);
    bool IsEnabled() const;

protected:
    // PhysicsSystem reads these directly to avoid virtual calls in the collision loop.
    sf::FloatRect bounds;
    bool isTrigger = false;
    bool isEnabled = true;

    void OnCollision(const Collision& collision);
    void OnTriggerEnter(const Trigger& trigger);
    void OnTriggerExit(const Trigger& trigger);

    std::vector<std::function<void(Collision)>> onCollisionActions;
    std::vector<std::function<void(Trigger)>> onTriggerEnterActions;
    std::vector<std::function<void(Trigger)>> onTriggerExitActions;
};
} // namespace EngineGame
