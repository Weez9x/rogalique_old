#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

#include "GameState.h"
#include "Platform.h"
#include "Ball.h"
#include "Brick.h"
#include "Bonus.h"
#include "BonusEffectManager.h"
#include "LifeSystem.h"

namespace Arkanoid
{
    class GameStatePlaying : public GameState
    {
    private:
        Platform platform;
        Ball ball;

        std::vector<std::unique_ptr<GameObject>> bricks;
        std::vector<std::unique_ptr<Bonus>> bonuses;

        BonusEffectManager effectManager;
        LifeSystem lifeSystem;

        sf::Font font;
        sf::Text infoText;
        sf::Text livesText;
        sf::Text scoreText;
        sf::Text bonusText;

        bool isGameOver = false;
        bool isWin = false;
        bool requestToMainMenu = false;

        int score = 0;

        void buildBricks();
        void trySpawnBonus(const sf::FloatRect& blockBounds);

    public:
        GameStatePlaying();
        ~GameStatePlaying() override = default;

        void onEnter() override;
        void handleEvent(const sf::Event& event) override;
        void update(float dt) override;
        void draw(sf::RenderWindow& window) override;

        bool gameOver() const { return isGameOver; }
        bool gameWin() const { return isWin; }
        bool shouldGoToMainMenu() const { return requestToMainMenu; }

        LifeSystem& getLifeSystem() { return lifeSystem; }

        void addScore(int v) { score += v; }
        int getScore() const { return score; }
    };
}
