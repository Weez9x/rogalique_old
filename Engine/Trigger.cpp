#include "pch.h"
#include "Trigger.h"
namespace EngineGame
{
ColliderComponent* Trigger::GetFirst() const
{
    return first;
}

ColliderComponent* Trigger::GetSecond() const
{
    return second;
}
} // namespace EngineGame