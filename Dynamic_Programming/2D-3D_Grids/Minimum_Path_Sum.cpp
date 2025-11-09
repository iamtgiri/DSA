/* 
File: Minimum_Path_Sum.cpp
Date: 2025-09-20 11:27

Problem: Minimum Path Sum
Link: https://leetcode.com/problems/minimum-path-sum/

Problem Statement:
Given a m x n grid filled with non-negative numbers, find a path from top-left to bottom-right 
which minimizes the sum of all numbers along its path.
You can only move either down or right at any point in time.

-------------------------------------------------
❌ Brute Force (Recursion / Backtracking)
- Idea: Try all possible paths recursively (down/right), keep track of minimum sum.
- Time complexity: O(2^(m+n)) (exponential).
- Space complexity: O(m+n) recursion stack.
- Limitations: Will TLE for larger inputs.

✅ Optimized Approaches

1. Tabulation (Bottom-Up DP)
- Idea:
  - dp[i][j] = minimum sum to reach cell (i,j).
  - Transition: dp[i][j] = min(dp[i-1][j], dp[i][j-1]) + grid[i][j].
  - Initialize first row and first column separately.
- Time complexity: O(m*n)
- Space complexity: O(m*n)

2. Space Optimization
- Idea:
  - Each state depends only on top (previous row) and left (same row).
  - Use a 1D array of size n.
- Time complexity: O(m*n)
- Space complexity: O(n)

💡 Key Pattern:
- Grid DP with restricted moves (down/right).
- Similar to "Unique Paths" but minimizing sum instead of counting paths.

Keywords:
- Dynamic Programming
- Grid
- Path Sum
-------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // 1. Tabulation (2D DP)
    int minPathSumTab(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        vector<vector<int>> dp(m, vector<int>(n, 0));

        dp[0][0] = grid[0][0];

        // Initialize top row
        for (int j = 1; j < n; ++j) {
            dp[0][j] = dp[0][j - 1] + grid[0][j];
        }

        // Initialize first column
        for (int i = 1; i < m; ++i) {
            dp[i][0] = dp[i - 1][0] + grid[i][0];
        }

        // Fill remaining cells
        for (int i = 1; i < m; ++i) {
            for (int j = 1; j < n; ++j) {
                dp[i][j] = min(dp[i - 1][j], dp[i][j - 1]) + grid[i][j];
            }
        }

        return dp[m - 1][n - 1];
    }

    // 2. Space Optimization (1D DP)
    int minPathSumSpaceOpt(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        vector<int> dp(n, 0);

        dp[0] = grid[0][0];

        // Initialize first row
        for (int j = 1; j < n; ++j) {
            dp[j] = dp[j - 1] + grid[0][j];
        }

        // Process each row
        for (int i = 1; i < m; ++i) {
            dp[0] += grid[i][0]; // first column
            for (int j = 1; j < n; ++j) {
                dp[j] = min(dp[j], dp[j - 1]) + grid[i][j];
            }
        }

        return dp[n - 1];
    }
};

int main() {
    Solution sol;

    vector<vector<int>> grid1 = {{1,3,1},{1,5,1},{4,2,1}};
    vector<vector<int>> grid2 = {{1,2,3},{4,5,6}};

    cout << "Tabulation: " << sol.minPathSumTab(grid1) << endl;      // 7
    cout << "Space Opt: " << sol.minPathSumSpaceOpt(grid1) << endl;  // 7

    cout << "Tabulation: " << sol.minPathSumTab(grid2) << endl;      // 12
    cout << "Space Opt: " << sol.minPathSumSpaceOpt(grid2) << endl;  // 12

    return 0;
}
