/*
File: maximum_ribbon_cut.cpp
Date: 2025-09-12 14:39

Problem: Maximum Ribbon Cut
Link: URL

Problem Statement:
------------------
You are given a ribbon of length `n` and three possible cut lengths: `a`, `b`, and `c`.  
The task is to cut the ribbon into the maximum number of pieces such that every piece 
has a length equal to one of `a`, `b`, or `c`.  
If it is not possible to cut the ribbon exactly, return `-1`.

Examples:
---------
Input:  n = 7, a = 5, b = 2, c = 2
Output: 3
Explanation: 7 = 2 + 2 + 3 is invalid (3 not allowed), 
             but 7 = 2 + 2 + 2 + 1 is invalid (1 not allowed),
             7 = 5 + 2 works (2 pieces),
             maximum achievable = 3 (using allowed cuts).

-------------------------------------------------
❌ Brute Force (Recursion)
- Idea: Try all possible cuts recursively.
- Time complexity: Exponential (O(3^n))
- Space complexity: O(n) recursion depth
- Limitations: Too slow for larger inputs.

✅ Dynamic Programming (Optimized)
- Idea: Use bottom-up DP to maximize number of pieces for each sub-length.
- Transition: dp[i] = max(dp[i - a], dp[i - b], dp[i - c]) + 1
- Time complexity: O(n)
- Space complexity: O(n)

💡 Key Pattern:
- This is the maximization version of the **Unbounded Knapsack Problem**.

Keywords:
- Dynamic Programming
- Unbounded Knapsack
- Maximum Cuts

🗒️ Notes:
- Similar to "Rod Cutting" and "Coin Change (maximize count)".
- Watch out for invalid states (use INT_MIN as sentinel).
-------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // DP approach to find the maximum number of cuts
    int maxRibbonCut(int n, int a, int b, int c) {
        vector<int> dp(n + 1, INT_MIN);
        dp[0] = 0; // Base case: no ribbon = 0 cuts

        for (int i = 1; i <= n; i++) {
            if (i >= a && dp[i - a] != INT_MIN)
                dp[i] = max(dp[i], dp[i - a] + 1);
            if (i >= b && dp[i - b] != INT_MIN)
                dp[i] = max(dp[i], dp[i - b] + 1);
            if (i >= c && dp[i - c] != INT_MIN)
                dp[i] = max(dp[i], dp[i - c] + 1);
        }

        return (dp[n] < 0) ? -1 : dp[n];
    }
};

int main() {
    Solution sol;
    int n, a, b, c;

    cout << "Enter n, a, b, c: ";
    cin >> n >> a >> b >> c;

    int result = sol.maxRibbonCut(n, a, b, c);
    if (result == -1)
        cout << "Impossible to cut the ribbon exactly.\n";
    else
        cout << "Maximum Ribbon Cuts: " << result << "\n";

    return 0;
}
