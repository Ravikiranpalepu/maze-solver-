#include <iostream>
#include <vector>

using namespace std;

// Directions for moving in the maze: right, down, left, up
const int directions[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

bool isSafe(int x, int y, const vector<vector<int>>& maze, vector<vector<bool>>& visited) {
    return (x >= 0 && x < maze.size() && y >= 0 && y < maze[0].size() &&
            maze[x][y] == 0 && !visited[x][y]);
}

bool solveMazeUtil(int x, int y, const vector<vector<int>>& maze, vector<vector<bool>>& visited, vector<pair<int, int>>& path) {
    // If we reach the bottom-right corner, we found a path
    if (x == maze.size() - 1 && y == maze[0].size() - 1) {
        path.push_back({x, y});
        return true;
    }

    // Check if the current position is safe
    if (isSafe(x, y, maze, visited)) {
        // Mark the cell as visited
        visited[x][y] = true;
        path.push_back({x, y});

        // Explore all possible directions
        for (int i = 0; i < 4; i++) {
            int newX = x + directions[i][0];
            int newY = y + directions[i][1];

            if (solveMazeUtil(newX, newY, maze, visited, path)) {
                return true;
            }
        }

        // If no direction works, backtrack
        path.pop_back();
        visited[x][y] = false;
    }

    return false;
}

void solveMaze(const vector<vector<int>>& maze) {
    vector<vector<bool>> visited(maze.size(), vector<bool>(maze[0].size(), false));
    vector<pair<int, int>> path;

    if (solveMazeUtil(0, 0, maze, visited, path)) {
        cout << "Path to exit: " << endl;
        for (const auto& p : path) {
            cout << "(" << p.first << ", " << p.second << ") ";
        }
        cout << endl;
    } else {
        cout << "No path found!" << endl;
    }
}

int main() {
    vector<vector<int>> maze = {
        {0, 1, 0, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 0, 1, 0},
        {0, 1, 0, 0, 0},
        {0, 0, 0, 1, 0}
    };

    solveMaze(maze);

    return 0;
}
