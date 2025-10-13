/*
File: Number_of_Enclaves.cpp
Date: 2025-10-14 01:08

Problem: Number of Enclaves
Link: https://leetcode.com/problems/number-of-enclaves/description/

Problem Statement:
You are given an m x n binary matrix grid, where 0 represents a sea cell and
1 represents a land cell.
A move consists of walking from one land cell to another adjacent (4-directionally)
land cell or walking off the boundary of the grid.
Return the number of land cells that cannot walk off the boundary of the grid.

Example:
Input: grid = [[0,1,1,0],[0,0,1,0],[0,0,1,0],[0,0,0,0]]
Output: 3 (The three '1's in the middle column are trapped)
----------------------------------------------------------------------------------
❌ Brute Force
- Idea: For every land cell, run a separate BFS/DFS to check if it can reach
  any border cell.
- Time complexity: O((m*n)^2) - Up to O(m*n) land cells, each taking O(m*n)
  to check reachability.
- Space complexity: O(m*n) for storing distance matrix or visited set per check.
- Limitations: Extremely inefficient due to repeated calculations.

✅ Optimized Approach
- Idea: Instead of checking every land cell, use Multi-Source BFS starting from
  all land cells on the perimeter. Any land cell not visited by this process
  is an enclave.
- Approach: Multi-Source BFS
- Algorithm:
  1. Count `total` number of land cells (1s).
  2. Initialize a queue with all border land cells. Change their value to 2
     (visited/reachable) and decrement `total`.
  3. Perform BFS: From the queue, explore adjacent land cells (1s).
  4. For every newly reached land cell, change its value to 2, enqueue it,
     and decrement `total`.
  5. The final value of `total` is the number of enclaves.
- Time complexity: O(m*n). Each cell is visited and processed exactly once.
- Space complexity: O(m*n) for the BFS queue.

💡 Key Pattern:
- Connectivity problems involving boundaries: Flood-fill/BFS/DFS from the
  boundaries inwards to mark "exposed" areas.

ℹ️ Keywords:
- BFS, Multi-Source, Grid, Flood Fill, Boundary Traversal

🗒️ Notes
- Reusing the grid (changing 1 to 2) avoids the need for a separate visited array.
- This problem is similar to "Surrounded Regions" (LeetCode 130).
----------------------------------------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    /**
     * @brief Counts the number of land cells (1s) that cannot reach the grid boundary.
     * @param grid The input m x n binary matrix (modified in place: 1 becomes 2).
     * @return The number of land cells that are enclaves.
     */
    int numEnclaves(vector<vector<int>> &grid)
    {
        int m = grid.size();
        int n = grid[0].size();
        // total stores the count of land cells that are not connected to the border
        // (initialized to total land count, and decremented as connected cells are found)
        int total = 0;

        // Queue for Multi-Source BFS
        queue<pair<int, int>> q;

        // 1. Initial Scan: Find all land cells and initialize border BFS
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (grid[i][j] == 1)
                {
                    // Count all land cells initially
                    ++total;

                    // If the land cell is on the border, it is a source for BFS
                    if (i == 0 || i == m - 1 || j == 0 || j == n - 1)
                    {
                        // Mark as visited/reachable (using '2') and start the flood-fill
                        grid[i][j] = 2;
                        q.push({i, j});
                        // Decrement total count since this land cell is border-reachable
                        --total;
                    }
                }
            }
        }

        // Standard directions for 4-directional movement (up, down, left, right)
        int dirs[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

        // 2. Multi-Source BFS: Flood-fill from the border land cells
        while (!q.empty())
        {
            // Use structured binding for cleaner coordinate access
            auto [x, y] = q.front();
            q.pop();

            // Explore 4 neighbors
            for (auto &d : dirs)
            {
                int nx = x + d[0];
                int ny = y + d[1];

                // Check boundary conditions and if the neighbor is an unvisited land cell ('1')
                if (nx >= 0 && nx < m && ny >= 0 && ny < n &&
                    grid[nx][ny] == 1)
                {

                    // Mark as visited/reachable (using '2')
                    grid[nx][ny] = 2;
                    q.push({nx, ny});

                    // Decrement total count since this land cell is border-reachable
                    --total;
                }
            }
        }

        // The remaining count in 'total' is the number of enclaves (trapped '1's)
        return total;
    }
};

// Main function for testing
int main()
{
    Solution sol;

    // Test Case 1: Example provided in problem statement
    // Input: [[0,1,1,0],[0,0,1,0],[0,0,1,0],[0,0,0,0]]
    // Expected Output: 3 (The three '1's in the middle column are trapped)
    vector<vector<int>> grid1 = {{0, 1, 1, 0}, {0, 0, 1, 0}, {0, 0, 1, 0}, {0, 0, 0, 0}};
    cout << "Test Case 1: Expected 3" << endl;
    cout << "Result: " << sol.numEnclaves(grid1) << endl;

    // Test Case 2: Additional Test Case
    // Input: [[0,0,0,0],[1,0,1,0],[0,1,1,0],[0,0,0,0]]
    // Expected Output: 1 (The single '1' at (1, 2) is trapped)
    vector<vector<int>> grid2 = {{0, 0, 0, 0}, {1, 0, 1, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}};
    cout << "\nTest Case 2: Expected 1" << endl;
    cout << "Result: " << sol.numEnclaves(grid2) << endl;

    return 0;
}
