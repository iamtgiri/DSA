#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

// ---------------------------
// Helper Functions
// ---------------------------

// 1. Recursive 0/1 Knapsack
int knapsack_recursive(const vector<int>& values, const vector<int>& weights, int W, int n)
{
    if (W == 0 || n == 0)
        return 0;

    if (weights[n - 1] <= W)
        return max(values[n - 1] + knapsack_recursive(values, weights, W - weights[n - 1], n - 1),
                   knapsack_recursive(values, weights, W, n - 1));
    
    return knapsack_recursive(values, weights, W, n - 1);
}

// 2. Memoization 0/1 Knapsack
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

// 3. Top-Down (Dynamic Programming) 0/1 Knapsack
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

    cout << "Maximum value (Recursive): " << knapsack_recursive(values, weights, W, n) << endl;

    // Reset dp array before using memoization
    dp.assign(102, vector<int>(102, -1));
    cout << "Maximum value (Memoization): " << knapsack_memo(values, weights, W, n) << endl;

    // Reset DP table for top-down approach
    t.assign(102, vector<int>(102, 0));
    cout << "Maximum value (DP): " << knapsack_dp(values, weights, W, n) << endl;

    return 0;
}
