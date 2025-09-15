/*
File: max_number_insertions_deletions_to_convert_a_to_b.cpp
Date: 2025-09-14 16:11

Problem: Minimum number of insertions and deletions to convert string A to string B
Link: URL

Problem Statement:
------------------
Given two strings A and B, find the minimum number of insertions and deletions
required to convert A into B. Only insertion and deletion operations are allowed.

Examples:
---------
Input:
A = "heap"
B = "pea"

Output:
Insertions = 1, Deletions = 2

Explanation:
LCS("heap", "pea") = "ea" (length = 2).
Deletions = |A| - LCS = 4 - 2 = 2
Insertions = |B| - LCS = 3 - 2 = 1

-------------------------------------------------
❌ Brute Force
- Idea: Try all possible edit sequences.
- Time complexity: Exponential.
- Space complexity: O(1).
- Limitations: Not feasible for larger strings.

✅ Optimized Approach (Using LCS)
- Idea:
  - Compute the length of the Longest Common Subsequence (LCS).
  - Deletions = |A| - LCS
  - Insertions = |B| - LCS
- Time complexity: O(n * m).
- Space complexity: O(n * m).

💡 Key Pattern:
- This is a variant of Edit Distance but restricted to only insertions and deletions.

Keywords:
- LCS
- Dynamic Programming
- Edit Distance Variant

🗒️ Notes:
- Remember off-by-one indexing in DP table.
- Insertions and deletions are inversely tied to LCS length.
-------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    vector<int> min_insertions_deletions(const string &A, const string &B)
    {
        int n = A.size(), m = B.size();
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

        // Compute LCS length
        for (int i = 1; i <= n; ++i)
        {
            for (int j = 1; j <= m; ++j)
            {
                if (A[i - 1] == B[j - 1])
                    dp[i][j] = 1 + dp[i - 1][j - 1];
                else
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }

        int lcs = dp[n][m];
        int deletions = n - lcs;
        int insertions = m - lcs;

        return {insertions, deletions};
    }
};

int main()
{
    Solution sol;

    string A = "heap";
    string B = "pea";

    auto result = sol.min_insertions_deletions(A, B);
    cout << "Insertions = " << result[0]
         << ", Deletions = " << result[1] << "\n";

    return 0;
}
