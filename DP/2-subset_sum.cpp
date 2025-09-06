/*
Problem Statement:
------------------
Given an array of positive integers and a target value `sum`, 
determine whether there exists a subset of the array such that 
the sum of its elements is exactly equal to `sum`.

Example:
--------
Input:  arr = {3, 34, 4, 12, 5, 2}, sum = 9
Output: true
Explanation: Subset {4, 5} sums to 9.

Input:  arr = {3, 34, 4, 12, 5, 2}, sum = 30
Output: false
Explanation: No subset sums to 30.

Approaches:
-----------
1. Classic DP (2D table):
   - dp[i][j] = true if a subset of first i elements can form sum j.
   - Time:  O(n * sum)
   - Space: O(n * sum)

2. Space-Optimized DP (1D array):
   - dp[j] = true if some subset can form sum j.
   - Traverse backwards to avoid reusing the same element multiple times.
   - Time:  O(n * sum)
   - Space: O(sum)
*/

#include <iostream>
#include <vector>
#include <algorithm>

// 2D DP approach
bool subset_sum(const std::vector<int>& arr, int sum)
{
    int n = arr.size();
    std::vector<std::vector<bool>> dp(n + 1, std::vector<bool>(sum + 1, false));

    // Base case: sum 0 is always possible
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

// 1D Space-Optimized DP approach
bool subset_sum_optimized(const std::vector<int>& arr, int sum)
{
    int n = arr.size();
    std::vector<bool> dp(sum + 1, false);
    dp[0] = true; // sum 0 always possible

    for (int num : arr)
    {
        // Traverse backwards to prevent reusing same element
        for (int j = sum; j >= num; --j)
        {
            if (dp[j - num])
                dp[j] = true;
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
    for (int i = 0; i < n; i++)
        std::cin >> arr[i];

    // Run both approaches
    bool result1 = subset_sum(arr, sum);
    bool result2 = subset_sum_optimized(arr, sum);

    std::cout << "\n--- Results ---\n";
    std::cout << "2D DP Approach: ";
    if (result1)
        std::cout << "Subset with sum " << sum << " exists.\n";
    else
        std::cout << "No subset with sum " << sum << " exists.\n";

    std::cout << "1D Optimized DP Approach: ";
    if (result2)
        std::cout << "Subset with sum " << sum << " exists.\n";
    else
        std::cout << "No subset with sum " << sum << " exists.\n";

    return 0;
}
