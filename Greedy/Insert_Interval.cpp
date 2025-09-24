/*
File: Insert_Interval.cpp
Date: 2025-09-24 10:36

Problem: Insert Interval
Link: https://leetcode.com/problems/insert-interval/

Problem Statement:
You are given a sorted array of non-overlapping intervals `intervals`. You are
also given a `newInterval`. Insert `newInterval` into `intervals` such that the
resulting array is still sorted and non-overlapping. Merge overlapping intervals
if necessary.

Example 1:
Input: intervals = [[1,3],[6,9]], newInterval = [2,5]
Output: [[1,5],[6,9]]
Explanation: The new interval [2,5] overlaps with [1,3], so they are merged.

Example 2:
Input: intervals = [[1,2],[3,5],[6,7],[8,10],[12,16]], newInterval = [4,8]
Output: [[1,2],[3,10],[12,16]]
Explanation: The new interval [4,8] overlaps with [3,5], [6,7], and [8,10].
-------------------------------------------------
❌ Brute Force
- Idea: A brute-force approach would be to first insert the `newInterval` into
the array, and then use a separate algorithm (like the one for "Merge Intervals")
to merge all overlapping intervals.
- Time complexity: O(N log N) if the sorting step is required.
- Space complexity: O(N) to store the new array.
- Limitations: This is not the most efficient method because it doesn't
leverage the pre-sorted nature of the input.

✅ Optimized Approach
- Idea: Since the input `intervals` array is already sorted and non-overlapping, we
can process the insertion and merging in a single linear pass. This is a greedy
approach that handles three distinct phases: before the overlap, during the
overlap, and after the overlap.
- Approach: A greedy, single-pass algorithm.
- Algorithm:
  1. Initialize a result array `ans`.
  2. **Phase 1: Add non-overlapping intervals before `newInterval`**. Iterate
  through `intervals` and add any interval that ends before `newInterval` starts
  (i.e., `intervals[i][1] < newInterval[0]`) to `ans`.
  3. **Phase 2: Merge overlapping intervals**. Iterate through `intervals` as long
  as an overlap exists (i.e., `intervals[i][0] <= newInterval[1]`). For each
  overlap, expand `newInterval` by taking the minimum of the start times and the
  maximum of the end times.
  4. **Phase 3: Add the merged interval and remaining intervals**. After the loop
  from Phase 2, the `newInterval` will be updated to its final, merged form. Add this
  merged `newInterval` to `ans`. Then, add all remaining intervals from the original
  array to `ans`.
- Time complexity: O(N) because we iterate through the `intervals` array only
once.
- Space complexity: O(N) to store the new array.

💡 Key Pattern:
- **Interval Problems with Sorting**: The sorted nature of the input is a critical
clue. It allows us to process the intervals linearly and make local greedy
decisions (to merge or not) that lead to a globally optimal solution.

ℹ️ Keywords:
- Greedy Algorithm, Interval Problems, Sorting, Linear Scan, Two Pointers

🗒️ Notes
- The "Merge Intervals" problem is a good prerequisite for this one, as the
merging logic is a core part of the solution.
-------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    /**
     * @brief Inserts a new interval into a sorted list of non-overlapping intervals,
     * merging if necessary.
     * @param intervals A sorted vector of non-overlapping intervals.
     * @param newInterval The interval to insert.
     * @return The updated vector of intervals.
     */
    vector<vector<int>> insert(vector<vector<int>> &intervals,
                               vector<int> &newInterval)
    {
        vector<vector<int>> ans;
        int i = 0;
        int n = intervals.size();

        // Phase 1: Add intervals that are completely before newInterval.
        while (i < n && intervals[i][1] < newInterval[0])
        {
            ans.push_back(intervals[i]);
            i++;
        }

        // Phase 2: Merge overlapping intervals.
        // The condition for overlap is `intervals[i][0] <= newInterval[1]`.
        // The intervals are sorted, so we only need to check this condition.
        while (i < n && intervals[i][0] <= newInterval[1])
        {
            newInterval[0] = min(newInterval[0], intervals[i][0]);
            newInterval[1] = max(newInterval[1], intervals[i][1]);
            i++;
        }
        ans.push_back(newInterval);

        // Phase 3: Add intervals that are completely after the merged interval.
        while (i < n)
        {
            ans.push_back(intervals[i]);
            i++;
        }

        return ans;
    }
};

int main()
{
    Solution sol;

    // Example 1
    vector<vector<int>> intervals1 = {{1, 3}, {6, 9}};
    vector<int> newInterval1 = {2, 5};
    vector<vector<int>> result1 = sol.insert(intervals1, newInterval1);
    cout << "Example 1 Output: ";
    for (const auto &interval : result1)
    {
        cout << "[" << interval[0] << ", " << interval[1] << "] ";
    }
    cout << endl; // Expected: [[1,5], [6,9]]

    // Example 2
    vector<vector<int>> intervals2 = {{1, 2}, {3, 5}, {6, 7}, {8, 10}, {12, 16}};
    vector<int> newInterval2 = {4, 8};
    vector<vector<int>> result2 = sol.insert(intervals2, newInterval2);
    cout << "Example 2 Output: ";
    for (const auto &interval : result2)
    {
        cout << "[" << interval[0] << ", " << interval[1] << "] ";
    }
    cout << endl; // Expected: [[1,2], [3,10], [12,16]]

    return 0;
}