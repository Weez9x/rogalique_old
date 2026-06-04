#pragma once

#include <SFML/Graphics.hpp>

namespace EngineGame
{
class RenderSystem
{
public:
    static RenderSystem* Instance();

    void SetMainWindow(sf::RenderWindow* newWindow);
    sf::RenderWindow& GetMainWindow() const;

    // Central draw entry keeps components from storing their own window references.
    void Render(const sf::Drawable& drawable);

private:
    sf::RenderWindow* window;

    RenderSystem() {}
    ~RenderSystem() {}

    RenderSystem(RenderSystem const&) = delete;
    RenderSystem& operator=(RenderSystem const&) = delete;
};
} // namespace EngineGame
