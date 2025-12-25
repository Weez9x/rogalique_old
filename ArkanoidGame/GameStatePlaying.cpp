#include "GameStatePlaying.h"
#include "GameSettings.h"
#include "CrackedBrick.h"
#include "BonusFactory.h"
#include <cstdlib>
#include <cmath>

namespace Arkanoid
{
    GameStatePlaying::GameStatePlaying()
        : platform(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT - 50.f),
        ball(SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f)
    {
        lifeSystem.reset(1);
        buildBricks();
    }

    void GameStatePlaying::onEnter()
    {
        font.loadFromFile(FONTS_PATH + "Roboto-Regular.ttf");

        infoText.setFont(font);
        infoText.setCharacterSize(18);
        infoText.setFillColor(sf::Color::White);
        infoText.setPosition(10.f, 10.f);
        infoText.setString("ESC - to menu");

        livesText.setFont(font);
        livesText.setCharacterSize(18);
        livesText.setFillColor(sf::Color::White);
        livesText.setPosition(150.f, 10.f);

        scoreText.setFont(font);
        scoreText.setCharacterSize(18);
        scoreText.setFillColor(sf::Color::White);
        scoreText.setPosition(250.f, 10.f);

        bonusText.setFont(font);
        bonusText.setCharacterSize(18);
        bonusText.setFillColor(sf::Color::Cyan);
        bonusText.setPosition(500.f, 10.f);
    }

    void GameStatePlaying::handleEvent(const sf::Event& event)
    {
        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Escape)
                requestToMainMenu = true;
        }
    }

    void GameStatePlaying::trySpawnBonus(const sf::FloatRect& blockBounds)
    {
        if (std::rand() % 100 < 10)
        {
            float bx = blockBounds.left + blockBounds.width / 2.f;
            float by = blockBounds.top + blockBounds.height / 2.f;

            auto bonus = BonusFactory::createRandomBonus(bx, by);
            if (bonus)
                bonuses.emplace_back(std::move(bonus));
        }
    }

    void GameStatePlaying::update(float dt)
    {
        if (isGameOver || isWin) return;

        effectManager.update(dt, ball, platform, *this);

        platform.update(dt);
        ball.update(dt, platform.getBounds());

        sf::FloatRect ballBounds = ball.getBounds();

        // обновляем бонусы (падение и подбор)
        for (auto& b : bonuses)
        {
            if (!b->isActive()) continue;

            b->update(dt);

            sf::FloatRect platformBounds = platform.getBounds();
            sf::FloatRect topHalf = platformBounds;
            topHalf.height *= 0.5f;

            if (b->getBounds().intersects(topHalf))
            {
                b->applyEffect(effectManager, ball, platform, *this);
                b->deactivate();
            }
            else if (b->getBounds().top > SCREEN_HEIGHT)
            {
                b->deactivate();
            }
        }

        // прогноз следующего положения
        sf::FloatRect nextPos = ballBounds;
        sf::Vector2f vel = ball.getVelocity();
        nextPos.left += vel.x * dt;
        nextPos.top += vel.y * dt;

        // столкновение с кирпичами
        for (auto& brick : bricks)
        {
            if (!brick->isActive()) continue;

            sf::FloatRect br = brick->getBounds();

            if (nextPos.intersects(br))
            {
                // Fireball: убиваем этот и до 3 соседних
                if (ball.isFireball())
                {
                    int destroyed = 0;
                    for (auto& b2 : bricks)
                    {
                        if (!b2->isActive()) continue;
                        sf::FloatRect br2 = b2->getBounds();

                        // в небольшой окрестности
                        if (std::abs(br2.top - br.top) <= BRICK_HEIGHT &&
                            std::abs(br2.left - br.left) <= BRICK_WIDTH * 1.5f)
                        {
                            b2->destroy();
                            addScore(50);
                            destroyed++;
                            if (destroyed >= 4) break;
                        }
                    }
                    trySpawnBonus(br);
                    ball.reflectY();
                    break;
                }

                // Ghost ball: разрушает и летит дальше без отражения
                if (ball.isGhost())
                {
                    brick->destroy();
                    addScore(10);
                    trySpawnBonus(br);
                    continue;
                }

                // обычный мяч
                brick->destroy();
                addScore(10);
                trySpawnBonus(br);

                sf::FloatRect bb = ball.getBounds();

                float overlapLeft = (bb.left + bb.width) - br.left;
                float overlapRight = (br.left + br.width) - bb.left;
                float overlapTop = (bb.top + bb.height) - br.top;
                float overlapBottom = (br.top + br.height) - bb.top;

                bool fromLeft = std::abs(overlapLeft) < std::abs(overlapRight);
                bool fromTop = std::abs(overlapTop) < std::abs(overlapBottom);

                float minOverlapX = fromLeft ? overlapLeft : -overlapRight;
                float minOverlapY = fromTop ? overlapTop : -overlapBottom;

                if (std::abs(minOverlapX) < std::abs(minOverlapY))
                    ball.reflectX();
                else
                    ball.reflectY();

                break;
            }
        }

        // победа?
        bool allDead = true;
        for (auto& b : bricks)
        {
            if (b->isActive())
            {
                allDead = false;
                break;
            }
        }
        if (allDead)
            isWin = true;

        // проверка потери шара
        if (ball.lost())
        {
            if (lifeSystem.consumeLife())
            {
                ball.reset();
                platform.reset();
            }
            else
            {
                isGameOver = true;
            }
        }

        // HUD
        livesText.setString("Lives: " + std::to_string(lifeSystem.getLives()));
        scoreText.setString("Score: " + std::to_string(score));

        if (effectManager.hasActiveBonus())
        {
            int t = static_cast<int>(std::ceil(effectManager.getRemainingTime()));
            bonusText.setString("Bonus: " + effectManager.getActiveBonusName() +
                " (" + std::to_string(t) + "s)");
        }
        else
        {
            bonusText.setString("Bonus: None");
        }
    }

    void GameStatePlaying::draw(sf::RenderWindow& window)
    {
        platform.draw(window);
        ball.draw(window);

        for (auto& brick : bricks)
            brick->draw(window);

        for (auto& b : bonuses)
            b->draw(window);

        window.draw(infoText);
        window.draw(livesText);
        window.draw(scoreText);
        window.draw(bonusText);
    }

    void GameStatePlaying::buildBricks()
    {
        bricks.clear();

        const float gap = 5.f;
        float totalWidth = BRICK_COLUMNS * BRICK_WIDTH + (BRICK_COLUMNS - 1) * gap;
        float startX = (SCREEN_WIDTH - totalWidth) / 2.f + BRICK_WIDTH / 2.f;
        float startY = 80.f;

        for (int i = 0; i < BRICK_ROWS; ++i)
        {
            for (int j = 0; j < BRICK_COLUMNS; ++j)
            {
                float x = startX + j * (BRICK_WIDTH + gap);
                float y = startY + i * (BRICK_HEIGHT + gap);
                int typeIndex = i % 5;

                if ((i + j) % 4 == 0)
                    bricks.emplace_back(std::make_unique<CrackedBrick>(x, y, BRICK_WIDTH, BRICK_HEIGHT, typeIndex));
                else
                    bricks.emplace_back(std::make_unique<Brick>(x, y, BRICK_WIDTH, BRICK_HEIGHT, typeIndex));
            }
        }
    }
}
