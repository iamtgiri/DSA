/*
File: longest_common_substring.cpp
Date: 2025-09-12 17:41

Problem: Longest Common Substring
Link: URL

Problem Statement:
------------------
Given two strings X and Y, find the length of their **Longest Common Substring**.
- A substring is a contiguous sequence of characters within a string.
- The longest common substring is the longest contiguous sequence
  of characters present in both X and Y.

Examples:
---------
Input:
X = "abcdxyz"
Y = "xyzabcd"

Output:
4
Explanation: The longest common substring is "abcd" (length = 4).

-------------------------------------------------
❌ Brute Force
- Idea: Generate all substrings of X and check if present in Y.
- Time complexity: O(n² * m) [too slow].
- Space complexity: O(1).
- Limitations: Exponential checks, infeasible for large strings.

✅ Optimized Approach (Dynamic Programming)
- Idea: Use a DP table where dp[i][j] represents the length of the longest
        common substring ending at X[i-1] and Y[j-1].
- Transition:
    If X[i-1] == Y[j-1] → dp[i][j] = 1 + dp[i-1][j-1]
    Else                → dp[i][j] = 0
- Track maximum over all dp[i][j].
- Time complexity: O(n * m)
- Space complexity: O(n * m) [can be optimized to O(min(n, m))].

💡 Key Pattern:
- Unlike LCS (Longest Common Subsequence), mismatch resets length to 0.
- Contiguity is the key difference.

Keywords:
- DP
- String Matching
- Longest Common Substring

🗒️ Notes:
- Watch out for off-by-one indexing.
- Useful in plagiarism detection, bioinformatics, and text similarity.
-------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int longest_common_substring(const string &X, const string &Y)
    {
        int n = X.size(), m = Y.size();
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

        int result = 0; // track maximum length

        for (int i = 1; i <= n; ++i)
        {
            for (int j = 1; j <= m; ++j)
            {
                if (X[i - 1] == Y[j - 1])
                {
                    dp[i][j] = 1 + dp[i - 1][j - 1];
                    result = max(result, dp[i][j]);
                }
                else
                {
                    dp[i][j] = 0; // reset if mismatch
                }
            }
        }
        return result;
    }
};

int main()
{
    Solution sol;

    string X = "abcdxyz";
    string Y = "xyzabcd";

    cout << "Length of Longest Common Substring: "
         << sol.longest_common_substring(X, Y) << "\n";

    return 0;
}
