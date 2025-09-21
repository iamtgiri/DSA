/*
File: min_deletion_to_make_palindrome.cpp
Date: 2025-09-14 16:52

Problem: Minimum Number of Deletions to Make a String Palindrome
Link: URL

Problem Statement:
------------------
Given a string X, find the minimum number of deletions required to make it a palindrome.

Examples:
---------
Input: "agbcba"
Output: 1
Explanation:
The longest palindromic subsequence is "abcba" (length = 5).
Min deletions = |X| - LPS(X) = 6 - 5 = 1.

-------------------------------------------------
❌ Brute Force
- Idea: Try deleting characters in all possible ways until a palindrome is formed.
- Time complexity: Exponential.
- Space complexity: O(1).
- Limitations: Not feasible for large strings.

✅ Optimized Approach (Using LPS)
- Idea:
  - LPS(X) = LCS(X, reverse(X)).
  - Minimum deletions = |X| - LPS(X).
- Time complexity: O(n^2).
- Space complexity: O(n^2).

💡 Key Pattern:
- LPS is the backbone for many palindrome-related problems.

Keywords:
- LCS
- LPS
- Dynamic Programming
- String DP

🗒️ Notes:
- Similar approach applies to "Insertions to Make a String Palindrome".
-------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int min_deletions_to_make_palindrome(const string &X)
    {
        string Y = X;
        reverse(Y.begin(), Y.end());

        int n = X.size();
        vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));

        // Compute LCS(X, Y) → gives LPS length
        for (int i = 1; i <= n; ++i)
        {
            for (int j = 1; j <= n; ++j)
            {
                if (X[i - 1] == Y[j - 1])
                    dp[i][j] = 1 + dp[i - 1][j - 1];
                else
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }

        int lps = dp[n][n];
        return n - lps; // min deletions
    }
};

int main()
{
    Solution sol;

    string X = "agbcba";
    cout << "Minimum deletions to make \"" << X
         << "\" a palindrome: "
         << sol.min_deletions_to_make_palindrome(X) << "\n";

    return 0;
}
