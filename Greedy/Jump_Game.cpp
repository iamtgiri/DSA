/*
File: Jump_Game.cpp
Date: 2025-09-22 10:41

Problem: Jump Game
Link: https://leetcode.com/problems/jump-game/
Problem Statement: Given an array of non-negative integers `nums`, you are initially positioned at the first index. Each element in the array represents your maximum jump length at that position. Determine if you can reach the last index.

-------------------------------------------------
❌ Brute Force
- Idea: A brute-force solution would involve a recursive backtracking approach. Starting from the first index, we would explore all possible jump paths. For each position, we recursively try every possible jump length (from 1 up to `nums[i]`) until we either reach the end or determine a path is a dead end. This can be optimized with memoization to solve a related problem, but it's not the most efficient.
- Time complexity: O(N^N) in the worst case without memoization, as each position could branch into multiple paths. With memoization, it becomes O(N^2).
- Space complexity: O(N) for the recursion stack or memoization table.
- Limitations: Highly inefficient due to its exponential time complexity.

✅ Optimized Approach
- Idea: The most efficient approach is a **greedy algorithm**. The key insight is that we don't need to consider all possible paths. We just need to track the furthest we can possibly reach from our current position. If at any point our current position `i` is beyond this furthest reachable point, it means we can't get to the current position, and thus we can't reach the end.
- Approach: A greedy, single-pass algorithm.
- Algorithm:
  1. Initialize a variable, `max_reach`, to 0. This variable will track the maximum index we can reach from all positions traversed so far.
  2. Iterate through the array from the start index `i` up to the second-to-last index.
  3. At each index `i`, check if `i` is greater than `max_reach`. If it is, it means we have reached a position that is a dead end, as we couldn't even get to it from any previous point. In this case, it's impossible to reach the end, so return `false`.
  4. Update `max_reach` to the maximum of its current value and the furthest we can reach from the current position (`i + nums[i]`).
  5. If `max_reach` ever becomes greater than or equal to the last index (`n - 1`), it means we can definitely reach the end, so return `true`.
  6. If the loop completes without `max_reach` reaching the end, it implies we can't get there. However, a small edge case exists where the loop finishes, and the last position hasn't been reached. The final check after the loop handles this.

- Time complexity: O(N), as we iterate through the array once.
- Space complexity: O(1), as we only use a few integer variables.

💡 Key Pattern:
- **Greedy Algorithms**: This problem is a perfect example where a locally optimal choice (maximizing the current reach) leads to a globally optimal solution. The "greedy choice property" holds because advancing to the furthest possible position at each step is always the best move.

ℹ️ Keywords:
- Greedy Algorithm, Jump Game, Array, Reachability, Single Pass

🗒️ Notes
- The logic is slightly counter-intuitive. We are not literally "jumping" through the array; instead, we are simulating a traversal while keeping track of the best possible outcome at each step.
-------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    /**
     * @brief Determines if it's possible to reach the last index of the array.
     * @param nums A vector of non-negative integers representing jump lengths.
     * @return true if the last index can be reached, false otherwise.
     */
    bool canJump(vector<int> &nums)
    {
        int max_reach = 0;
        int n = nums.size();

        // Iterate through each index of the array.
        for (int i = 0; i < n; ++i)
        {
            // If the current index is beyond the maximum reachable point, it's a dead end.
            if (i > max_reach)
            {
                return false;
            }
            // Update the maximum reachable index from the current position.
            max_reach = max(max_reach, i + nums[i]);

            // If we have already reached or surpassed the last index, we're done.
            if (max_reach >= n - 1)
            {
                return true;
            }
        }

        // This line is technically redundant because the loop will either return true or false
        // but it's a good practice for finality. It will be reached only if n=1 and i=0.
        return true;
    }
};

int main()
{
    Solution sol;

    // Example 1
    vector<int> nums1 = {2, 3, 1, 1, 4};
    cout << "Example 1: " << (sol.canJump(nums1) ? "true" : "false") << endl; // Expected: true

    // Example 2
    vector<int> nums2 = {3, 2, 1, 0, 4};
    cout << "Example 2: " << (sol.canJump(nums2) ? "true" : "false") << endl; // Expected: false

    return 0;
}