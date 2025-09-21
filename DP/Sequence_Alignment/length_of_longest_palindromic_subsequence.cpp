/*
File: length_of_longest_palindromic_subsequence.cpp
Date: 2025-09-14 16:29

Problem: Length of Longest Palindromic Subsequence
Link: URL

Problem Statement:
------------------
Given a string X, find the length of its longest palindromic subsequence (LPS).
- A subsequence is derived from another string by deleting some characters
  without changing the order of the remaining characters.
- The LPS is the longest subsequence that is also a palindrome.

Examples:
---------
Input: "bbabcbcab"
Output: 7
Explanation: The longest palindromic subsequence is "babcbab".

-------------------------------------------------
❌ Brute Force
- Idea: Generate all subsequences and check if palindrome.
- Time complexity: O(2^n).
- Space complexity: O(1).
- Limitations: Not feasible for large strings.

✅ Optimized Approach (Using LCS)
- Idea:
  - LPS(X) = LCS(X, reverse(X)).
  - Use DP to compute LCS length.
- Time complexity: O(n^2).
- Space complexity: O(n^2).

💡 Key Pattern:
- LPS is a direct application of LCS.

Keywords:
- LCS
- LPS
- Dynamic Programming
- String DP

🗒️ Notes:
- Remember that `std::reverse` modifies the string in place.
-------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int longest_palindromic_subseq_length(const string &X)
    {
        string Y = X;
        reverse(Y.begin(), Y.end());

        int n = X.size();
        vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));

        // Compute LCS(X, Y)
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
        return dp[n][n];
    }
};

int main()
{
    Solution sol;

    string X = "bbabcbcab";
    cout << "Length of Longest Palindromic Subsequence: "
         << sol.longest_palindromic_subseq_length(X) << "\n";

    return 0;
}
