/*
File: min_insertion_to_make_palindrome.cpp
Date: 2025-09-15 13:14

Problem: Minimum Number of Insertions Required to Make a String Palindrome
Link: URL

Problem Statement:
------------------
Given a string X, find the minimum number of insertions required
to make it a palindrome.

Example:
--------
Input: "abcda"
Output: 2
Explanation: Insert "d" and "c" → "adcbcda"

-------------------------------------------------
❌ Brute Force
- Idea: Try all possible insertions until palindrome is formed.
- Time complexity: Exponential.
- Space complexity: O(1).
- Limitations: Not feasible for n > 20.

✅ Optimized Approach (DP + LCS)
- Idea:
  - The minimum insertions = n - LPS_length,
    where LPS_length is the length of the Longest Palindromic Subsequence (LPS).
  - LPS can be computed as LCS(X, reverse(X)).
- Time complexity: O(n^2).
- Space complexity: O(n^2).

💡 Key Pattern:
- Palindrome problems often reduce to LCS with the reversed string.

Keywords:
- LCS
- LPS
- Palindrome
- Dynamic Programming

🗒️ Notes
- Remember: Deletions and insertions for palindrome problems
  are symmetric (n - LPS).
-------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int min_insertions_to_make_palindrome(const string &X) {
        string Y = X;
        reverse(Y.begin(), Y.end());

        int n = X.size();
        vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));

        // Compute LCS(X, Y) → gives LPS length
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (X[i - 1] == Y[j - 1])
                    dp[i][j] = 1 + dp[i - 1][j - 1];
                else
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }

        int lps = dp[n][n];
        return n - lps; // minimum insertions = total length - LPS length
    }
};

int main() {
    Solution sol;

    cout << sol.min_insertions_to_make_palindrome("abcda") << "\n"; // 2
    cout << sol.min_insertions_to_make_palindrome("race") << "\n";  // 3 ("ecarace")
    cout << sol.min_insertions_to_make_palindrome("a") << "\n";     // 0
    cout << sol.min_insertions_to_make_palindrome("ab") << "\n";    // 1

    return 0;
}
