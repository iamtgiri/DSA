#include <iostream>
#include <vector>
using namespace std;

/*
Coin Change I Problem
---------------------
You are given:
- An array coins[] representing distinct coin denominations.
- An integer amount (target sum).

Task:
Count the number of combinations to make up that amount using the coins.
- You may use each coin unlimited times.
- The order of coins does NOT matter (1+3 == 3+1).

Example:
---------
coins = [1, 2, 3], amount = 4

Ways:
- 1+1+1+1
- 1+1+2
- 2+2
- 1+3
Answer = 4

This is an Unbounded Knapsack variation:
- "weights" = coins[]
- "capacity" = amount
- Instead of maximizing value, we COUNT the number of ways.
*/

/* ---------------------------------------------------
   1. Recursive (Exponential Time)
--------------------------------------------------- */
int coinChangeRec(vector<int>& coins, int n, int amount) {
    if (amount == 0) return 1;              // found valid way
    if (n == 0) return 0;                   // no coins left
    if (n == 1) return (amount % coins[0] == 0); // only one type left

    if (coins[n - 1] <= amount) {
        // Option 1: take coin[n-1] (stay at same index, unbounded)
        // Option 2: skip it
        return coinChangeRec(coins, n, amount - coins[n - 1]) +
               coinChangeRec(coins, n - 1, amount);
    } else {
        return coinChangeRec(coins, n - 1, amount);
    }
}

/* ---------------------------------------------------
   2. Memoization (Top-Down DP)
--------------------------------------------------- */
int coinChangeMemoHelper(vector<int>& coins, int n, int amount, vector<vector<int>>& dp) {
    if (amount == 0) return 1;
    if (n == 0) return 0;
    if (n == 1) return (amount % coins[0] == 0);

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

    cout << "Recursive: " << coinChangeRec(coins, n, amount) << endl;
    cout << "Memoization: " << coinChangeMemo(coins, amount) << endl;
    cout << "Tabulation: " << coinChangeTabulation(coins, amount) << endl;
    cout << "Optimized: " << coinChangeOptimized(coins, amount) << endl;

    return 0;
}
