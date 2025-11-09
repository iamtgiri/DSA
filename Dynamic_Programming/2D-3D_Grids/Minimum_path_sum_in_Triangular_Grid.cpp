/*
File: Minimum_path_sum_in_Triangular_Grid.cpp
Date: 2025-09-20 01:25

Problem: Minimum path sum in Triangular Grid
Link: https://leetcode.com/problems/triangle/
Problem Statement:
Given a triangle array, return the minimum path sum from top to bottom.

For each step, you may move to an adjacent number of the row below.
More formally, if you are on index i on the current row, you may move to either
index i or index i + 1 on the next row.

Example 1:
Input: triangle = [[2],[3,4],[6,5,7],[4,1,8,3]]
Output: 11
Explanation: The minimum path sum from top to bottom is 2 + 3 + 5 + 1 = 11.

-------------------------------------------------
❌ Brute Force (Recursion)
- Idea: From each cell, try moving down and diagonal down-right recursively.
- Time complexity: O(2^n) (exponential)
- Space complexity: O(n) recursion depth
- Limitations: Huge recomputation → TLE for larger inputs.

✅ Optimized Approaches
1. Recursion + Memoization
- Idea: Cache results of subproblems (i, j).
- Time complexity: O(n^2)
- Space complexity: O(n^2 + n)

2. Tabulation (Bottom-Up DP)
- Idea: Start from bottom row and propagate upwards.
- Time complexity: O(n^2)
- Space complexity: O(n^2)

3. Space Optimized DP
- Idea: Only keep one row (or modify triangle in-place).
- Time complexity: O(n^2)
- Space complexity: O(n) or O(1) (in-place)

💡 Key Pattern:
- Classic "triangle path sum" → same structure as Minimum Falling Path Sum.
- Overlapping subproblems + adjacency constraint.

Keywords:
- Recursion
- DP on Grid
- Triangle DP
- Path Sum

🗒️ Notes
- Learned how bottom-up naturally eliminates recursion.
- Common mistake: forgetting to handle boundaries at last row.
-------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    // ----------------- 1. Pure Recursion -----------------
    int solveRec(int i, int j, vector<vector<int>> &triangle, int n)
    {
        if (i == n - 1)
            return triangle[i][j]; // base case: bottom row

        int down = triangle[i][j] + solveRec(i + 1, j, triangle, n);
        int diag = triangle[i][j] + solveRec(i + 1, j + 1, triangle, n);
        return min(down, diag);
    }

    // ----------------- 2. Recursion + Memoization -----------------
    int solveMemo(int i, int j, vector<vector<int>> &triangle, int n, vector<vector<int>> &dp)
    {
        if (i == n - 1)
            return triangle[i][j];
        if (dp[i][j] != -1)
            return dp[i][j];
            
        int down = triangle[i][j] + solveMemo(i + 1, j, triangle, n, dp);
        int diag = triangle[i][j] + solveMemo(i + 1, j + 1, triangle, n, dp);
        return dp[i][j] = min(down, diag);
    }

    // ----------------- 3. Tabulation (Bottom-Up DP) -----------------
    int solveTab(vector<vector<int>> &triangle)
    {
        int n = triangle.size();
        vector<vector<int>> dp(n, vector<int>(n, 0));
        // Base: last row = triangle's last row
        for (int j = 0; j < n; j++)
            dp[n - 1][j] = triangle[n - 1][j];

        // Build bottom-up
        for (int i = n - 2; i >= 0; i--)
        {
            for (int j = 0; j <= i; j++)
            {
                dp[i][j] = triangle[i][j] + min(dp[i + 1][j], dp[i + 1][j + 1]);
            }
        }
        return dp[0][0];
    }

    // ----------------- 4. Space Optimized -----------------
    int solveSpaceOpt(vector<vector<int>> &triangle)
    {
        int n = triangle.size();
        vector<int> front(n, 0), cur(n, 0);

        // Base: last row
        for (int j = 0; j < n; j++)
            front[j] = triangle[n - 1][j];

        for (int i = n - 2; i >= 0; i--)
        {
            for (int j = 0; j <= i; j++)
            {
                cur[j] = triangle[i][j] + min(front[j], front[j + 1]);
            }
            front = cur;
        }
        return front[0];
    }

    // ----------------- API Function -----------------
    int minimumTotal(vector<vector<int>> &triangle)
    {
        int n = triangle.size();

        // 1. Pure recursion (not efficient for large n)
        // return solveRec(0, 0, triangle, n);

        // 2. Recursion + Memoization
        // vector<vector<int>> dp(n, vector<int>(n, -1));
        // return solveMemo(0, 0, triangle, n, dp);

        // 3. Tabulation
        // return solveTab(triangle);

        // 4. Space Optimized
        return solveSpaceOpt(triangle);
    }
};

int main()
{
    Solution sol;
    vector<vector<int>> triangle = {{2}, {3, 4}, {6, 5, 7}, {4, 1, 8, 3}};
    cout << sol.minimumTotal(triangle) << endl; // Output: 11
    return 0;
}
