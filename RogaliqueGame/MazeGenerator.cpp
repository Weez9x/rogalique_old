#include "MazeGenerator.h"

#include <cstdlib>
#include <ctime>

namespace RogaliqueGame
{
MazeGenerator::MazeGenerator(int width, int height) : width(width), height(height) {}

std::vector<std::vector<MazeCell>> MazeGenerator::Generate()
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    visited = std::vector<std::vector<bool>>(height, std::vector<bool>(width, false));

    maze = std::vector<std::vector<MazeCell>>(height, std::vector<MazeCell>(width, MazeCell::Wall));

    int startX = 1;
    int startY = 1;

    std::stack<std::pair<int, int>> stack;
    stack.push({startX, startY});

    visited[startY][startX] = true;
    maze[startY][startX] = MazeCell::Floor;

    // Depth-first backtracking keeps the maze fully connected without isolated rooms.
    while (!stack.empty())
    {
        auto [x, y] = stack.top();

        std::vector<std::pair<int, int>> directions = GetAvailableDirections(x, y);

        if (directions.empty())
        {
            stack.pop();
            continue;
        }

        std::pair<int, int> direction = directions[std::rand() % directions.size()];

        int nextX = x + direction.first;
        int nextY = y + direction.second;

        RemoveWall(x, y, nextX, nextY);

        visited[nextY][nextX] = true;
        maze[nextY][nextX] = MazeCell::Floor;

        stack.push({nextX, nextY});
    }
    ExpandPassages();
    return maze;
}

std::vector<std::pair<int, int>> MazeGenerator::GetAvailableDirections(int x, int y)
{
    std::vector<std::pair<int, int>> directions = {{0, -2}, {0, 2}, {-2, 0}, {2, 0}};

    std::vector<std::pair<int, int>> available;

    for (const auto& direction : directions)
    {
        int nextX = x + direction.first;
        int nextY = y + direction.second;

        if (IsInside(nextX, nextY) && !visited[nextY][nextX])
        {
            available.push_back(direction);
        }
    }

    return available;
}

void MazeGenerator::RemoveWall(int x1, int y1, int x2, int y2)
{
    // The algorithm jumps by two cells, so the middle cell is the wall to carve.
    int wallX = (x1 + x2) / 2;
    int wallY = (y1 + y2) / 2;

    maze[y1][x1] = MazeCell::Floor;
    maze[wallY][wallX] = MazeCell::Floor;
    maze[y2][x2] = MazeCell::Floor;
}

bool MazeGenerator::IsInside(int x, int y) const
{
    return x > 0 && x < width - 1 && y > 0 && y < height - 1;
}
void MazeGenerator::ExpandPassages()
{
    auto expandedMaze = maze;

    for (int y = 1; y < height - 1; ++y)
    {
        for (int x = 1; x < width - 1; ++x)
        {
            if (maze[y][x] == MazeCell::Floor)
            {
                expandedMaze[y][x] = MazeCell::Floor;

                if (x + 1 < width - 1)
                {
                    expandedMaze[y][x + 1] = MazeCell::Floor;
                }
            }
        }
    }

    maze = expandedMaze;
}
} // namespace RogaliqueGame
