/*
File: Assign_Cookies.cpp
Date: 2025-09-19 22:45

Problem: Assign Cookies
Link: https://leetcode.com/problems/assign-cookies/

Problem Statement:
------------------
Each child has a "greed factor" g[i], representing the minimum size of cookie 
they need to be satisfied. Each cookie has a size s[j]. A child can receive 
at most one cookie, and a cookie can be given to at most one child.

Goal: Maximize the number of satisfied children.

-------------------------------------------------
❌ Brute Force
- Idea: Try all assignments of cookies to children.
- Time complexity: O(n! * m!), infeasible.
- Space complexity: O(1).
- Limitations: Exponential explosion.

✅ Optimized Approach (Greedy + Sorting)
- Idea:
  1. Sort both greed factors and cookie sizes.
  2. Use two pointers: one for children, one for cookies.
  3. Assign the smallest cookie that can satisfy the current child.
  4. Move to next child when satisfied; otherwise, try the next bigger cookie.
- Time complexity: O(n log n + m log m).
- Space complexity: O(1).

✅ Alternative Approach (DP: LCS-style)
- Idea:
  1. Sort greed factors and cookie sizes.
  2. Use DP where dp[i][j] = max number of satisfied children
     using first i children and first j cookies.
  3. Transition:
     - If s[j-1] >= g[i-1], then we can either:
       - match: 1 + dp[i-1][j-1]
       - skip: max(dp[i-1][j], dp[i][j-1])
     - Otherwise: dp[i][j] = max(dp[i-1][j], dp[i][j-1]).
- Time complexity: O(n * m).
- Space complexity: O(n * m) (can optimize to O(min(n, m))).

💡 Key Pattern:
- Greedy matching with two pointers (optimal).
- DP is like an LCS variant (educational, but slower).

Keywords:
- Greedy
- Two Pointers
- Sorting
- Dynamic Programming
- LCS Variant

🗒️ Notes
- Greedy is optimal for this problem.
- DP helps understand the problem as a matching problem.
-------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // --- Greedy Solution ---
    int findContentChildrenGreedy(vector<int>& g, vector<int>& s) {
        sort(g.begin(), g.end());
        sort(s.begin(), s.end());

        int child = 0, cookie = 0;
        int n = g.size(), m = s.size();

        while (child < n && cookie < m) {
            if (s[cookie] >= g[child]) {
                // Assign this cookie to the child
                child++;
            }
            // Always move to next cookie
            cookie++;
        }
        return child;
    }

    // --- DP (LCS-style) Solution ---
    int findContentChildrenDP(vector<int>& g, vector<int>& s) {
        int n = g.size(), m = s.size();
        sort(g.begin(), g.end());
        sort(s.begin(), s.end());

        vector<vector<int>> dp(n+1, vector<int>(m+1, 0));

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (s[j-1] >= g[i-1]) {
                    dp[i][j] = max({
                        dp[i-1][j],     // skip child
                        dp[i][j-1],     // skip cookie
                        1 + dp[i-1][j-1] // match
                    });
                } else {
                    dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
                }
            }
        }

        return dp[n][m];
    }
};

// --- Main Function ---
int main() {
    Solution sol;

    vector<int> g1 = {1,2,3}, s1 = {1,1};
    cout << "Greedy: " << sol.findContentChildrenGreedy(g1, s1) << "\n"; // 1
    cout << "DP: " << sol.findContentChildrenDP(g1, s1) << "\n";         // 1

    vector<int> g2 = {1,2}, s2 = {1,2,3};
    cout << "Greedy: " << sol.findContentChildrenGreedy(g2, s2) << "\n"; // 2
    cout << "DP: " << sol.findContentChildrenDP(g2, s2) << "\n";         // 2

    return 0;
}
