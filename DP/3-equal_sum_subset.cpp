#include <iostream>
#include <vector>
#include <algorithm>

// Returns true if the array can be partitioned into two subsets with equal sum
bool equal_sum(const std::vector<int>& arr)
{
    int n = arr.size();
    int sum = 0;
    for (int x : arr)
        sum += x;

    // If total sum is odd, can't split into two equal subsets
    if (sum % 2 != 0)
        return false;

    int target = sum / 2;

    // dp[i][j] = true if sum 'j' can be formed using first 'i' elements
    std::vector<std::vector<bool>> dp(n + 1, std::vector<bool>(target + 1, false));

    // Base case: sum 0 is always possible
    for (int i = 0; i <= n; ++i)
        dp[i][0] = true;

    // Fill the DP table
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= target; ++j)
        {
            if (arr[i - 1] <= j)
                dp[i][j] = dp[i - 1][j] || dp[i - 1][j - arr[i - 1]];
            else
                dp[i][j] = dp[i - 1][j];
        }
    }

    return dp[n][target];
}

// Example usage
int main()
{
    int n;
    std::cout << "Enter number of elements and target sum:\n";
    std::cin >> n;

    std::vector<int> arr(n);
    std::cout << "Enter elements of the array:\n";
    for (int i = 0; i < n; i++)
        std::cin >> arr[i];
    if (equal_sum(arr))
        std::cout << "Array can be partitioned into two subsets with equal sum.\n";
    else
        std::cout << "Array cannot be partitioned into two subsets with equal sum.\n";

    return 0;
}
