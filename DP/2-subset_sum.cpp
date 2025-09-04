#include <iostream>
#include <vector>
#include<algorithm>

// ---------------------------
// Helper Function: Subset Sum (Top-Down DP)
// Returns true if there exists a subset of 'arr' with sum equal to 'sum'
bool subset_sum(const std::vector<int>& arr, int sum)
{
    int n = arr.size();
    // dp[i][j] = true if sum 'j' can be formed using first 'i' elements
    std::vector<std::vector<bool>> dp(n + 1, std::vector<bool>(sum + 1, false));

    // Initialize: sum 0 is always possible (empty subset)
    for (int i = 0; i <= n; i++)
        dp[i][0] = true;

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= sum; j++)
        {
            if (arr[i - 1] <= j)
                dp[i][j] = dp[i - 1][j] || dp[i - 1][j - arr[i - 1]];
            else
                dp[i][j] = dp[i - 1][j];
        }
    }

    return dp[n][sum];
}

// ---------------------------
// Main Function
// ---------------------------
int main()
{
    int n, sum;
    std::cout << "Enter number of elements and target sum:\n";
    std::cin >> n >> sum;

    std::vector<int> arr(n);
    std::cout << "Enter elements of the array:\n";
    for (int i = 0; i < n; i++)
        std::cin >> arr[i];

    if (subset_sum(arr, sum))
        std::cout << "Subset with sum " << sum << " exists.\n";
    else
        std::cout << "No subset with sum " << sum << " exists.\n";

    return 0;
}
