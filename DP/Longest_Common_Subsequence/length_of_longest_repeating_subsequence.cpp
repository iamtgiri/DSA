/*
File: length_of_longest_repeating_subsequence.cpp
Date: 2025-09-14 21:50

Problem: Length of Longest Repeating Subsequence
Link: URL

Problem Statement:
------------------
Given a string X, find the length of the longest subsequence which occurs 
at least twice in the string. The two subsequences should not have the same 
character at the same index (i != j).

Examples:
---------
Input: "aab"
Output: 1
Explanation:
The longest repeating subsequence is "a" (appears twice).

Input: "axxxy"
Output: 2
Explanation:
The longest repeating subsequence is "xx".

-------------------------------------------------
❌ Brute Force
- Idea: Generate all subsequences and check which ones repeat.
- Time complexity: O(2^n).
- Space complexity: O(n).
- Limitations: Not feasible for n > 20.

✅ Optimized Approach (DP)
- Idea:
  - LRS is just LCS(X, X) with the condition i != j.
- Time complexity: O(n^2).
- Space complexity: O(n^2).

💡 Key Pattern:
- LRS is a variant of LCS with an index restriction.

Keywords:
- LCS
- Dynamic Programming
- Subsequence
- String

🗒️ Notes:
- This pattern is useful in detecting repeated subsequences.
- Be careful to enforce the "i != j" condition.
-------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int longest_repeating_subsequence(const string &X)
    {
        int n = X.size();
        vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));

        for (int i = 1; i <= n; ++i)
        {
            for (int j = 1; j <= n; ++j)
            {
                if (X[i - 1] == X[j - 1] && i != j)
                    dp[i][j] = 1 + dp[i - 1][j - 1];
                else
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }

        return dp[n][n];
    }
};

int main()
{
    Solution sol;

    string X1 = "aab";
    cout << "Input: " << X1
         << " → LRS length = " << sol.longest_repeating_subsequence(X1) << "\n";

    string X2 = "axxxy";
    cout << "Input: " << X2
         << " → LRS length = " << sol.longest_repeating_subsequence(X2) << "\n";

    return 0;
}
