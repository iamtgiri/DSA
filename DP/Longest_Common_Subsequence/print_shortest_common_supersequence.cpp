/*
File: print_shortest_common_supersequence.cpp
Date: 2025-09-14 17:12

Problem: Print Shortest Common Supersequence (SCS)
Link: URL

Problem Statement:
------------------
Given two strings X and Y, print their shortest common supersequence (SCS).
- A supersequence is a string that contains both X and Y as subsequences.
- The SCS is the shortest such string.

Examples:
---------
Input: X = "AGGTAB", Y = "GXTXAYB"
Output: "AGXGTXAYB"

-------------------------------------------------
❌ Brute Force
- Idea: Generate all supersequences and choose the shortest.
- Time complexity: Exponential.
- Space complexity: O(1).
- Limitations: Not feasible for large strings.

✅ Optimized Approach (DP + Backtracking)
- Idea:
  - First compute LCS(X, Y) using DP.
  - Backtrack to merge characters from both strings while preserving order.
- Time complexity: O(n * m).
- Space complexity: O(n * m).

💡 Key Pattern:
- SCS = X + Y - LCS(X, Y).

Keywords:
- LCS
- SCS
- Dynamic Programming
- String Construction

🗒️ Notes:
- Be careful with backtracking and leftover characters.
-------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string get_shortest_common_superseq(const string &X, const string &Y)
    {
        int n = X.size(), m = Y.size();
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

        // Step 1: Fill DP table (LCS)
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

        // Step 2: Backtrack to build SCS
        string scs;
        int i = n, j = m;

        while (i > 0 && j > 0)
        {
            if (X[i - 1] == Y[j - 1])
            {
                scs.push_back(X[i - 1]); // common char (part of LCS)
                --i; --j;
            }
            else if (dp[i - 1][j] > dp[i][j - 1])
            {
                scs.push_back(X[i - 1]);
                --i;
            }
            else
            {
                scs.push_back(Y[j - 1]);
                --j;
            }
        }

        // Add remaining characters (if any)
        while (i > 0) scs.push_back(X[i-- - 1]);
        while (j > 0) scs.push_back(Y[j-- - 1]);

        reverse(scs.begin(), scs.end());
        return scs;
    }
};

int main() {
    Solution sol;

    string X = "AGGTAB";
    string Y = "GXTXAYB";

    cout << "Shortest Common Supersequence of "<<X<< " & "<< Y<<" : "
         << sol.get_shortest_common_superseq(X, Y) << "\n";

    return 0;
}
