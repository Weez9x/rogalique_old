#pragma once

#include "Character.h"

namespace RogaliqueGame
{
class Enemy : public Character
{
public:
    // Marker base for enemy wrappers stored by EnemySpawner.
    Enemy() = default;
    virtual ~Enemy() = default;
};
} // namespace RogaliqueGame
