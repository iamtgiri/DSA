/*
Problem Statement:
------------------
Given an array of positive integers `arr` and an integer `sum`,
count the number of subsets of `arr` whose elements add up exactly to `sum`.

Approaches:
-----------
1. 2D DP (Tabulation):
   - dp[i][j] = number of subsets from first i elements with sum j.
   - Time:  O(n * sum)
   - Space: O(n * sum)

2. 1D DP (Space Optimized):
   - dp[j] = number of subsets with sum j using processed elements so far.
   - Update dp backwards for each element.
   - Time:  O(n * sum)
   - Space: O(sum)
*/

#include <iostream>
#include <vector>

// ---------------------------
// 1. 2D DP Approach
// ---------------------------
std::vector<std::vector<int>> dp(102, std::vector<int>(102, 0));

int countSubset(const std::vector<int> &arr, int sum)
{
    const int n = arr.size();

    for (int i = 0; i <= n; ++i)
        dp[i][0] = 1; // sum=0 is always possible with empty set

    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= sum; ++j)
        {
            if (arr[i - 1] <= j)
                dp[i][j] = dp[i - 1][j] + dp[i - 1][j - arr[i - 1]];
            else
                dp[i][j] = dp[i - 1][j];
        }
    }
    return dp[n][sum];
}

// ---------------------------
// 2. 1D DP (Space Optimized)
// ---------------------------
int countSubset_optimized(const std::vector<int> &arr, int sum)
{
    std::vector<int> dp(sum + 1, 0);
    dp[0] = 1; // sum=0 possible by empty set

    for (int num : arr)
    {
        // Traverse backwards to avoid overwriting results
        for (int j = sum; j >= num; --j)
        {
            dp[j] += dp[j - num];
        }
    }
    return dp[sum];
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
    for (int i = 0; i < n; ++i)
        std::cin >> arr[i];

    std::cout << "\n--- Results ---\n";
    std::cout << "2D DP Approach:   " << countSubset(arr, sum) << std::endl;
    std::cout << "1D Optimized DP:  " << countSubset_optimized(arr, sum) << std::endl;

    return 0;
}
