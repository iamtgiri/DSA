/*
Problem Statement:
------------------
Given an array of positive integers `arr` and an integer `sum`,
count the number of subsets of `arr` whose elements add up exactly to `sum`.

This is a variation of the "Subset Sum" problem, solved using
Dynamic Programming (DP).

Approach:
---------
We use a DP table `dp[i][j]` where:
- i = number of elements considered (from 0..n)
- j = target sum (from 0..sum)

dp[i][j] = number of subsets of first i elements that form sum j.

Recurrence:
-----------
1. Base cases:
   - dp[0][0] = 1  (empty set forms sum 0)
   - dp[0][j] = 0  (no subsets possible for j>0 with 0 elements)
   - dp[i][0] = 1  (empty subset always forms sum 0)

2. Transition:
   If we consider the i-th element (arr[i-1]):
   - If arr[i-1] <= j:
       dp[i][j] = dp[i-1][j] + dp[i-1][j - arr[i-1]]
       (exclude element + include element)
   - Else:
       dp[i][j] = dp[i-1][j]  (can't include element)

Time Complexity:  O(n * sum)
Space Complexity: O(n * sum)   (can be optimized to O(sum))
*/

#include <iostream>
#include <vector>

std::vector<std::vector<int>> dp(102, std::vector<int>(102, 0));

int countSubset(const std::vector<int> &arr, int sum)
{
    const int n = arr.size();

    // Base cases
    for (int i = 0; i <= n; ++i)
        dp[i][0] = 1; // sum=0 is always possible with empty set

    // Build DP table
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

int main()
{
    int n, sum;
    std::cout << "Enter number of elements and target sum:\n";
    std::cin >> n >> sum;

    std::vector<int> arr(n);
    std::cout << "Enter elements of the array:\n";
    for (int i = 0; i < n; ++i)
        std::cin >> arr[i];

    std::cout << "Number of subsets with sum " << sum << " = "
              << countSubset(arr, sum) << std::endl;

    return 0;
}
