/*
File: Edit_Distance.cpp
Date: 2025-09-20 15:07

Problem: Edit Distance
Link: https://leetcode.com/problems/edit-distance/

Problem Statement:
Given two strings word1 and word2, return the minimum number of operations
required to convert word1 to word2 using insert, delete, or replace operations.

Example 1:
    Input: word1 = "horse", word2 = "ros"
    Output: 3
    Explanation: 
        horse -> rorse (replace 'h' with 'r')
        rorse -> rose (remove 'r')
        rose -> ros (remove 'e')

Example 2:
    Input: word1 = "intention", word2 = "execution"
    Output: 5
    Explanation: 
        intention -> inention (remove 't')
        inention -> enention (replace 'i' with 'e')
        enention -> exention (replace 'n' with 'x')
        exention -> exection (replace 'n' with 'c')
        exection -> execution (insert 'u')
-------------------------------------------------
❌ Brute Force
- Idea: Try all possible operations at each step recursively.
- Time complexity: Exponential
- Space complexity: O(max(n,m)) recursion stack
- Limitations: Too slow for large strings

✅ Optimized Approach (DP)
- Idea: Use a 2D DP table where dp[i][j] stores the minimum number of operations
  required to convert word1[0..i-1] to word2[0..j-1].
  Fill the table iteratively using previously computed subproblems.
- Time complexity: O(n * m)
- Space complexity: O(n * m)

💡 Connection to LCS:
- LCS represents the part of the strings that do NOT need any change.
- Characters NOT in LCS are candidates for insert, delete or replace.
- DP builds on this idea to efficiently compute the minimum edits.

💡 Key Pattern:
- 2D DP on sequences with character comparisons and allowed operations.
*/

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int minDistance(string word1, string word2)
    {
        int n = word1.size();
        int m = word2.size();

        // dp[i][j] = min operations to convert word1[0..i-1] -> word2[0..j-1]
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

        // Base cases: converting empty string
        for (int i = 0; i <= n; ++i)
            dp[i][0] = i; // delete all characters
        for (int j = 0; j <= m; ++j)
            dp[0][j] = j; // insert all characters

        // Fill DP table
        for (int i = 1; i <= n; ++i)
        {
            for (int j = 1; j <= m; ++j)
            {
                if (word1[i - 1] == word2[j - 1])
                {
                    // Characters match → no operation needed (like LCS match)
                    dp[i][j] = dp[i - 1][j - 1];
                }
                else
                {
                    // Characters differ → consider all 3 operations
                    int insertOp = dp[i][j - 1] + 1;      // insert word2[j-1] into word1
                    int deleteOp = dp[i - 1][j] + 1;      // delete word1[i-1]
                    int replaceOp = dp[i - 1][j - 1] + 1; // replace word1[i-1] with word2[j-1]

                    dp[i][j] = min({insertOp, deleteOp, replaceOp});
                }
            }
        }

        return dp[n][m]; // min operations to convert full strings
    }
};

int main()
{
    Solution sol;
    string word1 = "horse";
    string word2 = "ros";
    cout << sol.minDistance(word1, word2) << "\n"; // Output: 3

    return 0;
}
