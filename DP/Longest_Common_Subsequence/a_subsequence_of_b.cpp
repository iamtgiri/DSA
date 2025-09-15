/*
File: subsequence_pattern_matching.cpp
Date: 2025-09-14 22:07

Problem: Check if one string is a subsequence of another
Link: URL

Problem Statement:
------------------
Given two strings X and Y, check if X is a subsequence of Y.
- A subsequence of a string is obtained by deleting zero or more characters 
  without changing the order of the remaining characters.

Examples:
---------
Input: X = "abc", Y = "axbycz"
Output: true

Input: X = "abc", Y = "acb"
Output: false

-------------------------------------------------
❌ Brute Force
- Idea: Generate all subsequences of Y and check if X appears.
- Time complexity: O(2^m).
- Space complexity: O(m).
- Limitations: Exponential, not feasible.

✅ Optimized Approach 1 (Two Pointers)
- Idea:
  - Traverse both strings.
  - Increment pointer in X only when characters match.
  - If we reach end of X, it is a subsequence.
- Time complexity: O(m).
- Space complexity: O(1).

✅ Optimized Approach 2 (LCS-based, for learning)
- Idea:
  - Compute LCS(X, Y).
  - If LCS length == |X|, then X is a subsequence of Y.
- Time complexity: O(n * m).
- Space complexity: O(n * m).
-------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    // ✅ Approach 1: Two pointers
    bool isSubsequenceTwoPointer(const string &X, const string &Y)
    {
        int i = 0, j = 0;
        while (i < X.size() && j < Y.size())
        {
            if (X[i] == Y[j])
                ++i;
            ++j;
        }
        return i == X.size();
    }

    // ✅ Approach 2: Using LCS (slower, but good for DP pattern practice)
    bool isSubsequenceLCS(const string &X, const string &Y)
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
        return dp[n][m] == n;
    }
};

int main()
{
    Solution sol;

    string X = "abc", Y = "axbycz";
    cout << "Is \"" << X << "\" subsequence of \"" << Y << "\"? "
         << (sol.isSubsequenceTwoPointer(X, Y) ? "Yes" : "No") << "\n";

    string X2 = "abc", Y2 = "acb";
    cout << "Is \"" << X2 << "\" subsequence of \"" << Y2 << "\"? "
         << (sol.isSubsequenceTwoPointer(X2, Y2) ? "Yes" : "No") << "\n";

    return 0;
}
