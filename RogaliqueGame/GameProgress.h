#pragma once

namespace RogaliqueGame
{
class GameProgress
{
public:
    static int CurrentLevel;
    static void NextLevel();
    static int CurrentKills;
    static int RequiredKills;
};
} // namespace RogaliqueGame