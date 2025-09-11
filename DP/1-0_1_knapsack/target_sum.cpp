#include <iostream>
#include <vector>
using namespace std;

/*
Target Sum Problem
------------------
You are given an array of non-negative integers `nums` and an integer `target`.

You have to assign either '+' or '-' before each integer in `nums`
and evaluate the resulting expression. Your task is to count the 
number of different ways to assign signs such that the final sum equals `target`.

Key Insight:
------------
- Assigning '+' to a number means putting it in subset S1,
- Assigning '-' to a number means putting it in subset S2.

So:
    S1 - S2 = target
    S1 + S2 = totalSum
 => 2*S1 = target + totalSum
 => S1 = (target + totalSum)/2

Thus, the problem reduces to: 
Count subsets with sum = (target + totalSum)/2.

Constraints:
------------
- 1 <= nums.length <= 20
- 0 <= nums[i] <= 1000
- The final sum will always fit within a 32-bit integer.

Example 1:
----------
Input:
5 3
1 1 1 1 1

Output:
5

Explanation:
There are 5 ways to assign signs to reach target 3:
-1+1+1+1+1 = 3
+1-1+1+1+1 = 3
+1+1-1+1+1 = 3
+1+1+1-1+1 = 3
+1+1+1+1-1 = 3

Example 2:
----------
Input:
4 1
1 2 3 4

Output:
2
*/

/*
Function: findTargetSumWays
---------------------------
Counts the number of ways to assign '+' or '-' signs 
to elements of nums such that the total sum equals target.
*/
int findTargetSumWays(vector<int>& nums, int target) {
    int n = nums.size();
    int totalSum = 0;
    for (int x : nums) totalSum += x;

    // If (target + totalSum) is odd or |target| > totalSum, no solution
    if ((target + totalSum) % 2 != 0 || abs(target) > totalSum) return 0;

    int subsetSum = (target + totalSum) / 2;

    // DP table: dp[i][j] = number of ways to form sum j using first i elements
    vector<vector<int>> dp(n + 1, vector<int>(subsetSum + 1, 0));

    // Base case: sum 0 can always be formed with empty subset
    for (int i = 0; i <= n; ++i) dp[i][0] = 1;

    // Fill DP table
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= subsetSum; ++j) {
            if (nums[i - 1] <= j) {
                dp[i][j] = dp[i - 1][j] + dp[i - 1][j - nums[i - 1]];
            } else {
                dp[i][j] = dp[i - 1][j];
            }
        }
    }

    return dp[n][subsetSum];
}

/*
Main function:
--------------
Input format:
n target
arr[0] arr[1] ... arr[n-1]

Example:
5 3
1 1 1 1 1

Output:
5
*/
int main() {
    int n, target;
    cin >> n >> target;

    vector<int> nums(n);
    for (int i = 0; i < n; ++i) cin >> nums[i];

    cout << findTargetSumWays(nums, target) << endl;

    return 0;
}
