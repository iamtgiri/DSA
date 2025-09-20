/*
File: Grid_Unique_Paths.cpp
Date: 2025-09-20 10:12

Problem: Grid Unique Paths  
Link: https://leetcode.com/problems/unique-paths/

Problem Statement:
There is a robot on an m x n grid. The robot is initially located at the top-left corner.
The robot tries to move to the bottom-right corner. It can only move either down or right.
Return the number of unique paths the robot can take.

Example:
Input: m = 3, n = 7
Output: 28

-------------------------------------------------
❌ Brute Force (Recursion / Backtracking)
- Idea: From each cell, explore both moves (down, right) recursively until reaching bottom-right.
- Time complexity: O(2^(m+n)) (exponential)
- Space complexity: O(m+n) recursion depth
- Limitations: TLE for m,n > 15

✅ Optimized Approaches

1. Tabulation (Bottom-Up DP)
- Idea:
  - dp[i][j] = number of ways to reach cell (i,j).
  - Transition: dp[i][j] = dp[i-1][j] + dp[i][j-1].
  - Base: First row/col = 1 (only one straight path).
- Time complexity: O(m*n)
- Space complexity: O(m*n)

2. Space Optimization
- Idea: Only the previous row is needed to compute the current row.
- Use two 1D arrays (or reuse one).
- Time complexity: O(m*n)
- Space complexity: O(n)

3. Best Version (Combinatorics)
- Idea:
  - To reach bottom-right, robot must take (m-1) downs and (n-1) rights.
  - Total moves = (m+n-2). Choose positions for downs (or rights).
  - Formula: C(m+n-2, m-1) = (m+n-2)! / ((m-1)! * (n-1)!).
- Time complexity: O(min(m,n)) (using iterative formula for binomial coefficient)
- Space complexity: O(1)

💡 Key Pattern:
- Grid DP with restricted moves
- Relation to binomial coefficients

Keywords:
- DP on Grid
- Combinatorics
- Paths in Matrix

🗒️ Notes
- Learned multiple ways to solve same problem: recursion → DP → math.
- Common mistake: mixing up m (rows) and n (columns).
-------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // 1. Tabulation (DP)
    int uniquePathsTab(int m, int n) {
        vector<vector<int>> dp(m, vector<int>(n, 1));
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
            }
        }
        return dp[m - 1][n - 1];
    }

    // 2. Space Optimization
    int uniquePathsSpaceOpt(int m, int n) {
        vector<int> prev(n, 1), cur(n, 1);
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                cur[j] = prev[j] + cur[j - 1];
            }
            prev = cur;
        }
        return prev[n - 1];
    }

    // 3. Best Version (Combinatorics)
    int uniquePathsComb(int m, int n) {
        long long res = 1;
        int N = m + n - 2;
        int r = min(m - 1, n - 1);
        for (int i = 1; i <= r; i++) {
            res = res * (N - r + i) / i;
        }
        return (int)res;
    }
};

int main() {
    Solution sol;
    cout << "Tabulation: " << sol.uniquePathsTab(3, 7) << endl;      // 28
    cout << "Space Opt: " << sol.uniquePathsSpaceOpt(3, 7) << endl;  // 28
    cout << "Combinatorics: " << sol.uniquePathsComb(3, 7) << endl;  // 28
    return 0;
}
