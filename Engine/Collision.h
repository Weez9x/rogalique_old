#pragma once

#include <SFML/Graphics.hpp>

namespace EngineGame
{
class ColliderComponent;
// Collision carries the two colliders and their overlap rectangle for non-trigger contacts.
struct Collision
{
public:
    Collision(ColliderComponent* newFirst, ColliderComponent* newSecond, sf::FloatRect newCollisionRect)
        : first(newFirst), second(newSecond), collisionRect(newCollisionRect) {};

private:
    ColliderComponent* first;
    ColliderComponent* second;
    sf::FloatRect collisionRect;
};
} // namespace EngineGame
