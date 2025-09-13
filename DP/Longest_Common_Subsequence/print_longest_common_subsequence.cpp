/*
File: print_longest_common_subsequence.cpp
Date: 2025-09-12 22:39

Problem: Print Longest Common Subsequence (LCS)
Link: URL

Problem Statement:
------------------
Given two strings X and Y, find and print their **Longest Common Subsequence (LCS)**.
- A subsequence is a sequence derived from another sequence by deleting some
  elements without changing the order of the remaining elements.
- Unlike substring, subsequence need not be contiguous.

Examples:
---------
Input:
X = "abcdxyz"
Y = "xyzabcd"

Output:
"abcd"

-------------------------------------------------
❌ Brute Force
- Idea: Try all subsequences of X and check if present in Y.
- Time complexity: O(2^n * 2^m).
- Space complexity: O(1).
- Limitations: Impractical for large strings.

✅ Optimized Approach (Dynamic Programming)
- Idea: Use a DP table where dp[i][j] = length of LCS of X[0..i-1] and Y[0..j-1].
- After filling dp, reconstruct subsequence by backtracking from dp[n][m].
- Time complexity: O(n * m).
- Space complexity: O(n * m).

💡 Key Pattern:
- Similar to Edit Distance and LCSubstring, but mismatch leads to max() instead of reset.

Keywords:
- LCS
- Dynamic Programming
- String Matching

🗒️ Notes:
- Backtracking from dp[n][m] is essential to reconstruct sequence.
-------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    string get_longest_common_subseq(string X, string Y)
    {
        int n = X.size(), m = Y.size();
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

        // Step 1: Fill DP table
        for (int i = 1; i <= n; ++i)
        {
            for (int j = 1; j <= m; ++j)
            {
                if (X[i - 1] == Y[j - 1])
                {
                    dp[i][j] = 1 + dp[i - 1][j - 1];
                }
                else
                {
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }

        // Step 2: Backtrack to construct subsequence
        string subseq = "";
        int i = n, j = m;
        while (i > 0 && j > 0)
        {
            if (X[i - 1] == Y[j - 1])
            {
                subseq.push_back(X[i - 1]); // add matched char
                --i; --j;
            }
            else if (dp[i - 1][j] > dp[i][j - 1])
            {
                --i; // move up
            }
            else
            {
                --j; // move left
            }
        }

        reverse(subseq.begin(), subseq.end()); // reverse because built backwards
        return subseq;
    }
};

int main()
{
    Solution sol;

    string X = "abcdxyz";
    string Y = "xyzabcd";

    string subseq = sol.get_longest_common_subseq(X, Y);
    if (!subseq.empty())
        cout << "Longest Common Subsequence: " << subseq << "\n";
    else
        cout << "No common subsequence found.\n";

    return 0;
}
