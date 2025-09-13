/*
File: length_of_shortest_common_supersequence.cpp
Date: 2025-09-13 19:14

Problem: Shortest Common Supersequence (SCS)
Link: URL

Problem Statement:
------------------
Given two strings X and Y, find the length of their **Shortest Common Supersequence (SCS)**.
- A supersequence of two strings is a string that contains both X and Y as subsequences.
- The goal is to find the minimum length of such a string.

Examples:
---------
Input:
X = "AGGTAB"
Y = "GXTXAYB"

Output:
9

Explanation:
The Shortest Common Supersequence is "AGXGTXAYB" or "AGGXTXAYB", both of length 9.

-------------------------------------------------
❌ Brute Force
- Idea: Generate all supersequences and pick the shortest.
- Time complexity: Exponential.
- Space complexity: O(1).
- Limitations: Not feasible for large strings.

✅ Optimized Approach (Using LCS)
- Idea:
  Length of SCS = |X| + |Y| - LCS(X, Y).
  - First compute LCS length using DP.
  - Then apply formula.
- Time complexity: O(n * m).
- Space complexity: O(n * m).

💡 Key Pattern:
- SCS is built on the LCS relationship.
- Longer the LCS, shorter the SCS.

Keywords:
- LCS
- SCS
- Dynamic Programming
- String DP

🗒️ Notes:
- Useful in problems related to string merging and data compression.
-------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int length_SCS(const string &X, const string &Y)
    {
        int n = X.size(), m = Y.size();
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

        // Compute LCS
        for (int i = 1; i <= n; ++i)
        {
            for (int j = 1; j <= m; ++j)
            {
                if (X[i - 1] == Y[j - 1])
                    dp[i][j] = 1 + dp[i - 1][j - 1];
                else
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }

        // Apply formula
        return n + m - dp[n][m];
    }
};

int main()
{
    Solution sol;

    string X = "AGGTAB";
    string Y = "GXTXAYB";

    cout << "Length of Shortest Common Supersequence: "
         << sol.length_SCS(X, Y) << "\n";

    return 0;
}
