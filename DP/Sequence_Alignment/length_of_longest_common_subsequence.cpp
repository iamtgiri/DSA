/*
File: longest_common_subsequence.cpp
Date: 2025-09-12 15:27

Problem: Longest Common Subsequence (LCS)
Link: URL

Problem Statement:
------------------
Given two strings X and Y, find the length of their Longest Common Subsequence (LCS).
- A subsequence is a sequence derived by deleting some or no characters,
  without changing the order of the remaining characters.
- The LCS is the longest subsequence present in both strings.

Examples:
---------
Input:
X = "abcdgh"
Y = "abedfhr"
Output: 4
Explanation: LCS = "abdh"

-------------------------------------------------
❌ Brute Force (Recursion)
- Idea: Compare last characters. If equal → 1 + recurse on smaller prefixes.
        Else → max of ignoring one character from either string.
- Time complexity: O(2^(n+m)) [exponential]
- Space complexity: O(n + m) recursion depth
- Limitations: Too slow for larger inputs.

✅ Optimized Approaches
1. Memoization (Top-Down DP)
- Idea: Cache subproblem results to avoid recomputation.
- Time complexity: O(n * m)
- Space complexity: O(n * m) + recursion stack

2. Tabulation (Bottom-Up DP)
- Idea: Iteratively build DP table for all prefixes.
- Time complexity: O(n * m)
- Space complexity: O(n * m)

3. Space Optimized DP
- Idea: Only previous row matters → reduce to O(min(n, m)) space.
- Time complexity: O(n * m)
- Space complexity: O(min(n, m))

💡 Key Pattern:
- Classic DP problem, similar to Edit Distance and String Matching.

Keywords:
- LCS
- Dynamic Programming
- String DP

🗒️ Notes:
- Careful with indexing (length vs. index).
- Useful as a subroutine in many problems (diff utility, DNA alignment).
-------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    // 1. Recursive (Brute Force)
    int LCS(string &X, int n, string &Y, int m)
    {
        if (n == 0 || m == 0)
            return 0;

        if (X[n - 1] == Y[m - 1]) // compare last characters
            return 1 + LCS(X, n - 1, Y, m - 1);
        else
            return max(LCS(X, n - 1, Y, m), LCS(X, n, Y, m - 1));
    }

    // 2. Memoization (Top-Down DP)
    int LCS_memo_helper(string &X, int n, string &Y, int m, vector<vector<int>> &dp)
    {
        if (n == 0 || m == 0)
            return 0;

        if (dp[n][m] != -1)
            return dp[n][m];

        if (X[n - 1] == Y[m - 1])
            return dp[n][m] = 1 + LCS_memo_helper(X, n - 1, Y, m - 1, dp);
        else
            return dp[n][m] = max(LCS_memo_helper(X, n - 1, Y, m, dp),
                                  LCS_memo_helper(X, n, Y, m - 1, dp));
    }

    int LCS_memo(string X, string Y)
    {
        int n = X.size(), m = Y.size();
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, -1));
        return LCS_memo_helper(X, n, Y, m, dp);
    }

    // 3. Tabulation (Bottom-Up DP)
    int LCS_tab(string X, string Y)
    {
        int n = X.size(), m = Y.size();
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

        for (int i = 1; i <= n; ++i)
        {
            for (int j = 1; j <= m; ++j)
            {
                if (X[i - 1] == Y[j - 1])
                    dp[i][j] = 1 + dp[i - 1][j - 1];
                else
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
        return dp[n][m];
    }

    // 4. Space Optimized DP (2-row rolling array)
    int LCS_space_optimized(string X, string Y)
    {
        int n = X.size(), m = Y.size();
        if (m > n) swap(X, Y), swap(n, m); // ensure Y is shorter

        vector<int> prev(m + 1, 0), curr(m + 1, 0);

        for (int i = 1; i <= n; ++i)
        {
            for (int j = 1; j <= m; ++j)
            {
                if (X[i - 1] == Y[j - 1])
                    curr[j] = 1 + prev[j - 1];
                else
                    curr[j] = max(prev[j], curr[j - 1]);
            }
            prev = curr;
        }
        return prev[m];
    }
};

int main()
{
    Solution sol;

    string X = "abcdgh";
    string Y = "abedfhr";

    cout << "Recursive (Brute Force): " << sol.LCS(X, X.size(), Y, Y.size()) << "\n";
    cout << "Memoization: " << sol.LCS_memo(X, Y) << "\n";
    cout << "Tabulation: " << sol.LCS_tab(X, Y) << "\n";
    cout << "Space Optimized: " << sol.LCS_space_optimized(X, Y) << "\n";

    return 0;
}
