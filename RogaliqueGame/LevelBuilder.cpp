#include "LevelBuilder.h"
#include "Vector.h"
#include "GameSettings.h"

namespace RogaliqueGame
{
	void LevelBuilder::BuildLevel()
	{
		const int tileSize = 64;
		const int halfTile = tileSize / 2;

		// Координаты центров крайних тайлов
		const int left = halfTile;
		const int top = halfTile;
		const int right = SCREEN_WIDTH - halfTile;
		const int bottom = SCREEN_HEIGHT - halfTile;

		// Сколько тайлов помещается по центрам
		const int cols = (right - left) / tileSize + 1;
		const int rows = (bottom - top) / tileSize + 1;

		// Пол — по всей области, включая пространство под стенами
		for (int row = 0; row <= rows; ++row)
		{
			for (int col = 0; col <= cols; ++col)
			{
				const int x = left + col * tileSize;
				const int y = top + row * tileSize;

				floorTiles.push_back(std::make_unique<FloorTile>(EngineGame::Vector2Df((float)x, (float)y),tileSize,tileSize,0));
			}
		}

		// Верхняя и нижняя стены
		for (int col = 0; col < cols; ++col)
		{
			const int x = left + col * tileSize;

			walls.push_back(std::make_unique<Wall>(EngineGame::Vector2Df((float)x, (float)top),tileSize,tileSize));

			walls.push_back(std::make_unique<Wall>(EngineGame::Vector2Df((float)x, (float)bottom),tileSize,tileSize));
		}

		// Левая и правая стены, без повторения углов
		for (int row = 1; row < rows - 1; ++row)
		{
			const int y = top + row * tileSize;

			walls.push_back(std::make_unique<Wall>(EngineGame::Vector2Df((float)left, (float)y),tileSize,tileSize));

			walls.push_back(std::make_unique<Wall>(EngineGame::Vector2Df((float)right, (float)y),tileSize,tileSize));
		}
	}
}