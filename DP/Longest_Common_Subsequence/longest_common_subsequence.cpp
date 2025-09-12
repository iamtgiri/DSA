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

✅ Optimized Approach (DP)
- Idea: Memoization or Tabulation to avoid recomputation.
- Time complexity: O(n * m)
- Space complexity: O(n * m) [can be optimized to O(min(n, m))]

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
    // 1. Recursive (brute force)
    int LCS(string &X, int n, string &Y, int m)
    {
        if (n == 0 || m == 0)
            return 0;

        if (X[n - 1] == Y[m - 1]) // compare last characters
            return 1 + LCS(X, n - 1, Y, m - 1);
        else
            return max(LCS(X, n - 1, Y, m), LCS(X, n, Y, m - 1));
    }
};

int main()
{
    Solution sol;

    string X = "abcdgh";
    string Y = "abedfhr";

    cout << "LCS length = " << sol.LCS(X, X.size(), Y, Y.size()) << "\n";
    return 0;
}
