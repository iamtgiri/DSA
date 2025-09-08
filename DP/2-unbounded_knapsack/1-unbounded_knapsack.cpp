#include <iostream>
#include <vector>
using namespace std;


/*
                  Unbounded Knapsack Problem
                 ----------------------------
     Given weights[] and values[] of n items, and a capacity W,
  find the maximum value you can achieve by picking items such that:
        - You can take unlimited copies of each item.
        - The total weight does not exceed W.
*/


int unbd_knapsack(const vector<int> &weights, const vector<int> &values, int W)
{
    int n = weights.size();
    vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));

    // dp[i][j] = maximum value using first i items with capacity j
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= W; ++j)
        {
            if (weights[i - 1] <= j)
            {
                // Either skip the item or take it (again, since unlimited)
                dp[i][j] = max(dp[i - 1][j], values[i - 1] + dp[i][j - weights[i - 1]]);
            }
            else
            {
                dp[i][j] = dp[i - 1][j];
            }
        }
    }
    return dp[n][W];
}




int main()
{
    int n, W;
    cout << "Enter number of elements and capacity:";
    cin >> n >> W;

    vector<int> weights(n), values(n);

    cout << "Enter weights:";
    for (int i = 0; i < n; i++)
        cin >> weights[i];

    cout << "Enter values:";
    for (int i = 0; i < n; i++)
        cin >> values[i];

    cout << unbd_knapsack(weights, values, W) << endl;
    return 0;
}
