#pragma once
#include <memory>
#include <vector>
#include "FloorTile.h"
#include "Wall.h"
#include "MazeGenerator.h"

namespace RogaliqueGame
{
class LevelBuilder
{
public:
    void BuildLevel();
    const std::vector<EngineGame::Vector2Df>& GetFloorPositions() const;
    EngineGame::Vector2Df GetRandomFloorPosition() const;
    EngineGame::Vector2Df GetRandomFloorPositionFarFrom(const EngineGame::Vector2Df& avoidPosition, float minDistance) const;

private:
    std::vector<std::unique_ptr<FloorTile>> floorTiles;
    std::vector<std::unique_ptr<Wall>> walls;
    std::vector<EngineGame::Vector2Df> floorPositions;
    float levelWidth = 0.f;
    float levelHeight = 0.f;
    bool IsWall(const std::vector<std::vector<MazeCell>>& maze, int col, int row) const;
    int GetWallTileIndex(const std::vector<std::vector<MazeCell>>& maze, int col, int row) const;
};
} // namespace RogaliqueGame