#pragma once

namespace RogaliqueGame
{
class GameProgress
{
public:
    // Progress is reset only on a full GameOver restart, not between levels.
    static void Reset();
    static int CurrentLevel;
    static void NextLevel();
    static int CurrentKills;
    static int RequiredKills;
};
} // namespace RogaliqueGame
