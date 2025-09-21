/*
File: Wildcard_Matching.cpp
Date: 2025-09-21 10:23

Problem: Wildcard Matching
Link: https://leetcode.com/problems/wildcard-matching/

Problem Statement:
Given an input string s and a pattern p, implement wildcard pattern matching 
with support for '?' and '*' where:
- '?' Matches any single character.
- '*' Matches any sequence of characters (including the empty sequence).
The matching should cover the entire input string (not partial).

-------------------------------------------------
❌ Brute Force
- Idea: Try all possible expansions of '*' (empty, one char, multiple chars)
  recursively and check if pattern == string.
- Time complexity: O(2^(n+m)) in worst case (because '*' introduces branching).
- Space complexity: O(n+m) recursion depth.
- Limitations: Explodes for input length > 20–30.

✅ Optimized Approach
- Idea: Use Dynamic Programming (DP).
  Define dp[i][j] = true if s[0..i-1] matches p[0..j-1].
  - If p[j-1] == s[i-1] or '?': dp[i][j] = dp[i-1][j-1]
  - If p[j-1] == '*': dp[i][j] = dp[i][j-1] (empty) OR dp[i-1][j] (match one/more)
  - Else: dp[i][j] = false
- Time complexity: O(n × m)
- Space complexity: O(n × m), can be optimized to O(m)

💡 Key Pattern:
- This problem is part of the "sequence alignment" family (like LCS, Edit Distance).
- '?' → strict one-to-one alignment.
- '*' → flexible alignment (zero or more characters).
- DP ensures subproblems are reused, avoiding exponential blow-up.

Keywords: Wildcard Matching, DP on Strings, Sequence Alignment

🗒️ Notes
- Learned how '*' creates two recursive choices.
- Similar problems: Regex Matching, Edit Distance, Distinct Subsequences.
- Mistake to avoid: Don’t forget base case where string is empty but pattern 
  has only '*'.
-------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    //------------------------------------
    // 1. Pure Recursion (Exponential)
    //------------------------------------
    bool isMatchRecursive(string &s, string &p, int i, int j) {
        if (i < 0 && j < 0) return true;   // both exhausted
        if (j < 0 && i >= 0) return false; // pattern empty, string not
        if (i < 0 && j >= 0) {
            // string empty, pattern must be all '*'
            for (int k = 0; k <= j; k++) if (p[k] != '*') return false;
            return true;
        }

        if (p[j] == s[i] || p[j] == '?')
            return isMatchRecursive(s, p, i - 1, j - 1);

        if (p[j] == '*')
            return isMatchRecursive(s, p, i, j - 1) ||   // '*' = empty
                   isMatchRecursive(s, p, i - 1, j);     // '*' = consume one char

        return false;
    }

    //------------------------------------
    // 2. Top-Down with Memoization
    //------------------------------------
    bool isMatchTopDown(string &s, string &p, int i, int j, vector<vector<int>> &dp) {
        if (i < 0 && j < 0) return true;
        if (j < 0 && i >= 0) return false;
        if (i < 0 && j >= 0) {
            for (int k = 0; k <= j; k++) if (p[k] != '*') return false;
            return true;
        }

        if (dp[i][j] != -1) return dp[i][j];

        if (p[j] == s[i] || p[j] == '?')
            return dp[i][j] = isMatchTopDown(s, p, i - 1, j - 1, dp);

        if (p[j] == '*') {
            bool emptyMatch = isMatchTopDown(s, p, i, j - 1, dp);
            bool charMatch  = isMatchTopDown(s, p, i - 1, j, dp);
            return dp[i][j] = (emptyMatch || charMatch);
        }

        return dp[i][j] = false;
    }

    //------------------------------------
    // 3. Bottom-Up DP
    //------------------------------------
    bool isMatchBottomUp(string s, string p) {
        int n = s.size(), m = p.size();
        vector<vector<bool>> dp(n + 1, vector<bool>(m + 1, false));

        dp[0][0] = true; // empty string, empty pattern

        // If string empty, pattern must be all '*'
        for (int j = 1; j <= m; j++) {
            if (p[j - 1] == '*') dp[0][j] = dp[0][j - 1];
        }

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (p[j - 1] == s[i - 1] || p[j - 1] == '?') {
                    dp[i][j] = dp[i - 1][j - 1];
                } else if (p[j - 1] == '*') {
                    dp[i][j] = dp[i][j - 1] || dp[i - 1][j];
                } else {
                    dp[i][j] = false;
                }
            }
        }

        return dp[n][m];
    }
};

int main() {
    Solution sol;
    string s1 = "aa", p1 = "a";   // false
    string s2 = "aa", p2 = "*";   // true
    string s3 = "cb", p3 = "?a";  // false
    string s4 = "adceb", p4 = "*a*b"; // true

    cout << boolalpha;
    cout << "Recursive:   " << sol.isMatchRecursive(s1, p1, s1.size()-1, p1.size()-1) << "\n";
    vector<vector<int>> dp(s2.size(), vector<int>(p2.size(), -1));
    cout << "Top Down:    " << sol.isMatchTopDown(s2, p2, s2.size()-1, p2.size()-1, dp) << "\n";
    cout << "Bottom Up:   " << sol.isMatchBottomUp(s4, p4) << "\n";

    return 0;
}
