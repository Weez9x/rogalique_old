#include "LevelBuilder.h"
#include "Vector.h"

namespace RogaliqueGame
{
	void LevelBuilder::BuildLevel()
	{
		const int tileSize = 64;

		const int left = 64;
		const int right = 736;
		const int top = 64;
		const int bottom = 544;

		// Пол
		for (int y = top + tileSize; y <= bottom - tileSize; y += tileSize)
		{
			for (int x = left + tileSize; x <= right - tileSize; x += tileSize)
			{
				floorTiles.push_back(std::make_unique<FloorTile>(EngineGame::Vector2Df((float)x, (float)y),tileSize,tileSize,0));
			}
		}

		// Верх и низ
		for (int x = left; x <= right; x += tileSize)
		{
			walls.push_back(std::make_unique<Wall>(EngineGame::Vector2Df((float)x, (float)top),tileSize,tileSize));

			walls.push_back(std::make_unique<Wall>(EngineGame::Vector2Df((float)x, (float)bottom),tileSize,tileSize));
		}

		// Лево и право
		for (int y = top + tileSize; y <= bottom - tileSize; y += tileSize)
		{
			walls.push_back(std::make_unique<Wall>(EngineGame::Vector2Df((float)left, (float)y),tileSize,tileSize));

			walls.push_back(std::make_unique<Wall>(EngineGame::Vector2Df((float)right, (float)y),tileSize,tileSize));
		}
	}
}