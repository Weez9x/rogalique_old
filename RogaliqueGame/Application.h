#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

#include "Engine.h"
#include "RenderSystem.h"
#include "GameScene.h"

namespace RogaliqueGame
{
class Application
{
public:
    void run();

private:
    // The game currently owns a single scene and rebuilds its content between levels.
    void CreateScene();

    std::unique_ptr<GameScene> scene;
};
} // namespace RogaliqueGame
