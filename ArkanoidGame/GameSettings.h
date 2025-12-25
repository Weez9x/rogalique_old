#pragma once
#include <string>

namespace Arkanoid
{
	const std::string RESOURCES_PATH = "Resources/";
	const std::string TEXTURES_PATH = RESOURCES_PATH + "Textures/";
	const std::string FONTS_PATH = RESOURCES_PATH + "Fonts/";
	const std::string SOUNDS_PATH = RESOURCES_PATH + "Sounds/";

	const unsigned int SCREEN_WIDTH = 800;
	const unsigned int SCREEN_HEIGHT = 600;
	const float TIME_PER_FRAME = 1.f / 60.f; // 60 FPS

	const float PLATFORM_WIDTH = 100.f;
	const float PLATFORM_HEIGHT = 20.f;
	const float PLATFORM_SPEED = 400.f;

	const float BALL_RADIUS = 10.f;
	const float BALL_SPEED = 300.f;

	const int BRICK_ROWS = 5;
	const int BRICK_COLUMNS = 10;
	const float BRICK_WIDTH = 70.f;
	const float BRICK_HEIGHT = 25.f;
}
