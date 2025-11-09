/*
File: Minimum_Falling_Path_Sum.cpp
Date: 2025-09-20 14:28

Problem: Minimum Falling Path Sum
Link: https://leetcode.com/problems/minimum-falling-path-sum/

Problem Statement:
Given an n x n integer matrix, return the minimum sum of any falling path through the matrix.
A falling path starts at any element in the first row and moves to the next row, either directly below or diagonally left/right.

Example:
    Input: matrix = [[2,1,3],
                    [6,5,4],
                    [7,8,9]]
    Output: 13
-------------------------------------------------
❌ Brute Force
- Idea: Try all paths recursively starting from the first row.
- Time complexity: O(3^n)
- Space complexity: O(n) recursion stack
- Limitation: Exponential, not feasible for n=100

✅ Optimized Approaches

1. Tabulation (Bottom-Up DP)
- Idea:
  - dp[i][j] = minimum falling path sum starting from cell (i,j) to bottom.
  - Transition: dp[i][j] = matrix[i][j] + min(dp[i+1][j], dp[i+1][j-1], dp[i+1][j+1])
  - Compute from bottom row upwards.
- Time complexity: O(n^2)
- Space complexity: O(n^2)

2. Space Optimization
- Idea:
  - Only need the previous row to compute the current row.
  - Use a single 1D array to store previous row sums.
- Time complexity: O(n^2)
- Space complexity: O(n)

💡 Key Pattern:
- DP on grids with restricted moves (down-left, down, down-right)
- Bottom-up DP

Keywords:
- Grid DP
- Falling Path
-------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // 1. Tabulation (Bottom-Up DP)
    int minFallingPathSum(vector<vector<int>>& matrix) {
        int n = matrix.size();
        vector<vector<int>> dp(n, vector<int>(n));

        // Initialize bottom row
        for (int j = 0; j < n; ++j)
            dp[n-1][j] = matrix[n-1][j];

        // Fill DP from bottom up
        for (int i = n-2; i >= 0; --i) {
            for (int j = 0; j < n; ++j) {
                int best = dp[i+1][j]; // down
                if (j-1 >= 0) best = min(best, dp[i+1][j-1]); // down-left
                if (j+1 < n) best = min(best, dp[i+1][j+1]);  // down-right
                dp[i][j] = matrix[i][j] + best;
            }
        }

        return *min_element(dp[0].begin(), dp[0].end());
    }

    // 2. Space Optimization
    int minFallingPathSumSpaceOpt(vector<vector<int>>& matrix) {
        int n = matrix.size();
        vector<int> prev(n);

        // Initialize bottom row
        for (int j = 0; j < n; ++j)
            prev[j] = matrix[n-1][j];

        // Compute from bottom up
        for (int i = n-2; i >= 0; --i) {
            vector<int> curr(n);
            for (int j = 0; j < n; ++j) {
                int best = prev[j]; // down
                if (j-1 >= 0) best = min(best, prev[j-1]); // down-left
                if (j+1 < n) best = min(best, prev[j+1]);  // down-right
                curr[j] = matrix[i][j] + best;
            }
            prev = curr;
        }

        return *min_element(prev.begin(), prev.end());
    }
};

int main() {
    Solution sol;

    vector<vector<int>> matrix1 = {{2,1,3},{6,5,4},{7,8,9}};
    vector<vector<int>> matrix2 = {{-19,57},{-40,-5}};

    cout << "Tabulation: " << sol.minFallingPathSum(matrix1) << endl;      // 13
    cout << "Space Opt: " << sol.minFallingPathSumSpaceOpt(matrix1) << endl; // 13

    cout << "Tabulation: " << sol.minFallingPathSum(matrix2) << endl;      // -59
    cout << "Space Opt: " << sol.minFallingPathSumSpaceOpt(matrix2) << endl; // -59

    return 0;
}
