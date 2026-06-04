#pragma once
#define NOMINMAX

#include "SFML/Graphics.hpp"

namespace EngineGame
{
class Engine
{
public:
    Engine(const Engine& app) = delete;
    Engine& operator=(const Engine&) = delete;

    static Engine* Instance();

    // Runs the main SFML loop until the window is closed.
    void Run();

private:
    Engine();
    ~Engine() = default;
};
} // namespace EngineGame
