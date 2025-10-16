/*
File: Rotting_Oranges.cpp
Date: 2025-10-13 23:58

Problem: Rotting Oranges
Link: https://leetcode.com/problems/rotting-oranges/description/

Problem Statement:
You are given an m x n grid where each cell can have one of three values:
- 0 representing an empty cell,
- 1 representing a fresh orange, or
- 2 representing a rotten orange.
Every minute, any fresh orange that is 4-directionally adjacent to a rotten
orange becomes rotten. Return the minimum number of minutes that must elapse
until no cell has a fresh orange. If this is impossible, return -1.

-------------------------------------------------
❌ Brute Force
- A more naive approach is not really applicable here. The problem asks for
  the minimum time for a process to spread, which naturally leads to a
  Breadth-First Search (BFS) solution. BFS is the standard, efficient way to
  solve shortest path or level-order problems on unweighted graphs/grids.

✅ Optimized Approach (Multi-Source BFS)
- Idea: This problem can be modeled as finding the shortest time for all
  fresh oranges to be reached by rotten ones. Since the rotting process
  happens simultaneously from all initially rotten oranges, this is a classic
  multi-source BFS problem.
- Approach: We start a single BFS traversal from all rotten oranges at once.
  The "level" of the BFS corresponds to the number of minutes passed.
- Algorithm:
  1. Initialize a queue and add the coordinates of all initially rotten (2)
     oranges.
  2. Count the total number of fresh (1) oranges.
  3. If there are no fresh oranges, the time required is 0.
  4. Start the BFS. The process is level-by-level. A level corresponds to
     one minute.
  5. In each level (minute), dequeue all oranges currently in the queue and
     for each, find its fresh neighbors.
  6. For each fresh neighbor, make it rotten, decrement the `fresh` count,
     and add it to the queue for the next level.
  7. After processing a level, increment the minute counter.
  8. After the BFS is complete, if the `fresh` count is 0, return the total
     minutes. Otherwise, some oranges were unreachable, so return -1.
- Time complexity: O(m * n). Each cell is visited at most once.
- Space complexity: O(m * n). In the worst case, the queue can hold all cells.

💡 Key Pattern:
- Multi-Source BFS on a grid. This pattern is used when a process starts
  from multiple points simultaneously and you need to find the time it takes
  to reach all other points.

ℹ️ Keywords:
- Grid, Matrix, Graph, BFS, Multi-Source BFS, Queue, Level-Order Traversal

🗒️ Notes
- The key is processing the queue level by level to correctly track time.
- It's important to count fresh oranges initially. This helps in the final
  check to see if all fresh oranges could be reached.
-------------------------------------------------
*/

#include <iostream>
#include <vector>
#include <queue>
#include <utility>

using namespace std;

class Solution
{
public:
    /**
     * @brief Calculates the minimum time required for all fresh oranges to rot.
     * @param grid The m x n grid of oranges.
     * @return Minimum minutes to rot all oranges, or -1 if impossible.
     */
    int orangesRotting(vector<vector<int>> &grid)
    {
        int m = grid.size();
        int n = grid[0].size();
        queue<pair<int, int>> q;
        int freshOranges = 0;

        // Step 1: Find all rotten oranges and count fresh ones.
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (grid[i][j] == 2)
                {
                    q.push({i, j});
                }
                else if (grid[i][j] == 1)
                {
                    freshOranges++;
                }
            }
        }

        // Edge case: No fresh oranges to begin with.
        if (freshOranges == 0)
        {
            return 0;
        }

        int minutes = 0;
        int dirs[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

        // Step 2: Start the multi-source BFS.
        while (!q.empty())
        {
            int levelSize = q.size();
            bool rottedThisMinute = false;

            for (int i = 0; i < levelSize; ++i)
            {
                auto [x, y] = q.front();
                q.pop();

                // Explore neighbors.
                for (auto &d : dirs)
                {
                    int nx = x + d[0];
                    int ny = y + d[1];

                    // Check boundaries and if the neighbor is a fresh orange.
                    if (nx >= 0 && nx < m && ny >= 0 && ny < n && grid[nx][ny] == 1)
                    {
                        grid[nx][ny] = 2; // Rot the fresh orange.
                        q.push({nx, ny});
                        freshOranges--;
                        rottedThisMinute = true;
                    }
                }
            }
            // Only increment minutes if at least one orange rotted.
            if (rottedThisMinute)
            {
                minutes++;
            }
        }

        // Step 3: Check if all fresh oranges were reached.
        return freshOranges == 0 ? minutes : -1;
    }
};

void runTest(const string &testName, vector<vector<int>> &grid, int expected)
{
    Solution sol;
    int result = sol.orangesRotting(grid);
    cout << testName << ": " << (result == expected ? "Passed" : "Failed") << endl;
    cout << "  Expected: " << expected << ", Got: " << result << endl;
}

int main()
{
    // Test Case 1
    vector<vector<int>> grid1 = {{2, 1, 1}, {1, 1, 0}, {0, 1, 1}};
    runTest("Test Case 1", grid1, 4);

    // Test Case 2
    vector<vector<int>> grid2 = {{2, 1, 1}, {0, 1, 1}, {1, 0, 1}};
    runTest("Test Case 2 (Impossible)", grid2, -1);

    // Test Case 3
    vector<vector<int>> grid3 = {{0, 2}};
    runTest("Test Case 3 (No Fresh Oranges)", grid3, 0);

    // Test Case 4
    vector<vector<int>> grid4 = {{0}};
    runTest("Test Case 4 (Empty Grid)", grid4, 0);

    // Test Case 5
    vector<vector<int>> grid5 = {{2, 2, 2, 1, 1}};
    runTest("Test Case 5", grid5, 2);

    return 0;
}
