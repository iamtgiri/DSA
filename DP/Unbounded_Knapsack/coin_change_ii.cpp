#include <iostream>
#include <vector>
#include <climits>
using namespace std;

/*
File: coin_change_ii.cpp
Date: 2025-09-12 10:08

Problem: Coin Change II
Link: URL

Problem Statement:
------------------
You are given:
- An array coins[] representing distinct coin denominations.
- An integer amount (target sum).

Task:
Find the minimum number of coins required to make up the amount.
If it is not possible, return -1.
- Each coin can be used unlimited times.
- Order does not matter.

Examples:
---------
Input:
coins = [1, 2, 5], amount = 11
Output: 3
Explanation: 5 + 5 + 1 = 3 coins

Input:
coins = [2], amount = 3
Output: -1 (cannot make 3 with only coin 2)

This is an **Unbounded Knapsack** variation:
- "weights" = coins[]
- "capacity" = amount
- Instead of counting ways, we minimize the number of coins.

-------------------------------------------------
❌ Brute Force (Recursion)
- Idea: At each step, either take the current coin or skip it.
- Time complexity: O(2^n * amount) [Exponential]
- Space complexity: O(amount) recursion depth
- Limitations: Extremely slow for larger amounts.

✅ Memoization (Top-Down DP)
- Idea: Cache results for (n, amount) states to avoid recomputation.
- Time complexity: O(n * amount)
- Space complexity: O(n * amount) + recursion stack

✅ Tabulation (Bottom-Up 2D DP)
- Idea: Iteratively fill dp[i][j] = min coins using first i coins to form sum j.
- Time complexity: O(n * amount)
- Space complexity: O(n * amount)

✅ Space Optimized (Bottom-Up 1D DP)
- Idea: Reduce 2D table to 1D since only current row matters.
- Time complexity: O(n * amount)
- Space complexity: O(amount)

💡 Key Pattern:
- This is the **minimization version of unbounded knapsack**.
- Transition: dp[j] = min(dp[j], 1 + dp[j - coin])

Keywords:
- Coin Change
- Dynamic Programming
- Unbounded Knapsack
-------------------------------------------------
*/

/* ---------------------------------------------------
   1. Recursive (Exponential Time)
--------------------------------------------------- */
int coinChangeRec(vector<int>& coins, int n, int amount) {
    if (amount == 0) return 0;               // no coins needed
    if (n == 0) return INT_MAX - 1;          // impossible

    if (coins[n - 1] <= amount) {
        // Option 1: take coin[n-1] (stay at same index)
        // Option 2: skip coin[n-1]
        return min(1 + coinChangeRec(coins, n, amount - coins[n - 1]),
                   coinChangeRec(coins, n - 1, amount));
    }
    return coinChangeRec(coins, n - 1, amount);
}

/* ---------------------------------------------------
   2. Memoization (Top-Down DP)
--------------------------------------------------- */
int coinChangeMemoHelper(vector<int>& coins, int n, int amount, vector<vector<int>>& dp) {
    if (amount == 0) return 0;
    if (n == 0) return INT_MAX - 1;

    if (dp[n][amount] != -1) return dp[n][amount];

    if (coins[n - 1] <= amount) {
        dp[n][amount] = min(1 + coinChangeMemoHelper(coins, n, amount - coins[n - 1], dp),
                            coinChangeMemoHelper(coins, n - 1, amount, dp));
    } else {
        dp[n][amount] = coinChangeMemoHelper(coins, n - 1, amount, dp);
    }
    return dp[n][amount];
}

int coinChangeMemo(vector<int>& coins, int amount) {
    int n = coins.size();
    vector<vector<int>> dp(n + 1, vector<int>(amount + 1, -1));
    int result = coinChangeMemoHelper(coins, n, amount, dp);
    return (result >= INT_MAX - 1 ? -1 : result);
}

/* ---------------------------------------------------
   3. Tabulation (Bottom-Up 2D DP)
--------------------------------------------------- */
int coinChangeTabulation(vector<int>& coins, int amount) {
    int n = coins.size();
    vector<vector<int>> dp(n + 1, vector<int>(amount + 1, INT_MAX - 1));

    for (int i = 0; i <= n; i++) dp[i][0] = 0; // 0 coins needed for amount 0

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= amount; j++) {
            if (coins[i - 1] <= j) {
                dp[i][j] = min(dp[i - 1][j], 1 + dp[i][j - coins[i - 1]]);
            } else {
                dp[i][j] = dp[i - 1][j];
            }
        }
    }
    return (dp[n][amount] >= INT_MAX - 1 ? -1 : dp[n][amount]);
}

/* ---------------------------------------------------
   4. Space Optimized (Bottom-Up 1D DP)
--------------------------------------------------- */
int coinChangeOptimized(vector<int>& coins, int amount) {
    vector<int> dp(amount + 1, INT_MAX - 1);
    dp[0] = 0;

    for (int coin : coins) {
        for (int j = coin; j <= amount; j++) {
            dp[j] = min(dp[j], 1 + dp[j - coin]);
        }
    }
    return (dp[amount] >= INT_MAX - 1 ? -1 : dp[amount]);
}

/* ---------------------------------------------------
   Main Function
--------------------------------------------------- */
int safeResult(int res) {
    return (res >= INT_MAX - 1 ? -1 : res);
}

int main() {
    int n, amount;
    cin >> n >> amount;
    vector<int> coins(n);
    for (int i = 0; i < n; i++) cin >> coins[i];

    cout << "Recursive: "   << safeResult(coinChangeRec(coins, n, amount)) << "\n";
    cout << "Memoization: " << coinChangeMemo(coins, amount) << "\n";
    cout << "Tabulation: "  << coinChangeTabulation(coins, amount) << "\n";
    cout << "Optimized: "   << coinChangeOptimized(coins, amount) << "\n";

    return 0;
}
