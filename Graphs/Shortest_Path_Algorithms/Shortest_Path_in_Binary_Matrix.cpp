/*
File: Shortest_Path_in_Binary_Matrix.cpp
Date: 2025-10-30 14:28

Problem: Shortest Path in Binary Matrix
Link: https://leetcode.com/problems/shortest-path-in-binary-matrix/description/

Problem Statement:
Given an n x n binary matrix grid, return the length of the shortest clear path in the matrix.
A clear path is from the top-left cell (0, 0) to the bottom-right cell (n-1, n-1) such that:
- All visited cells are 0 (unblocked),
- You may move 8-directionally (horizontal, vertical, diagonal).
If no such path exists, return -1.

-------------------------------------------------
❌ Brute Force
- Idea: DFS/backtracking exploring all paths and tracking minimum length.
- Time complexity: Exponential in the number of cells (worst-case 8^(n^2)).
- Space complexity: O(n^2) recursion stack and visited set.
- Limitations: Prohibitive for even modest n; will TLE.

✅ Optimized Approach
- Idea: Use BFS since all edges have equal weight (1). The first time we reach the target is the shortest path.
- Approach: Standard BFS from (0,0), exploring 8 directions, marking visited on enqueue to avoid revisits.
- Algorithm:
  1) If start or end is blocked, return -1.
  2) Initialize queue with (0,0,dist=1), visited[0][0] = true.
  3) Pop from queue; if it's the target, return dist.
  4) For each of 8 neighbors, if in-bounds, unblocked, and not visited, mark visited and enqueue with dist+1.
  5) If queue empties without reaching target, return -1.
- Time complexity: O(n^2) — each cell visited at most once.
- Space complexity: O(n^2) for visited and queue in the worst case.

💡 Key Pattern:
- BFS on grids with 8-direction movement; mark visited on enqueue; early exit upon reaching target.

ℹ️ Keywords:
- BFS, grid traversal, shortest path, 8 directions, queue.

🗒️ Notes
- Avoid mutating input when practical; use a visited matrix.
- Edge cases: empty grid, 1x1 grid (0 -> 1, 1 -> -1), blocked start/end.
-------------------------------------------------
*/

#include <iostream>
#include <vector>
#include <queue>
#include <tuple>

using namespace std;

class Solution
{
public:
    /**
     * @brief Returns the length of the shortest clear path (8-directional) in a binary matrix.
     * @param grid Reference to an n x n binary matrix (0 = clear, 1 = blocked).
     * @return Length of the shortest path (number of cells), or -1 if no path exists.
     */
    int shortestPathBinaryMatrix(vector<vector<int>> &grid)
    {
        int n = static_cast<int>(grid.size());
        if (n == 0)
            return -1;
        if (grid[0][0] == 1 || grid[n - 1][n - 1] == 1)
            return -1;

        // Direction vectors for 8 moves
        static const int dr[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
        static const int dc[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

        vector<vector<bool>> visited(n, vector<bool>(n, false));
        queue<tuple<int, int, int>> q; // r, c, dist

        visited[0][0] = true;
        q.emplace(0, 0, 1);

        while (!q.empty())
        {
            auto [r, c, dist] = q.front();
            q.pop();

            if (r == n - 1 && c == n - 1)
                return dist;

            for (int k = 0; k < 8; ++k)
            {
                int nr = r + dr[k], nc = c + dc[k];
                if (nr >= 0 && nc >= 0 && nr < n && nc < n &&
                    !visited[nr][nc] && grid[nr][nc] == 0)
                {
                    visited[nr][nc] = true;
                    q.emplace(nr, nc, dist + 1);
                }
            }
        }

        return -1;
    }
};

static void printGrid(const vector<vector<int>> &grid)
{
    for (const auto &row : grid)
    {
        for (int v : row)
            cout << v << ' ';
        cout << '\n';
    }
}

int main()
{
    Solution sol;

    // Example test cases
    vector<vector<vector<int>>> tests = {
        {{0, 1}, {1, 0}},                  // 2
        {{0, 0, 0}, {1, 1, 0}, {1, 1, 0}}, // 4
        {{1, 0}, {0, 0}},                  // -1 (start blocked)
        {{0}},                             // 1 (single clear cell)
        {{1}},                             // -1 (single blocked cell)
        {{0, 0}, {0, 0}}                   // 2
    };

    cout << "Running sample tests:\n\n";
    for (size_t i = 0; i < tests.size(); ++i)
    {
        cout << "Test " << i + 1 << ":\n";
        printGrid(tests[i]);
        int ans = sol.shortestPathBinaryMatrix(tests[i]);
        cout << "Shortest path length = " << ans << "\n\n";
    }

    return 0;
}