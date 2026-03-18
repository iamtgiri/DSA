/*
File: circular_house_robbery.cpp
Date: 2026-03-19

Problem: Circular House Robbery (LeetCode 213 - House Robber II)
Link: https://leetcode.com/problems/house-robber-ii/

-------------------------------------------------
Brute Force
- Idea: Try all subsets such that no two adjacent houses are robbed.
- Approach: Recursive pick / not-pick.
- Time complexity: O(2^n)
- Space complexity: O(n) recursion stack
- Limitation: Exponential → infeasible for n up to 100+

-------------------------------------------------
Optimized Approach (Dynamic Programming)

- Core Insight:
  Circular dependency → first and last house cannot both be robbed.

- Strategy:
  Break into 2 linear problems:
    1. Rob houses [0 ... n-2]
    2. Rob houses [1 ... n-1]
  Take max of both.

- Linear Subproblem:
  Classic House Robber I:
    dp[i] = max(
        nums[i] + dp[i-2],
        dp[i-1]
    )

- Space Optimization:
  Use two variables instead of DP array.

- Time complexity: O(n)
- Space complexity: O(1)

-------------------------------------------------
💡 Key Pattern:
- DP on linear array
- "Circular → split into two linear cases"
- State compression (prev1, prev2)

ℹ️ Keywords:
- Dynamic Programming
- House Robber
- Circular Array
- State Compression
- Range DP

🗒️ Notes
- Very common trick: circular problems → break into two linear cases
- Same pattern appears in:
    - Maximum sum in circular arrays
    - Circular DP problems
- Mistake-prone area:
    - Forgetting edge case n == 1
    - Incorrect index ranges
-------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int rob(vector<int> &nums)
    {
        int n = nums.size();

        // Edge cases
        if (n == 0)
            return 0;
        if (n == 1)
            return nums[0];

        // Case 1: Exclude last house
        int case1 = robLinear(nums, 0, n - 2);

        // Case 2: Exclude first house
        int case2 = robLinear(nums, 1, n - 1);

        return max(case1, case2);
    }

private:
    // Standard House Robber I on subarray [start, end]
    int robLinear(vector<int> &nums, int start, int end)
    {
        int prev2 = 0; // dp[i-1]
        int prev1 = 0; // dp[i-2]

        for (int i = start; i <= end; ++i)
        {
            int pick = nums[i] + prev1;
            int notPick = prev2;

            int curr = max(pick, notPick);

            prev1 = prev2;
            prev2 = curr;
        }

        return prev2;
    }
};

int main()
{
    Solution sol;

    vector<int> nums1 = {2, 3, 2};
    vector<int> nums2 = {1, 2, 3, 1};
    vector<int> nums3 = {1, 2, 1, 1};

    cout << sol.rob(nums1) << endl; // 3
    cout << sol.rob(nums2) << endl; // 4
    cout << sol.rob(nums3) << endl; // 3

    return 0;
}