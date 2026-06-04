#include "GameStateUIComponent.h"

#include "GameScene.h"
#include "GameSettings.h"
#include "GameState.h"
#include "GameStateManager.h"
#include "RenderSystem.h"

#include <SFML/Window/Keyboard.hpp>

namespace RogaliqueGame
{
GameStateUIComponent::GameStateUIComponent(EngineGame::GameObject* gameObject) : Component(gameObject)
{
    font.loadFromFile(FONTS_PATH + "ARCADEPI.ttf");

    text.setFont(font);
    text.setCharacterSize(48);
    text.setFillColor(sf::Color::White);

    overlay.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
    overlay.setFillColor(sf::Color(0, 0, 0, 170));
}

void GameStateUIComponent::Update(float deltaTime)
{
    bool rPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::R);
    bool escPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Escape);

    GameState state = GameStateManager::GetState();

    if (state == GameState::Win)
    {
        text.setString("YOU WIN\n\n"
                       "R - NEXT LEVEL\n"
                       "ESC - EXIT");
    }
    else if (state == GameState::GameOver)
    {
        text.setString("GAME OVER\n\n"
                       "R - RESTART\n"
                       "ESC - EXIT");
    }
    else
    {
        text.setString("");
    }

    sf::FloatRect bounds = text.getLocalBounds();

    text.setOrigin(bounds.left + bounds.width * 0.5f, bounds.top + bounds.height * 0.5f);

    text.setPosition(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f);

    if (state == GameState::Win && rPressed && !rPressedLastFrame)
    {
        rPressedLastFrame = rPressed;
        escPressedLastFrame = escPressed;

        GameScene::NextLevel();
        return;
    }

    if (state == GameState::GameOver && rPressed && !rPressedLastFrame)
    {
        rPressedLastFrame = rPressed;
        escPressedLastFrame = escPressed;

        GameScene::RestartLevel();
        return;
    }

    if ((state == GameState::Win || state == GameState::GameOver) && escPressed && !escPressedLastFrame)
    {
        EngineGame::RenderSystem::Instance()->GetMainWindow().close();
        return;
    }

    rPressedLastFrame = rPressed;
    escPressedLastFrame = escPressed;
}

void GameStateUIComponent::Render()
{
    if (GameStateManager::GetState() == GameState::Playing)
    {
        return;
    }

    auto& window = EngineGame::RenderSystem::Instance()->GetMainWindow();

    sf::View currentView = window.getView();

    window.setView(window.getDefaultView());

    window.draw(overlay);
    window.draw(text);

    window.setView(currentView);
}
} // namespace RogaliqueGame