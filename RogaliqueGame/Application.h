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
	private:
		std::unique_ptr<GameScene> scene;

		void CreateScene();

	public:
		void run();
	};
}
