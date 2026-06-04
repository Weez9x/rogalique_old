#include "PlayerStatsUIComponent.h"

#include "GameObject.h"
#include "RenderSystem.h"
#include "Logger.h"
#include "GameSettings.h"
#include "GameProgress.h"

#include <sstream>
#include <string>

namespace RogaliqueGame
{
PlayerStatsUIComponent::PlayerStatsUIComponent(EngineGame::GameObject* gameObject) : Component(gameObject)
{
    health = gameObject->GetComponent<EngineGame::HealthComponent>();
    lives = gameObject->GetComponent<PlayerLivesComponent>();

    if (health == nullptr)
    {
        EngineGame::Logger::Instance()->Warning("PlayerStatsUIComponent requires HealthComponent");
    }

    if (!font.loadFromFile(FONTS_PATH + "ARCADEPI.ttf"))
    {
        EngineGame::Logger::Instance()->Error("Failed to load UI font");
    }

    text.setFont(font);
    text.setCharacterSize(PLAYER_UI_FONT_SIZE);
    text.setFillColor(sf::Color::Red);
    text.setPosition(PLAYER_UI_X, PLAYER_UI_Y);
}

void PlayerStatsUIComponent::Update(float deltaTime)
{
    if (health == nullptr)
    {
        return;
    }

    std::ostringstream stream;
    std::string hearts;

    if (lives != nullptr && lives->GetLives() > 0)
    {
        for (int i = 0; i < lives->GetLives(); ++i)
        {
            hearts += "<3 ";
        }
    }
    else
    {
        hearts = "none";
    }

    stream << "Level: " << GameProgress::CurrentLevel;
    stream << "\nKills: " << GameProgress::CurrentKills << "/" << GameProgress::RequiredKills;
    stream << "\nLives: " << hearts;
    stream << "\nHP: " << health->GetHealth() << "  Armor: " << health->GetArmor();

    text.setString(stream.str());
}

void PlayerStatsUIComponent::Render()
{
    auto& window = EngineGame::RenderSystem::Instance()->GetMainWindow();

    sf::View currentView = window.getView();

    window.setView(window.getDefaultView());

    window.draw(text);

    window.setView(currentView);
}
} // namespace RogaliqueGame
