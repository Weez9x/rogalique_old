#include "PlayerStatsUIComponent.h"

#include "GameObject.h"
#include "RenderSystem.h"
#include "Logger.h"
#include "GameSettings.h"

#include <sstream>

namespace RogaliqueGame
{
	PlayerStatsUIComponent::PlayerStatsUIComponent(EngineGame::GameObject* gameObject)
		: Component(gameObject)
	{
		health = gameObject->GetComponent<EngineGame::HealthComponent>();

		if (health == nullptr)
		{
			EngineGame::Logger::Instance()->Warning("PlayerStatsUIComponent requires HealthComponent");
		}

		if (!font.loadFromFile(FONTS_PATH + "ARCADEPI.ttf"))
		{
			EngineGame::Logger::Instance()->Error("Failed to load UI font");
		}

		text.setFont(font);
		text.setCharacterSize(22);
		text.setFillColor(sf::Color::Red);
		text.setPosition(20.f, 20.f);
	}

	void PlayerStatsUIComponent::Update(float deltaTime)
	{
		if (health == nullptr)
		{
			return;
		}

		std::ostringstream stream;
		stream << "HP: " << health->GetHealth() << " | Armor: " << health->GetArmor();
		text.setString(stream.str());
	}

	void PlayerStatsUIComponent::Render()
	{
		EngineGame::RenderSystem::Instance()->Render(text);
	}
}