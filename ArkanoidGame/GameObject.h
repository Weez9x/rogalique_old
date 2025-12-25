#pragma once
#include <SFML/Graphics.hpp>

namespace Arkanoid
{
	class GameObject
	{
	protected:
		sf::RectangleShape shape;
		sf::Texture texture;
		bool active = true;

	public:
		GameObject() = default;
		virtual ~GameObject() = default;

		virtual void update(float /*dt*/) {}
		virtual void draw(sf::RenderWindow& window) const
		{
			if (active)
				window.draw(shape);
		}

		virtual sf::FloatRect getBounds() const
		{
			return shape.getGlobalBounds();
		}

		bool isActive() const { return active; }
		void deactivate() { active = false; }

		void setTexture(const std::string& path)
		{
			if (texture.loadFromFile(path))
			{
				shape.setTexture(&texture);
			}
		}

		virtual void destroy() { deactivate(); }
	};
}
