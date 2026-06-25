#pragma once

namespace EngineGame
{
class Scene
{
public:
    // Minimal scene contract used by the application and game-level restart logic.
    virtual void Start() = 0;
    virtual void Restart() = 0;
    virtual void Stop() = 0;
};
} // namespace EngineGame
