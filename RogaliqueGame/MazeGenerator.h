#pragma once

#include <vector>
#include <stack>
#include <utility>

namespace RogaliqueGame
{
enum class MazeCell
{
    Wall,
    Floor
};

class MazeGenerator
{
public:
    MazeGenerator(int width, int height);

    // Generates a connected floor/wall grid that LevelBuilder turns into game objects.
    std::vector<std::vector<MazeCell>> Generate();

private:
    int width = 0;
    int height = 0;

    std::vector<std::vector<bool>> visited;
    std::vector<std::vector<MazeCell>> maze;

    std::vector<std::pair<int, int>> GetAvailableDirections(int x, int y);
    void RemoveWall(int x1, int y1, int x2, int y2);
    bool IsInside(int x, int y) const;

    // Widens carved paths so movement feels less cramped for large sprites.
    void ExpandPassages();
};
} // namespace RogaliqueGame
