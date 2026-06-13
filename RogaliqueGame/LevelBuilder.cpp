#include "LevelBuilder.h"
#include "Vector.h"
#include "GameSettings.h"
#include "Logger.h"
#include "MazeGenerator.h"
#include "GameProgress.h"
#include <cstdlib>
#include <cmath>

namespace RogaliqueGame
{
void LevelBuilder::BuildLevel()
{
    floorPositions.clear();

    EngineGame::Logger::Instance()->Info("LevelBuilder: building level");

    const int tileSize = TILE_SIZE;

    int levelIndex = GameProgress::CurrentLevel - 1;

    if (levelIndex < 0)
    {
        levelIndex = 0;
    }

    const int mazeWidth = MAZE_WIDTH + levelIndex * 2;
    const int mazeHeight = MAZE_HEIGHT + levelIndex * 2;

    levelWidth = static_cast<float>(mazeWidth * tileSize);
    levelHeight = static_cast<float>(mazeHeight * tileSize);
    EngineGame::Logger::Instance()->Info("Level size: " + std::to_string(mazeWidth) + "x" + std::to_string(mazeHeight));

    MazeGenerator generator(mazeWidth, mazeHeight);
    auto maze = generator.Generate();

    for (int row = 0; row < mazeHeight; ++row)
    {
        for (int col = 0; col < mazeWidth; ++col)
        {
            float x = col * tileSize + tileSize / 2.0f;
            float y = row * tileSize + tileSize / 2.0f;

            if (maze[row][col] == MazeCell::Floor)
            {
                EngineGame::Vector2Df position(x, y);
                floorTiles.push_back(std::make_unique<FloorTile>(EngineGame::Vector2Df(x, y), tileSize, tileSize, 0));
                floorPositions.push_back(position);
            }
            else
            {
                int tileIndex = GetWallTileIndex(maze, col, row);

                floorTiles.push_back(std::make_unique<FloorTile>(EngineGame::Vector2Df(x, y), tileSize, tileSize, 0));

                walls.push_back(std::make_unique<Wall>(EngineGame::Vector2Df(x, y), tileSize, tileSize, tileIndex));
            }
        }
    }

    EngineGame::Logger::Instance()->Info("LevelBuilder: level built");
}
const std::vector<EngineGame::Vector2Df>& LevelBuilder::GetFloorPositions() const
{
    return floorPositions;
}

EngineGame::Vector2Df LevelBuilder::GetRandomFloorPosition() const
{
    if (floorPositions.empty())
    {
        EngineGame::Logger::Instance()->Warning("LevelBuilder has no floor positions.");
        return {0.f, 0.f};
    }

    int index = std::rand() % floorPositions.size();
    return floorPositions[index];
}
EngineGame::Vector2Df LevelBuilder::GetRandomFloorPositionFarFrom(const EngineGame::Vector2Df& avoidPosition,
                                                                  float minDistance) const
{
    if (floorPositions.empty())
    {
        EngineGame::Logger::Instance()->Warning("LevelBuilder has no floor positions.");
        return {0.f, 0.f};
    }

    for (int attempt = 0; attempt < RANDOM_POSITION_ATTEMPTS; ++attempt)
    {
        int index = std::rand() % floorPositions.size();
        EngineGame::Vector2Df position = floorPositions[index];

        // Border padding prevents portals and enemies from appearing half-hidden near walls.
        const float borderPadding = SPAWN_BORDER_PADDING;

        if (position.x < borderPadding || position.y < borderPadding || position.x > levelWidth - borderPadding ||
            position.y > levelHeight - borderPadding)
        {
            continue;
        }

        float dx = position.x - avoidPosition.x;
        float dy = position.y - avoidPosition.y;
        float distance = std::sqrt(dx * dx + dy * dy);

        if (distance >= minDistance)
        {
            return position;
        }
    }

    EngineGame::Logger::Instance()->Warning(
        "Could not find floor position far enough. Returning random floor position.");

    return GetRandomFloorPosition();
}
bool LevelBuilder::IsWall(const std::vector<std::vector<MazeCell>>& maze, int col, int row) const
{
    if (row < 0 || row >= static_cast<int>(maze.size()))
    {
        return false;
    }

    if (col < 0 || col >= static_cast<int>(maze[row].size()))
    {
        return false;
    }

    return maze[row][col] == MazeCell::Wall;
}

int LevelBuilder::GetWallTileIndex(const std::vector<std::vector<MazeCell>>& maze, int col, int row) const
{
    bool up = IsWall(maze, col, row - 1);
    bool down = IsWall(maze, col, row + 1);
    bool left = IsWall(maze, col - 1, row);
    bool right = IsWall(maze, col + 1, row);

    // Pick tile indices by neighboring walls so corners and straight walls look connected.
    if (!up && down && !left && right)
    {
        return 1;
    }

    if (!up && down && left && !right)
    {
        return 3;
    }

    if (up && !down && !left && right)
    {
        return 25;
    }

    if (up && !down && left && !right)
    {
        return 27;
    }

    if (up || down)
    {
        return 12;
    }

    if (left || right)
    {
        return 38;
    }

    return 12;
}
} // namespace RogaliqueGame