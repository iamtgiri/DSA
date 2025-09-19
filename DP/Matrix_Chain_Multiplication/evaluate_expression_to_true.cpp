/*
File: evaluate_expression_to_true.cpp
Date: 2025-09-19 18:45

Problem: Evaluate Expression to True (Boolean Parenthesization)
Link: URL

Problem Statement:
------------------
Given a boolean expression with symbols 'T' (true) and 'F' (false),
and operators '&' (AND), '|' (OR), '^' (XOR),
count the number of ways to parenthesize the expression
such that it evaluates to True.

-------------------------------------------------
❌ Brute Force
- Idea: Try all ways of parenthesizing recursively.
- Time complexity: Exponential (O(2^n)).
- Space complexity: O(n).
- Limitations: Explodes for length > 15.

✅ Optimized Approach (Recursion + Memoization)
- Idea:
  - Define dp(i,j,isTrue) = ways to evaluate s[i..j] to isTrue.
  - Split at every operator k.
  - Combine results of left/right based on operator truth table.
  - Store results in a memo table.
- Time complexity: O(n^3).
- Space complexity: O(n^2).

💡 Key Pattern:
- Interval DP
- Similar to Matrix Chain Multiplication / Palindrome Partitioning

Keywords:
- Boolean Parenthesization
- DP on intervals
- Evaluate Expression

🗒️ Notes
- Must pass dp by reference to retain memoization.
- Careful with operator precedence and cases.
-------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int solver(string &s, int i, int j, bool isTrue, unordered_map<string, int> &dp) {
        if (i > j) return 0;
        if (i == j) {
            if (isTrue) return (s[i] == 'T');
            else return (s[i] == 'F');
        }

        string key = to_string(i) + "_" + to_string(j) + "_" + to_string(isTrue);
        if (dp.find(key) != dp.end()) return dp[key];

        int ways = 0;
        for (int k = i + 1; k <= j - 1; k += 2) { // operators at odd positions
            int lt = solver(s, i, k - 1, true, dp);
            int lf = solver(s, i, k - 1, false, dp);
            int rt = solver(s, k + 1, j, true, dp);
            int rf = solver(s, k + 1, j, false, dp);

            if (s[k] == '&') {
                if (isTrue) ways += (lt * rt);
                else ways += (lt * rf + lf * rt + lf * rf);
            }
            else if (s[k] == '|') {
                if (isTrue) ways += (lt * rt + lt * rf + lf * rt);
                else ways += (lf * rf);
            }
            else if (s[k] == '^') {
                if (isTrue) ways += (lt * rf + lf * rt);
                else ways += (lt * rt + lf * rf);
            }
        }

        return dp[key] = ways;
    }

    int countWays(string s) {
        unordered_map<string, int> dp;
        return solver(s, 0, s.size() - 1, true, dp);
    }
};

int main() {
    Solution sol;
    string s = "T|F&T^F";
    cout << "Number of ways to True: " << sol.countWays(s) << "\n"; // Expected output: number of ways to True
    return 0;
}
