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
    void CreateScene();

    std::unique_ptr<GameScene> scene;
};
} // namespace RogaliqueGame