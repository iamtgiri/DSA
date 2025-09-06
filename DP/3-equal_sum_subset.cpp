/*
Problem Statement:
------------------
Given an array of positive integers, determine whether it can be partitioned 
into two subsets such that the sum of elements in both subsets is equal.

Approaches:
-----------
1. Classic DP (2D table):
   - Use dp[i][j] where dp[i][j] = true if a subset of first i elements
     can sum to j.
   - Time:  O(n * (sum/2))
   - Space: O(n * (sum/2))

2. Space-Optimized DP (1D array):
   - Use dp[j] where dp[j] = true if some subset sums to j.
   - Update dp backwards for each element.
   - Time:  O(n * (sum/2))
   - Space: O(sum/2)
*/

#include <iostream>
#include <vector>
#include <algorithm>

// 2D DP approach
bool equal_sum(const std::vector<int>& arr)
{
    int n = arr.size();
    int sum = 0;
    for (int x : arr)
        sum += x;

    if (sum % 2 != 0) return false; // Odd sum → impossible
    int target = sum / 2;

    // dp[i][j] = true if sum j is possible with first i elements
    std::vector<std::vector<bool>> dp(n + 1, std::vector<bool>(target + 1, false));

    // Base case: sum 0 is always possible
    for (int i = 0; i <= n; ++i)
        dp[i][0] = true;

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

// Space-optimized 1D DP approach
bool equal_sum_optimized(const std::vector<int>& arr)
{
    int n = arr.size();
    int sum = 0;
    for (int x : arr)
        sum += x;

    if (sum % 2 != 0) return false; // Odd sum → impossible
    int target = sum / 2;

    std::vector<bool> dp(target + 1, false);
    dp[0] = true; // sum 0 is always possible

    for (int num : arr)
    {
        // Traverse backwards to avoid reusing the same element
        for (int j = target; j >= num; --j)
        {
            if (dp[j - num])
                dp[j] = true;
        }
    }
    return dp[target];
}

int main()
{
    int n;
    std::cout << "Enter number of elements:\n";
    std::cin >> n;

    std::vector<int> arr(n);
    std::cout << "Enter elements of the array:\n";
    for (int i = 0; i < n; i++)
        std::cin >> arr[i];

    // Run both approaches
    bool result1 = equal_sum(arr);
    bool result2 = equal_sum_optimized(arr);

    std::cout << "\n--- Results ---\n";
    std::cout << "2D DP Approach: ";
    if (result1)
        std::cout << "Array CAN be partitioned.\n";
    else
        std::cout << "Array CANNOT be partitioned.\n";

    std::cout << "1D Optimized DP Approach: ";
    if (result2)
        std::cout << "Array CAN be partitioned.\n";
    else
        std::cout << "Array CANNOT be partitioned.\n";

    return 0;
}
