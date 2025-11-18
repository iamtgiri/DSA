/*
File: Soup_Servings.cpp
Date: 2025-11-18 23:49

Problem: Soup Servings
Link: https://leetcode.com/problems/soup-servings/description/

Problem Statement:
There are two bowls of soup, A and B, each initially containing N milliliters of soup.
We perform a series of servings, each with a 25% probability for one of four outcomes:
1. Serve 100 ml of A and 0 ml of B (i.e., A - 4, B - 0)
2. Serve 75 ml of A and 25 ml of B (i.e., A - 3, B - 1)
3. Serve 50 ml of A and 50 ml of B (i.e., A - 2, B - 2)
4. Serve 25 ml of A and 75 ml of B (i.e., A - 1, B - 3)

The serving stops when a bowl is empty. Find the probability that soup A runs out first,
plus half the probability that both soups run out simultaneously.

-------------------------------------------------
Brute Force (if any, ignore if not applicable)
- Idea: Recursive simulation without memoization. Explore all possible serving paths
  until a termination condition (A runs out, B runs out, or both run out) is met.
- Time complexity: O(4^(N/25)). Exponential time complexity due to redundant subproblems.
- Space complexity: O(N/25) for recursion depth.
- Limitations: Infeasible for large N due to Time Limit Exceeded (TLE).

Current/Optimized Approachs
- Idea: This is a Dynamic Programming problem on probability. The state is defined by the remaining amounts of
  soup (A, B). Since the transitions are fixed and many states are revisited,
  Memoization is used to calculate the probability for each state exactly once.
- Approach: **Memoization (Top-Down Dynamic Programming)**
- Algorithm:
  1. **Scaling:** Convert N ml to units of 25 ml: M = ceil(N/25).
  2. **Optimization (Cutoff):** If N is large (e.g., N >= 4800), the probability is extremely close to 1.0. Return 1.0.
  3. **State:** P(a, b) is the required probability when a and b units of soup remain.
  4. **Base Cases:**
     - a <= 0 and b <= 0: Both run out. P(a, b) = 0.5.
     - a <= 0 and b > 0: A runs out first. P(a, b) = 1.0.
     - a > 0 and b <= 0: B runs out first. P(a, b) = 0.0.
  5. **Recurrence:**
     P(a, b) = 0.25 * [P(a-4, b) + P(a-3, b-1) + P(a-2, b-2) + P(a-1, b-3)]
  6. **Memoization:** Store P(a, b) in a 2D DP table to avoid recomputation.
- Time complexity: O(M^2), where M = ceil(N/25). Due to the cutoff, this is effectively O(1) constant time complexity.
- Space complexity: O(M^2) for the 2D memoization table.

💡 Key Pattern:
- **Dynamic Programming on Probability:** Calculating the probability of reaching a target state by summing probabilities of previous states weighted by transition likelihoods.

ℹ️ Keywords:
- Dynamic Programming, Probability, Memoization, State Transition, Recurrence Relation.

🗒️ Notes
- The required scaling in the initial call: m = (n + 24) / 25; correctly handles the rounding up to units of 25 ml.
- The cutoff value (4800) is crucial for passing time limits and is based on the problem's mathematical convergence.
-------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    /**
     * @brief Helper function for memoized calculation of probability P(a, b).
     * @param a Remaining units of soup A (scaled by 25ml).
     * @param b Remaining units of soup B (scaled by 25ml).
     * @param dp Memoization table.
     * @return The required probability.
     */
    double serve(int a, int b, vector<vector<double>> &dp)
    {
        // Base Case 1: Both soups run out simultaneously
        if (a <= 0 && b <= 0)
            return 0.5;
        // Base Case 2: Soup A runs out first
        if (a <= 0)
            return 1.0;
        // Base Case 3: Soup B runs out first (not A)
        if (b <= 0)
            return 0.0;

        // Check Memoization table
        if (dp[a][b] >= 0)
            return dp[a][b];

        // Recurrence Relation (all 4 choices have 0.25 probability)
        return dp[a][b] =
                   0.25 * (serve(a - 4, b, dp) + serve(a - 3, b - 1, dp) +
                           serve(a - 2, b - 2, dp) + serve(a - 1, b - 3, dp));
    }

    /**
     * @brief Calculates the probability for the Soup Servings problem.
     * @param n Initial amount of soup A and B in ml.
     * @return The probability that A runs out first + 0.5 * probability that both run out simultaneously.
     */
    double soupServings(int n)
    {
        // Cutoff Optimization: For large N, the probability converges quickly to 1.0.
        // N=4800 corresponds to M=192 units. Beyond this, the probability is near 1.0.
        // The probability that A runs out first approaches 1 as N increases,
        // since A is consumed more aggressively than B on average.
        if (n >= 4800)
            return 1.0;

        // Scale N (ml) to M (25ml units), rounding up.
        // E.g., 50ml -> 2 units. 51ml -> 3 units (since one 100ml serving can empty the bowl).
        int m = (n + 24) / 25;

        // Initialize DP table. Size (m+1) x (m+1). -1.0 indicates uncalculated state.
        vector<vector<double>> dp(m + 1, vector<double>(m + 1, -1.0));

        // Start the recursive calculation from the initial state (m, m)
        return serve(m, m, dp);
    }
};

int main()
{
    Solution sol;

    int n1 = 50;
    // Expected: P(50, 50) = 0.625
    cout << "N=" << n1 << ", Probability: " << sol.soupServings(n1) << endl;

    int n2 = 100;
    // Expected: P(100, 100) = 0.71875
    cout << "N=" << n2 << ", Probability: " << sol.soupServings(n2) << endl;

    int n3 = 5000; // Triggers the cutoff
    cout << "N=" << n3 << ", Probability: " << sol.soupServings(n3) << endl;

    return 0;
}