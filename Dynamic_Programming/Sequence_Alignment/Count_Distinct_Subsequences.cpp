/*
File: Count_Distinct_Subsequences.cpp
Date: 2025-09-20 14:44

Problem: Distinct Subsequences
Link: https://leetcode.com/problems/distinct-subsequences/
Problem Statement:
Given two strings s and t, return the number of distinct subsequences of s which equals t.

Example:
    Input: s = "rabbbit", t = "rabbit"
    Output: 3
-------------------------------------------------
❌ Brute Force
- Idea: Try all subsequences of s and count matches with t.
- Time complexity: O(2^n) (n = length of s)
- Space complexity: O(n) recursion stack
- Limitations: Exponential, infeasible for n > 20

✅ Optimized Approaches
- Recursion + Memoization (Top-down)
- Bottom-up DP (Tabulation)
- Space-optimized DP

💡 Key Pattern:
- Sequence DP / 2D DP
- LCS-style transitions
- Transition depends on matching last characters

Keywords:
- DP on strings
- Subsequences
- LCS variant
-------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    // -------------------- Recursion --------------------
    int countRec(string &s, string &t, int i, int j)
    {
        // Base cases:
        if (j < 0)
            return 1; // all chars in t matched → valid subsequence
        if (i < 0)
            return 0; // s exhausted but t not matched → invalid

        // Transition:
        if (s[i] == t[j])
        {
            // Option 1: use s[i] to match t[j] → countRec(i-1, j-1)
            // Option 2: skip s[i] → countRec(i-1, j)
            return countRec(s, t, i - 1, j - 1) + countRec(s, t, i - 1, j);
        }
        else
        {
            // Characters do not match → skip s[i]
            return countRec(s, t, i - 1, j);
        }
    }

    // -------------------- Memoization (Top-down) --------------------
    int countMemoHelper(string &s, string &t, int i, int j, vector<vector<int>> &dp)
    {
        if (j < 0)
            return 1;
        if (i < 0)
            return 0;
        if (dp[i][j] != -1)
            return dp[i][j]; // reuse computed result

        if (s[i] == t[j])
            dp[i][j] = countMemoHelper(s, t, i - 1, j - 1, dp) +
                       countMemoHelper(s, t, i - 1, j, dp);
        else
            dp[i][j] = countMemoHelper(s, t, i - 1, j, dp);

        return dp[i][j];
    }

    int numDistinctMemo(string s, string t)
    {
        int n = s.size(), m = t.size();
        vector<vector<int>> dp(n, vector<int>(m, -1));
        return countMemoHelper(s, t, n - 1, m - 1, dp);
    }

    // -------------------- Bottom-up Tabulation --------------------
    int numDistinctTab(string s, string t)
    {
        int n = s.size(), m = t.size();
        vector<vector<unsigned long long>> dp(n + 1, vector<unsigned long long>(m + 1, 0));

        // Base case: empty t can be formed from any prefix of s in 1 way
        for (int i = 0; i <= n; ++i)
            dp[i][0] = 1;

        // Fill DP table
        for (int i = 1; i <= n; ++i)
        {
            for (int j = 1; j <= m; ++j)
            {
                if (s[i - 1] == t[j - 1])
                {
                    // If chars match → include or exclude
                    dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j];
                }
                else
                {
                    // If chars do not match → exclude s[i]
                    dp[i][j] = dp[i - 1][j];
                }
            }
        }
        return dp[n][m];
    }

    // -------------------- Space-optimized DP --------------------
    int numDistinctOptimized(string s, string t)
    {
        int n = s.size(), m = t.size();
        vector<unsigned long long> prev(m + 1, 0), curr(m + 1, 0);

        // Base case: empty t can be formed 1 way
        prev[0] = 1;

        for (int i = 1; i <= n; ++i)
        {
            curr[0] = 1; // empty t for current row
            for (int j = 1; j <= m; ++j)
            {
                if (s[i - 1] == t[j - 1])
                    curr[j] = prev[j - 1] + prev[j]; // include or exclude
                else
                    curr[j] = prev[j]; // exclude
            }
            prev = curr; // move to next row
        }
        return prev[m];
    }
};

int main()
{
    Solution sol;
    string s = "rabbbit", t = "rabbit";

    cout << "Recursion: " << sol.countRec(s, t, s.size() - 1, t.size() - 1) << "\n";
    cout << "Memoization: " << sol.numDistinctMemo(s, t) << "\n";
    cout << "Tabulation: " << sol.numDistinctTab(s, t) << "\n";
    cout << "Space Optimized: " << sol.numDistinctOptimized(s, t) << "\n";

    return 0;
}
