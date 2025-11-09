/*
File: Matrix_Chain_Multiplication.cpp
Date: 2025-09-15 13:51

Problem: Matrix Chain Multiplication
Link: URL

Problem Statement:
------------------
Given dimensions of matrices in an array arr[] of size n,
where the i-th matrix has dimension arr[i-1] x arr[i],
find the minimum number of scalar multiplications needed
to multiply the chain of matrices.

Example:
--------
Input: arr = {40, 20, 30, 10, 30}
Output: 26000
Explanation:
  (A1 x (A2 x A3)) x A4 = 26000 multiplications.

-------------------------------------------------
❌ Brute Force
- Idea: Try all possible ways of parenthesizing (divide at each k).
- Time complexity: Exponential.
- Space complexity: O(1).
- Limitations: Very slow for n > 15.

✅ Optimized Approach
- Memoization (Top-Down DP)
- Tabulation (Bottom-Up DP)
- Time complexity: O(n^3).
- Space complexity: O(n^2).

💡 Key Pattern:
- Interval DP
- Optimal Substructure

Keywords:
- Matrix Chain Multiplication
- DP on intervals
- Parenthesization

🗒️ Notes
- Careful with index ranges (arr[i-1]*arr[k]*arr[j]).
- Memoization vs Tabulation only differ in traversal order.
-------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // --- Pure Recursion ---
    int MCM_Recursion(vector<int>& arr, int i, int j) {
        if (i >= j) return 0;

        int mn = INT_MAX;
        for (int k = i; k < j; ++k) {
            int temp = MCM_Recursion(arr, i, k) +
                       MCM_Recursion(arr, k + 1, j) +
                       arr[i - 1] * arr[k] * arr[j];
            mn = min(mn, temp);
        }
        return mn;
    }

    // --- Memoization (Top-Down) ---
    int MCM_Memo_Helper(vector<int>& arr, int i, int j, vector<vector<int>>& dp) {
        if (i >= j) return 0;
        if (dp[i][j] != -1) return dp[i][j];

        int mn = INT_MAX;
        for (int k = i; k < j; ++k) {
            int temp = MCM_Memo_Helper(arr, i, k, dp) +
                       MCM_Memo_Helper(arr, k + 1, j, dp) +
                       arr[i - 1] * arr[k] * arr[j];
            mn = min(mn, temp);
        }
        return dp[i][j] = mn;
    }

    int MCM_Memo(vector<int>& arr) {
        int n = arr.size();
        vector<vector<int>> dp(n, vector<int>(n, -1));
        return MCM_Memo_Helper(arr, 1, n - 1, dp);
    }

    // --- Tabulation (Bottom-Up DP) ---
    int MCM_Tabulation(vector<int>& arr) {
        int n = arr.size();
        vector<vector<int>> dp(n, vector<int>(n, 0));

        // len = chain length
        for (int len = 2; len < n; ++len) {
            for (int i = 1; i < n - len + 1; ++i) {
                int j = i + len - 1;
                dp[i][j] = INT_MAX;

                for (int k = i; k < j; ++k) {
                    int cost = dp[i][k] + dp[k + 1][j] +
                               arr[i - 1] * arr[k] * arr[j];
                    dp[i][j] = min(dp[i][j], cost);
                }
            }
        }
        return dp[1][n - 1];
    }
};

// --- Main Function ---
int main() {
    Solution sol;
    vector<int> arr = {40, 20, 30, 10, 30};
    int n = arr.size();

    cout << "Recursion: " << sol.MCM_Recursion(arr, 1, n - 1) << "\n";
    cout << "Memoization: " << sol.MCM_Memo(arr) << "\n";
    cout << "Tabulation: " << sol.MCM_Tabulation(arr) << "\n";

    return 0;
}
