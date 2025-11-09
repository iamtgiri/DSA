/*
File: palindrome_partitioning.cpp
Date: 2025-09-15 17:19

Problem: Palindrome Partitioning (Min Cuts)
Link: URL

Problem Statement:
------------------
Given a string s, partition it such that every substring of the
partition is a palindrome. Return the minimum number of cuts needed.

Example:
--------
Input: "aab"
Output: 1
Explanation: ["aa","b"]

-------------------------------------------------
❌ Brute Force
- Idea: Try all possible cuts and check if each substring is a palindrome.
- Time complexity: Exponential (O(2^n)).
- Space complexity: O(n).
- Limitations: Very slow for n > 15.

✅ Optimized Approach 1 (Recursion + Memoization)
- Idea:
  - Use DP with memoization.
  - State: dp[i][j] = min cuts to partition s[i..j].
  - Transition: If s[i..j] is palindrome → 0.
    Else: min over k (dp[i][k] + dp[k+1][j] + 1).
- Time complexity: O(n^3).
- Space complexity: O(n^2).

✅ Optimized Approach 2 (Bottom-Up Tabulation)
- Idea:
  - dp[i] = min cuts needed for substring s[0..i].
  - Precompute palindrome table isPal[i][j].
  - Transition:
    - If s[0..i] is palindrome → dp[i] = 0
    - Else dp[i] = min(dp[j] + 1) for all j < i if s[j+1..i] is palindrome.
- Time complexity: O(n^2).
- Space complexity: O(n^2).

💡 Key Pattern:
- Interval DP
- Palindrome table precomputation

Keywords:
- Palindrome Partitioning
- DP on substrings
- Min Cuts

🗒️ Notes
- Must pass dp by reference to avoid recomputation.
- Precomputing palindrome table reduces complexity from O(n^3) → O(n^2).
-------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // --- Pure Recursion ---
    int partition_to_palindrome(const string &s, int i, int j) {
        if (i >= j) return 0;
        if (is_palindrome(s, i, j)) return 0;

        int ans = INT_MAX;
        for (int k = i; k < j; ++k) {
            int temp_ans = 1 + partition_to_palindrome(s, i, k)
                             + partition_to_palindrome(s, k + 1, j);
            ans = min(ans, temp_ans);
        }
        return ans;
    }

    // --- Memoization (Top-Down) ---
    int memo(string &s) {
        int n = s.size();
        vector<vector<int>> dp(n, vector<int>(n, -1));
        return memo_helper(s, 0, n - 1, dp);
    }

    int memo_helper(string &s, int i, int j, vector<vector<int>> &dp) {
        if (i >= j) return 0;
        if (is_palindrome(s, i, j)) return 0;
        if (dp[i][j] != -1) return dp[i][j];

        int ans = INT_MAX;
        for (int k = i; k < j; ++k) {
            int left = memo_helper(s, i, k, dp);
            int right = memo_helper(s, k + 1, j, dp);
            int temp_ans = 1 + left + right;
            ans = min(ans, temp_ans);
        }
        return dp[i][j] = ans;
    }

    // --- Tabulation (Bottom-Up) ---
    int tabulation(string &s) {
        int n = s.size();
        vector<int> dp(n, 0);
        vector<vector<bool>> isPal(n, vector<bool>(n, false));

        // Precompute palindrome table
        for (int i = n - 1; i >= 0; --i) {
            for (int j = i; j < n; ++j) {
                if (s[i] == s[j] && (j - i <= 2 || isPal[i + 1][j - 1])) {
                    isPal[i][j] = true;
                }
            }
        }

        for (int i = 0; i < n; ++i) {
            if (isPal[0][i]) {
                dp[i] = 0; // whole substring is palindrome
            } else {
                dp[i] = INT_MAX;
                for (int j = 0; j < i; ++j) {
                    if (isPal[j + 1][i]) {
                        dp[i] = min(dp[i], dp[j] + 1);
                    }
                }
            }
        }

        return dp[n - 1];
    }

private:
    bool is_palindrome(const string &s, int i, int j) {
        while (i < j) {
            if (s[i++] != s[j--]) return false;
        }
        return true;
    }
};

// --- Main Function ---
int main() {
    Solution sol;
    string s = "aab";
    cout << "Recursion: " << sol.partition_to_palindrome(s, 0, s.size() - 1) << "\n";
    cout << "Memoization: " << sol.memo(s) << "\n";
    cout << "Tabulation: " << sol.tabulation(s) << "\n";
    return 0;
}
