#pragma once
#include "GameObject.h"
#include <vector>

namespace Arkanoid
{
	class Brick : public GameObject
	{
	private:
		static std::vector<sf::Texture> textures; // общий набор текстур для всех блоков
		int type = 0; // индекс используемой текстуры

	public:
		Brick(float x, float y, float width, float height, int typeIndex);
		virtual void destroy();

		static void loadTextures(); // загрузка набора текстур один раз
		static void unloadTextures();//очистка текстур
	};
}