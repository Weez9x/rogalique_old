#include "GameProgress.h"

namespace RogaliqueGame
{
int GameProgress::CurrentLevel = 1;

int GameProgress::CurrentKills = 0;
int GameProgress::RequiredKills = 3;
void GameProgress::NextLevel()
{
    CurrentLevel++;

    CurrentKills = 0;

    RequiredKills += 2;
}
} // namespace RogaliqueGame