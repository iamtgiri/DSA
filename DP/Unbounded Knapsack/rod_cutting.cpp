#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
Rod Cutting Problem
-------------------
You are given:
- A rod of length N.
- An array price[], where price[i] is the price of a rod piece of length i+1.

Task:
Cut the rod into pieces such that the total profit is maximized.
You can cut the rod into any number of pieces, and you may reuse the same length multiple times.

Example:
Input:
N = 4
price = [2, 5, 7, 8]

Possible cuts:
- Cut into 4 pieces of length 1 -> 2+2+2+2 = 8
- Cut into 2+2 -> 5+5 = 10
- Cut into 3+1 -> 7+2 = 9
- No cut (just 4) -> 8
Answer = 10

This is essentially the Unbounded Knapsack problem:
- "weights" = lengths = {1, 2, ..., N}
- "values" = prices[]
- "capacity" = N
Goal: maximize value without exceeding N
*/

/* ---------------------------------------------------
   1. Recursive (Exponential Time)
--------------------------------------------------- */
int rodCuttingRec(vector<int>& price, int n, int length) {
    if (n == 0 || length == 0) return 0;

    if (n <= length) {
        // Option 1: take this piece (unbounded, so stay at n)
        // Option 2: skip this piece (go to n-1)
        return max(price[n - 1] + rodCuttingRec(price, n, length - n),
                   rodCuttingRec(price, n - 1, length));
    } else {
        // cannot take this piece
        return rodCuttingRec(price, n - 1, length);
    }
}

/* ---------------------------------------------------
   2. Memoization (Top-Down DP)
--------------------------------------------------- */
int rodCuttingMemoHelper(vector<int>& price, int n, int length, vector<vector<int>>& dp) {
    if (n == 0 || length == 0) return 0;
    if (dp[n][length] != -1) return dp[n][length];

    if (n <= length) {
        dp[n][length] = max(price[n - 1] + rodCuttingMemoHelper(price, n, length - n, dp),
                            rodCuttingMemoHelper(price, n - 1, length, dp));
    } else {
        dp[n][length] = rodCuttingMemoHelper(price, n - 1, length, dp);
    }
    return dp[n][length];
}

int rodCuttingMemo(vector<int>& price, int N) {
    vector<vector<int>> dp(N + 1, vector<int>(N + 1, -1));
    return rodCuttingMemoHelper(price, N, N, dp);
}

/* ---------------------------------------------------
   3. Tabulation (Bottom-Up 2D DP)
--------------------------------------------------- */
int rodCuttingTabulation(vector<int>& price, int N) {
    vector<vector<int>> dp(N + 1, vector<int>(N + 1, 0));

    for (int n = 1; n <= N; n++) {
        for (int length = 1; length <= N; length++) {
            if (n <= length) {
                dp[n][length] = max(dp[n - 1][length],
                                    price[n - 1] + dp[n][length - n]);
            } else {
                dp[n][length] = dp[n - 1][length];
            }
        }
    }

    return dp[N][N];
}

/* ---------------------------------------------------
   4. Space Optimized (Bottom-Up 1D DP)
--------------------------------------------------- */
int rodCuttingOptimized(vector<int>& price, int N) {
    vector<int> dp(N + 1, 0);

    for (int n = 1; n <= N; n++) {
        for (int length = 1; length <= N; length++) {
            if (n <= length) {
                dp[length] = max(dp[length], price[n - 1] + dp[length - n]);
            }
        }
    }

    return dp[N];
}

/* ---------------------------------------------------
   Main Function
--------------------------------------------------- */
int main() {
    int N;
    cin >> N;
    vector<int> price(N);
    for (int i = 0; i < N; i++) cin >> price[i];

    cout << "Recursive: " << rodCuttingRec(price, N, N) << endl;
    cout << "Memoization: " << rodCuttingMemo(price, N) << endl;
    cout << "Tabulation: " << rodCuttingTabulation(price, N) << endl;
    cout << "Optimized: " << rodCuttingOptimized(price, N) << endl;

    return 0;
}
