/*
File: Jump_Game_2.cpp
Date: 2025-09-22 11:01

Problem: Jump Game II
Link: https://leetcode.com/problems/jump-game-ii/
Problem Statement: You are given a 0-indexed array of integers `nums`. You are initially positioned at index 0. Each element `nums[i]` represents the maximum length of a forward jump from index `i`. Return the minimum number of jumps to reach index `n - 1`. Test cases are generated such that the last index can always be reached.

-------------------------------------------------
❌ Brute Force
- Idea: A brute-force solution would use recursion with backtracking to explore all possible jump paths from the start. We would find the minimum jumps by trying every possible jump from the current position and recursively calling the function for the new position. This can be optimized with memoization (or dynamic programming) to avoid recomputing subproblems.
- Time complexity: O(N^N) in the worst case without memoization. With dynamic programming, it becomes O(N^2).
- Space complexity: O(N) for the recursion stack or DP table.
- Limitations: Highly inefficient due to its exponential time complexity.

✅ Optimized Approach
- Idea: The most efficient approach is a **greedy algorithm**. We can think of the problem in terms of "jumps." From the current position, we want to make a jump that gets us as far as possible. We don't need to consider every intermediate step; instead, we can process the array in levels, where each level represents a single jump.
- Approach: A greedy, single-pass algorithm. This is sometimes referred to as a **level-order traversal** or **breadth-first search (BFS)** approach on the array.
- Algorithm:
  1. Initialize `jumps` to 0, `current_jump_end` to 0, and `farthest_reach` to 0.
  2. Iterate through the array from `i = 0` to `n - 2` (since we don't need to make a jump from the last element).
  3. At each index `i`, update `farthest_reach` to the maximum of its current value and the furthest we can reach from `i` (i.e., `i + nums[i]`).
  4. When `i` reaches `current_jump_end`, it means we have explored all the positions we could reach with the previous jump. At this point, we need to make another jump.
  5. Increment `jumps` by 1 and update `current_jump_end` to the new `farthest_reach`.
  6. The loop naturally ends when we are at or past `n - 1`. The final `jumps` count will be the minimum.

- Time complexity: O(N) because we iterate through the array once.
- Space complexity: O(1) as we only use a few integer variables.

💡 Key Pattern:
- **Greedy Algorithms / Breadth-First Search**: The problem can be modeled as finding the shortest path in an unweighted graph, which is solvable by BFS. The greedy approach simulates a BFS level by level. Each "level" consists of all indices reachable by a single jump. This is why the algorithm is optimal and efficient.

ℹ️ Keywords:
- Greedy Algorithm, Jump Game, Array, BFS, Level-order Traversal

🗒️ Notes
- The "BFS" analogy helps clarify why the greedy choice works. Each jump is a step in the BFS, and the `farthest_reach` represents the boundary of the next level. We always advance to the end of the current level before making the next jump.
-------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    /**
     * @brief Finds the minimum number of jumps to reach the end of the array.
     * @param nums A vector of non-negative integers representing jump lengths.
     * @return The minimum number of jumps.
     */
    int jump(vector<int> &nums)
    {
        int n = nums.size();
        if (n <= 1)
        {
            return 0;
        }

        int jumps = 0;
        int current_jump_end = 0;
        int farthest_reach = 0;

        for (int i = 0; i < n - 1; ++i)
        {
            // Find the maximum reachable index from the current position.
            farthest_reach = max(farthest_reach, i + nums[i]);

            // If we've reached the end of our current jump's range.
            if (i == current_jump_end)
            {
                jumps++;
                // Set the new end of our jump to the farthest we could reach.
                current_jump_end = farthest_reach;
            }
        }

        return jumps;
    }
};

int main()
{
    Solution sol;

    // Example 1
    vector<int> nums1 = {2, 3, 1, 1, 4};
    cout << "Example 1: Min jumps = " << sol.jump(nums1) << endl; // Expected: 2

    // Example 2
    vector<int> nums2 = {2, 3, 0, 1, 4};
    cout << "Example 2: Min jumps = " << sol.jump(nums2) << endl; // Expected: 2

    // Example 3
    vector<int> nums3 = {1, 1, 1, 1};
    cout << "Example 3: Min jumps = " << sol.jump(nums3) << endl; // Expected: 3

    return 0;
}