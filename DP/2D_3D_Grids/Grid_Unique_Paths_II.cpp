/*
File: Grid_Unique_Paths_II.cpp
Date: 2025-09-20 10:40

Problem: Grid Unique Paths II
Link: https://leetcode.com/problems/unique-paths-ii/

Problem Statement:
You are given an m x n integer array grid. The robot starts at the top-left corner (grid[0][0])
and tries to reach the bottom-right corner (grid[m-1][n-1]). The robot can only move either down
or right at any point in time. A path cannot pass through any cell that has an obstacle (marked as 1).
Return the number of unique paths the robot can take.

Example 1:
Input: obstacleGrid = [[0,0,0],[0,1,0],[0,0,0]]
Output: 2
Explanation: Two possible ways:
1. Right -> Right -> Down -> Down
2. Down -> Down -> Right -> Right

Example 2:
Input: obstacleGrid = [[0,1],[0,0]]
Output: 1

-------------------------------------------------
❌ Brute Force (Recursion / Backtracking)
- Idea: Try all possible paths (down/right) recursively, skipping cells with obstacles.
- Time complexity: O(2^(m+n)) (exponential)
- Space complexity: O(m+n) recursion depth
- Limitations: Will TLE for large grids.

✅ Optimized Approaches

1. Tabulation (Bottom-Up DP)
- Idea:
  - dp[i][j] = number of ways to reach cell (i,j).
  - Transition: if obstacleGrid[i][j] == 0, then
    dp[i][j] = dp[i-1][j] + dp[i][j-1].
  - Initialize first row and first column carefully (blocked cells => 0).
- Time complexity: O(m*n)
- Space complexity: O(m*n)

2. Space Optimization
- Idea:
  - Only current row and previous row are needed at any time.
  - We can compress into a single 1D array (size n).
- Time complexity: O(m*n)
- Space complexity: O(n)

💡 Key Pattern:
- Grid DP with restricted moves (down/right).
- Obstacle handling by zeroing out paths at blocked cells.

Keywords:
- DP on Grid
- Obstacles
- Paths in Matrix

🗒️ Notes
- Once an obstacle is encountered in a row/column, all further cells in that line have 0 paths.
- Be careful with start cell initialization: if blocked, answer is 0.
-------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // 1. Tabulation (Bottom-Up DP)
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int m = obstacleGrid.size(), n = obstacleGrid[0].size();
        vector<vector<int>> dp(m, vector<int>(n, 0));

        // Start cell
        if (obstacleGrid[0][0] == 1) return 0;
        dp[0][0] = 1;

        // First column
        for (int i = 1; i < m; ++i) {
            if (obstacleGrid[i][0] == 0 && dp[i - 1][0] == 1)
                dp[i][0] = 1;
        }

        // First row
        for (int j = 1; j < n; ++j) {
            if (obstacleGrid[0][j] == 0 && dp[0][j - 1] == 1)
                dp[0][j] = 1;
        }

        // Fill rest of dp
        for (int i = 1; i < m; ++i) {
            for (int j = 1; j < n; ++j) {
                if (obstacleGrid[i][j] == 0) {
                    dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
                }
            }
        }

        return dp[m - 1][n - 1];
    }

    // 2. Space Optimization (1D DP)
    int uniquePathsWithObstaclesSpaceOpt(vector<vector<int>>& obstacleGrid) {
        int m = obstacleGrid.size(), n = obstacleGrid[0].size();
        vector<int> dp(n, 0);

        if (obstacleGrid[0][0] == 1) return 0;
        dp[0] = 1;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (obstacleGrid[i][j] == 1) {
                    dp[j] = 0; // obstacle blocks path
                } else if (j > 0) {
                    dp[j] += dp[j - 1];
                }
            }
        }

        return dp[n - 1];
    }
};

int main() {
    Solution sol;
    vector<vector<int>> grid1 = {{0,0,0},{0,1,0},{0,0,0}};
    vector<vector<int>> grid2 = {{0,1},{0,0}};

    cout << "Tabulation: " << sol.uniquePathsWithObstacles(grid1) << endl;         // 2
    cout << "Space Opt: " << sol.uniquePathsWithObstaclesSpaceOpt(grid1) << endl;  // 2
    cout << "Tabulation: " << sol.uniquePathsWithObstacles(grid2) << endl;         // 1
    cout << "Space Opt: " << sol.uniquePathsWithObstaclesSpaceOpt(grid2) << endl;  // 1
    return 0;
}
