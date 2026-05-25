#pragma once
#include <memory>
#include <vector>
#include "FloorTile.h"
#include "Wall.h"

namespace RogaliqueGame
{
class LevelBuilder
{
public:
    void BuildLevel();

private:
    std::vector<std::unique_ptr<FloorTile>> floorTiles;
    std::vector<std::unique_ptr<Wall>> walls;
};
} // namespace RogaliqueGame