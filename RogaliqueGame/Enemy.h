#pragma once

#include "Character.h"

namespace RogaliqueGame
{
class Enemy : public Character
{
public:
    Enemy() = default;
    virtual ~Enemy() = default;
};
} // namespace RogaliqueGame