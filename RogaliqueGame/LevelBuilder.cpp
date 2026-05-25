#include "LevelBuilder.h"
#include "Vector.h"
#include "GameSettings.h"
#include "Logger.h"

namespace RogaliqueGame
{
void LevelBuilder::BuildLevel()
{
    EngineGame::Logger::Instance()->Info("LevelBuilder: building level");

    const int tileSize = 64;
    const int halfTile = tileSize / 2;

    const int left = halfTile;
    const int top = halfTile;
    const int right = SCREEN_WIDTH - halfTile;
    const int bottom = SCREEN_HEIGHT - halfTile;

    const int cols = (right - left) / tileSize + 1;
    const int rows = (bottom - top) / tileSize + 1;

    for (int row = 0; row < rows; ++row)
    {
        for (int col = 0; col < cols; ++col)
        {
            const int x = left + col * tileSize;
            const int y = top + row * tileSize;

            floorTiles.push_back(
                std::make_unique<FloorTile>(EngineGame::Vector2Df((float)x, (float)y), tileSize, tileSize, 0));
        }
    }

    for (int col = 0; col < cols; ++col)
    {
        const int x = left + col * tileSize;

        walls.push_back(std::make_unique<Wall>(EngineGame::Vector2Df((float)x, (float)top), tileSize, tileSize));

        walls.push_back(std::make_unique<Wall>(EngineGame::Vector2Df((float)x, (float)bottom), tileSize, tileSize));
    }

    for (int row = 1; row < rows - 1; ++row)
    {
        const int y = top + row * tileSize;

        walls.push_back(std::make_unique<Wall>(EngineGame::Vector2Df((float)left, (float)y), tileSize, tileSize));

        walls.push_back(std::make_unique<Wall>(EngineGame::Vector2Df((float)right, (float)y), tileSize, tileSize));
    }

    EngineGame::Logger::Instance()->Info("LevelBuilder: level built");
}
} // namespace RogaliqueGame