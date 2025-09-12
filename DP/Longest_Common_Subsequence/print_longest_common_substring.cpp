/*
File: print_longest_common_substring.cpp
Date: 2025-09-12 17:52

Problem: Print Longest Common Substring
Link: URL

Problem Statement:
------------------
Given two strings X and Y, find and print their **Longest Common Substring (LCSubStr)**.
- A substring is a contiguous block of characters within a string.
- If there are multiple answers, printing any one valid substring is acceptable.

Examples:
---------
Input:
X = "abcdxyz"
Y = "xyzabcd"

Output:
"abcd"

-------------------------------------------------
❌ Brute Force
- Idea: Generate all substrings of X and check if present in Y.
- Time complexity: O(n² * m).
- Space complexity: O(1).
- Limitations: Too slow for larger strings.

✅ Optimized Approach (Dynamic Programming)
- Idea: Use DP where dp[i][j] = length of longest common substring ending at X[i-1], Y[j-1].
- Keep track of maximum length and starting index.
- Time complexity: O(n * m).
- Space complexity: O(n * m).

💡 Key Pattern:
- Unlike LCS (subsequence), mismatches reset to 0.
- Contiguity is the critical property.

Keywords:
- DP
- Longest Common Substring
- String Matching

🗒️ Notes:
- Careful with indexing when extracting substring.
- Multiple valid substrings may exist if ties occur.
-------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    string print_longest_common_substring(const string &X, const string &Y)
    {
        int n = X.size(), m = Y.size();
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

        int max_len = 0, start_index = -1;

        for (int i = 1; i <= n; ++i)
        {
            for (int j = 1; j <= m; ++j)
            {
                if (X[i - 1] == Y[j - 1])
                {
                    dp[i][j] = 1 + dp[i - 1][j - 1];
                    if (dp[i][j] > max_len)
                    {
                        max_len = dp[i][j];
                        start_index = i - max_len; // track start in X
                    }
                }
                else
                {
                    dp[i][j] = 0; // reset if mismatch
                }
            }
        }

        if (start_index == -1)
            return "";
        else
            return X.substr(start_index, max_len);
    }
};

int main()
{
    Solution sol;

    string X = "abcdxyz";
    string Y = "xyzabcd";

    string substr = sol.print_longest_common_substring(X, Y);
    if (substr != "")
        cout << "Longest Common Substring: " << substr << "\n";
    else
        cout << "No common substring found.\n";

    return 0;
}
