/*
Problem Statement:
------------------
Given weights[] and values[] of n items, and a maximum capacity W, 
find the maximum total value that can be put into a knapsack of capacity W.

Approaches:
-----------
1. Recursive Solution:
   - Try including/excluding each item.
   - Time:  O(2^n), Space: O(n) (stack)

2. Memoization (Top-Down DP):
   - Store overlapping subproblem results.
   - Time:  O(n*W), Space: O(n*W)

3. Tabulation (Bottom-Up DP):
   - Iteratively build dp[i][w].
   - Time:  O(n*W), Space: O(n*W)

4. Space-Optimized DP:
   - Use 1D DP array updated backwards.
   - Time:  O(n*W), Space: O(W)
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

// ---------------------------
// 1. Recursive 0/1 Knapsack
// ---------------------------
int knapsack_recursive(const vector<int>& values, const vector<int>& weights, int W, int n)
{
    if (W == 0 || n == 0)
        return 0;

    if (weights[n - 1] <= W)
        return max(values[n - 1] + knapsack_recursive(values, weights, W - weights[n - 1], n - 1),
                   knapsack_recursive(values, weights, W, n - 1));
    
    return knapsack_recursive(values, weights, W, n - 1);
}

// ---------------------------
// 2. Memoization (Top-Down DP)
// ---------------------------
vector<vector<int>> dp(102, vector<int>(102, -1));

int knapsack_memo(const vector<int>& values, const vector<int>& weights, int W, int n)
{
    if (W == 0 || n == 0)
        return 0;

    if (dp[W][n] != -1)
        return dp[W][n];

    if (weights[n - 1] <= W)
        return dp[W][n] = max(values[n - 1] + knapsack_memo(values, weights, W - weights[n - 1], n - 1),
                               knapsack_memo(values, weights, W, n - 1));

    return dp[W][n] = knapsack_memo(values, weights, W, n - 1);
}

// ---------------------------
// 3. Tabulation (Bottom-Up DP)
// ---------------------------
vector<vector<int>> t(102, vector<int>(102, 0));

int knapsack_dp(const vector<int>& values, const vector<int>& weights, int W, int n)
{
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= W; j++)
        {
            if (weights[i - 1] <= j)
                t[i][j] = max(values[i - 1] + t[i - 1][j - weights[i - 1]], t[i - 1][j]);
            else
                t[i][j] = t[i - 1][j];
        }
    }
    return t[n][W];
}

// ---------------------------
// 4. Space-Optimized 1D DP
// ---------------------------
int knapsack_optimized(const vector<int>& values, const vector<int>& weights, int W, int n)
{
    vector<int> dp(W + 1, 0);

    for (int i = 0; i < n; i++)
    {
        for (int j = W; j >= weights[i]; --j)
        {
            dp[j] = max(dp[j], values[i] + dp[j - weights[i]]);
        }
    }
    return dp[W];
}

// ---------------------------
// Main Function
// ---------------------------
int main()
{
    int n, W;
    cout << "Enter number of items and maximum weight:" << endl;
    cin >> n >> W;

    vector<int> values(n), weights(n);
    cout << "Enter values of items:" << endl;
    for (int i = 0; i < n; i++)
        cin >> values[i];

    cout << "Enter weights of items:" << endl;
    for (int i = 0; i < n; i++)
        cin >> weights[i];

    cout << "\n--- Results ---\n";
    cout << "Recursive:       " << knapsack_recursive(values, weights, W, n) << endl;

    dp.assign(102, vector<int>(102, -1));
    cout << "Memoization:     " << knapsack_memo(values, weights, W, n) << endl;

    t.assign(102, vector<int>(102, 0));
    cout << "Tabulation DP:   " << knapsack_dp(values, weights, W, n) << endl;

    cout << "Optimized 1D DP: " << knapsack_optimized(values, weights, W, n) << endl;

    return 0;
}
