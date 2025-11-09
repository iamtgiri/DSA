/*
File: Dice_Sum_Ways.cpp
Date: 2025-11-09 17:10

Problem: Dice Sum Ways

Problem Statement:
Given three integers N, M, and X:
    - N → Number of dice
    - M → Number of faces on each die (faces are numbered 1 to M)
    - X → Target sum

You are required to find the total number of ways to obtain the sum X
when all N dice are rolled together.

-------------------------------------------------
Brute Force (if any, ignore if not applicable)
- Idea: Enumerate all possible outcomes of rolling N dice, summing
  each combination and counting those equal to X.
- Time complexity: O(M^N), since each die can take M values.
- Space complexity: O(1).
- Limitations: Exponential growth — not feasible for N > 10 or large M.

Current/Optimized Approach
- Idea: Use **Dynamic Programming** to count the number of ways
  to achieve each possible sum using smaller subproblems.
- Approach: **Bottom-Up DP (Tabulation)**
- Algorithm:
  1. Define dp[i][j] = number of ways to achieve sum j using i dice.
  2. Base case: dp[0][0] = 1 (one way to get sum 0 with 0 dice).
  3. Transition:
        dp[i][j] = Σ (dp[i-1][j-k]) for all k in [1, M] and k ≤ j.
     This means: for each possible face value k, check how many ways
     we could make the remaining sum j-k with one less die.
  4. The final answer is dp[N][X].

- Time complexity: O(N * M * X)
- Space complexity: O(N * X)
  (can be optimized to O(X) using rolling arrays)

💡 Key Pattern:
- **Subset Sum DP Analogy:** Similar to counting ways to make a total sum
  using bounded items (each die roll represents a bounded choice of [1..M]).
- **Overlap of Subproblems:** Each state (i, j) builds on smaller dice counts.

ℹ️ Keywords:
- Dynamic Programming, Combinatorics, Tabulation, Dice Throw Problem.

🗒️ Notes
- This is equivalent to the “number of dice rolls with target sum” problem.
- The result can grow large; in competitive problems, it’s often returned
  modulo 1e9+7.
-------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    /**
     * @brief Calculates the number of ways to get a target sum X
     *        using N dice with M faces each.
     * @param N Number of dice
     * @param M Number of faces per die
     * @param X Target sum
     * @return Number of possible ways to achieve sum X
     */
    long long findWays(int N, int M, int X)
    {
        vector<vector<long long>> dp(N + 1, vector<long long>(X + 1, 0));
        dp[0][0] = 1;

        for (int i = 1; i <= N; i++)
        {
            for (int j = 1; j <= X; j++)
            {
                for (int k = 1; k <= M && k <= j; k++)
                {
                    dp[i][j] += dp[i - 1][j - k];
                }
            }
        }
        return dp[N][X];
    }

    /**
     * @brief Optimized O(X) space version of findWays
     */
    long long findWaysOptimized(int N, int M, int X)
    {
        vector<long long> prev(X + 1, 0), curr(X + 1, 0);
        prev[0] = 1;

        for (int i = 1; i <= N; i++)
        {
            fill(curr.begin(), curr.end(), 0);
            for (int j = 1; j <= X; j++)
            {
                for (int k = 1; k <= M && k <= j; k++)
                {
                    curr[j] += prev[j - k];
                }
            }
            prev.swap(curr);
        }

        return prev[X];
    }
};

int main()
{
    Solution sol;

    // Test Case 1
    int N1 = 2, M1 = 6, X1 = 7;
    cout << "Input: N=" << N1 << ", M=" << M1 << ", X=" << X1 << "\n";
    cout << "Output: " << sol.findWays(N1, M1, X1) << endl; // Expected: 6

    // Test Case 2
    int N2 = 3, M2 = 6, X2 = 8;
    cout << "Input: N=" << N2 << ", M=" << M2 << ", X=" << X2 << "\n";
    cout << "Output: " << sol.findWays(N2, M2, X2) << endl; // Expected: 21

    // Test Case 3 (Edge Case)
    int N3 = 1, M3 = 6, X3 = 3;
    cout << "Input: N=" << N3 << ", M=" << M3 << ", X=" << X3 << "\n";
    cout << "Output: " << sol.findWays(N3, M3, X3) << endl; // Expected: 1

    // Test Case 4 (Large target)
    int N4 = 3, M4 = 8, X4 = 15;
    cout << "Input: N=" << N4 << ", M=" << M4 << ", X=" << X4 << "\n";
    cout << "Output: " << sol.findWays(N4, M4, X4) << endl;

    return 0;
}
