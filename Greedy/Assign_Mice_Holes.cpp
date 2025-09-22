/*
File: Assign_Mice_Holes.cpp
Date: 2025-09-22 16:26

Problem: Assign Mice Holes
Link: https://www.geeksforgeeks.org/problems/assign-mice-holes3053/1

Problem Statement:
You are given two arrays mices[] and holes[] of the same size. The array mices[]
represents the positions of the mice on a straight line, while the array holes[]
represents the positions of the holes on the same line. Each hole can accommodate
exactly one mouse. A mouse can either stay in its current position, move one step
to the right, or move one step to the left, and each move takes one minute. The
task is to assign each mouse to a distinct hole in such a way that the time taken
by the last mouse to reach its hole is minimized.

Examples:
Input: mices[] = [4, -4, 2], holes[] = [4, 0, 5]
Output: 4
Explanation: To minimize the maximum time, we should assign mouse at -4 to hole at
0 (time = 4), mouse at 2 to hole at 4 (time = 2), and mouse at 4 to hole at 5 (time
= 1). The maximum time is 4.

Input: mices[] = [1, 2], holes[] = [20, 10]
Output: 18
-------------------------------------------------
❌ Brute Force
- Idea: The brute force approach would be to check every possible one-to-one
assignment of mice to holes. This is a permutation problem. For N mice, there are
N! possible assignments.
- Time complexity: O(N! * N), where N is the number of mice.
- Space complexity: O(N) for recursion.
- Limitations: Infeasible for any but the smallest values of N.

✅ Optimized Approachs
- Idea: The problem can be solved efficiently with a **greedy approach**. To
minimize the maximum time taken, we should match the mice and holes in a sorted
order. The key insight is that if we sort both the mice and hole positions, the
optimal assignment is to match the i-th mouse to the i-th hole.
- Approach: A greedy algorithm using sorting.
- Algorithm:
  1. Sort the `mices` array in non-decreasing order.
  2. Sort the `holes` array in non-decreasing order.
  3. Iterate from i = 0 to n-1, where n is the number of mice/holes.
  4. For each pair of `mices[i]` and `holes[i]`, calculate the time taken, which is
  the absolute difference `|mices[i] - holes[i]|`.
  5. The minimum possible value for the "time taken by the last mouse" is the
  maximum of all these individual times.
  6. Keep a running `max_time` and update it with the current pair's time.
- Time complexity: O(N log N) dominated by the sorting step.
- Space complexity: O(1) if sorting is done in-place.

💡 Key Pattern:
- **Greedy Matching on Sorted Arrays**: When asked to minimize the maximum
difference or sum of pairs between two arrays, sorting both arrays and then
matching corresponding elements is often the optimal greedy strategy. 

ℹ️ Keywords:
- Greedy Algorithm, Sorting, Minimizing Max, Assignment Problem, Two Pointers

🗒️ Notes
- The proof for this greedy approach is based on an exchange argument. If we have
a non-optimal assignment where a mouse `A` (at `mices[i]`) is assigned to a hole
`B` (at `holes[j]`) and mouse `C` (at `mices[k]`) is assigned to hole `D` (at
`holes[l]`), with `mices[i] < mices[k]` and `holes[j] > holes[l]`, we can always
swap their assignments to reduce the total movement, or at least not increase
the max time.
-------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    /**
     * @brief Finds the minimum time for the last mouse to reach its hole.
     * @param mices A vector of integers representing the positions of mice.
     * @param holes A vector of integers representing the positions of holes.
     * @return The minimum possible maximum time.
     */
    int assignHole(vector<int> &mices, vector<int> &holes)
    {
        // Sort both arrays to apply the greedy matching strategy.
        sort(mices.begin(), mices.end());
        sort(holes.begin(), holes.end());
        
        int n = mices.size();
        int max_time = 0;
        
        // Iterate through the sorted arrays and find the maximum time.
        for (int i = 0; i < n; ++i)
        {
            int current_time = abs(mices[i] - holes[i]);
            max_time = max(max_time, current_time);
        }
        
        return max_time;
    }
};

int main()
{
    Solution sol;
    
    // Example 1
    vector<int> mices1 = {4, -4, 2};
    vector<int> holes1 = {4, 0, 5};
    cout << "Example 1: Min max time = " << sol.assignHole(mices1, holes1) << endl; 
    // Expected: 4

    // Example 2
    vector<int> mices2 = {1, 2};
    vector<int> holes2 = {20, 10};
    cout << "Example 2: Min max time = " << sol.assignHole(mices2, holes2) << endl; 
    // Expected: 18
    
    return 0;
}