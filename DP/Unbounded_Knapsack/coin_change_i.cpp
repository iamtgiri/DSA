#include <iostream>
#include <vector>
using namespace std;

/*
File: coin_change_i.cpp
Date: 2025-09-12 09:59

Problem: Coin Change I
Link: URL

Problem Statement:
------------------
You are given:
- An array coins[] representing distinct coin denominations.
- An integer amount (target sum).

Task:
Count the number of combinations to make up that amount using the coins.
- You may use each coin unlimited times.
- The order of coins does NOT matter (1+3 == 3+1).

Example:
--------
coins = [1, 2, 3], amount = 4

Ways:
- 1+1+1+1
- 1+1+2
- 2+2
- 1+3
Answer = 4

This is an **Unbounded Knapsack** variation:
- "weights" = coins[]
- "capacity" = amount
- Instead of maximizing value, we COUNT the number of ways.

-------------------------------------------------
❌ Brute Force (Recursion)
- Idea: At each step, choose whether to include the current coin or skip it.
- Time complexity: O(2^n * amount) [Exponential]
- Space complexity: O(amount) recursion depth
- Limitations: Very slow for larger inputs.

✅ Memoization (Top-Down DP)
- Idea: Store results of subproblems (n, amount) to avoid recomputation.
- Time complexity: O(n * amount)
- Space complexity: O(n * amount) for DP + recursion stack

✅ Tabulation (Bottom-Up 2D DP)
- Idea: Iteratively build dp[i][j] = number of ways using first i coins to make sum j.
- Time complexity: O(n * amount)
- Space complexity: O(n * amount)

✅ Space Optimized (Bottom-Up 1D DP)
- Idea: Since dp[i][j] only depends on current row and previous row, collapse to 1D.
- Time complexity: O(n * amount)
- Space complexity: O(amount)

💡 Key Pattern:
- This is a **counting version of unbounded knapsack**.
- Use "include current coin (stay at i)" + "exclude coin (move to i-1)".

Keywords:
- Unbounded Knapsack
- Coin Change
- Dynamic Programming
-------------------------------------------------
*/

/* ---------------------------------------------------
   1. Recursive (Exponential Time)
--------------------------------------------------- */
int coinChangeRec(vector<int>& coins, int n, int amount) {
    if (amount == 0) return 1;       // found valid way
    if (n == 0) return 0;            // no coins left

    if (coins[n - 1] <= amount) {
        // Option 1: take coin[n-1] (stay at same index, unbounded)
        // Option 2: skip it
        return coinChangeRec(coins, n, amount - coins[n - 1]) +
               coinChangeRec(coins, n - 1, amount);
    }
    return coinChangeRec(coins, n - 1, amount);
}

/* ---------------------------------------------------
   2. Memoization (Top-Down DP)
--------------------------------------------------- */
int coinChangeMemoHelper(vector<int>& coins, int n, int amount, vector<vector<int>>& dp) {
    if (amount == 0) return 1;
    if (n == 0) return 0;

    if (dp[n][amount] != -1) return dp[n][amount];

    if (coins[n - 1] <= amount) {
        dp[n][amount] = coinChangeMemoHelper(coins, n, amount - coins[n - 1], dp) +
                        coinChangeMemoHelper(coins, n - 1, amount, dp);
    } else {
        dp[n][amount] = coinChangeMemoHelper(coins, n - 1, amount, dp);
    }
    return dp[n][amount];
}

int coinChangeMemo(vector<int>& coins, int amount) {
    int n = coins.size();
    vector<vector<int>> dp(n + 1, vector<int>(amount + 1, -1));
    return coinChangeMemoHelper(coins, n, amount, dp);
}

/* ---------------------------------------------------
   3. Tabulation (Bottom-Up 2D DP)
--------------------------------------------------- */
int coinChangeTabulation(vector<int>& coins, int amount) {
    int n = coins.size();
    vector<vector<int>> dp(n + 1, vector<int>(amount + 1, 0));

    for (int i = 0; i <= n; i++) dp[i][0] = 1; // one way to form 0

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= amount; j++) {
            if (coins[i - 1] <= j) {
                dp[i][j] = dp[i - 1][j] + dp[i][j - coins[i - 1]];
            } else {
                dp[i][j] = dp[i - 1][j];
            }
        }
    }
    return dp[n][amount];
}

/* ---------------------------------------------------
   4. Space Optimized (Bottom-Up 1D DP)
--------------------------------------------------- */
int coinChangeOptimized(vector<int>& coins, int amount) {
    int n = coins.size();
    vector<int> dp(amount + 1, 0);
    dp[0] = 1;

    for (int i = 0; i < n; i++) {
        for (int j = coins[i]; j <= amount; j++) {
            dp[j] += dp[j - coins[i]];
        }
    }
    return dp[amount];
}

/* ---------------------------------------------------
   Main Function
--------------------------------------------------- */
int main() {
    int n, amount;
    cin >> n >> amount;
    vector<int> coins(n);
    for (int i = 0; i < n; i++) cin >> coins[i];

    cout << "Recursive: " << coinChangeRec(coins, n, amount) << "\n";
    cout << "Memoization: " << coinChangeMemo(coins, amount) << "\n";
    cout << "Tabulation: " << coinChangeTabulation(coins, amount) << "\n";
    cout << "Optimized: " << coinChangeOptimized(coins, amount) << "\n";

    return 0;
}
