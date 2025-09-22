/*
File: Merge_Intervals.cpp
Date: 2025-09-22 22:23

Problem: Merge Intervals
Link: https://leetcode.com/problems/merge-intervals/

Problem Statement:
Given an array of intervals where intervals[i] = [starti, endi], merge all
overlapping intervals, and return an array of the non-overlapping intervals
that cover all the intervals in the input.

Example 1:
Input: intervals = [[1,3],[2,6],[8,10],[15,18]]
Output: [[1,6],[8,10],[15,18]]
Explanation: Since intervals [1,3] and [2,6] overlap, merge them into [1,6].

Example 2:
Input: intervals = [[1,4],[4,5]]
Output: [[1,5]]
Explanation: Intervals [1,4] and [4,5] are considered overlapping.

Example 3:
Input: intervals = [[4,7],[1,4]]
Output: [[1,7]]
Explanation: Intervals [1,4] and [4,7] are considered overlapping.
-------------------------------------------------
❌ Brute Force
- Idea: A brute-force approach would be to check every pair of intervals for
overlap. If an overlap is found, they are merged, and the process is repeated.
This is a very inefficient and complex process to manage.
- Time complexity: O(N^2) in the worst case, as a single merge can require
another full pass to check for new overlaps.
- Space complexity: O(1) or O(N) depending on implementation.
- Limitations: Highly inefficient for large inputs due to repeated passes.

✅ Optimized Approach
- Idea: This problem is a classic **greedy algorithm** solved by sorting. The core
idea is that if we sort the intervals by their start times, any overlapping
intervals must be adjacent in the sorted list. This allows us to make a single
pass to merge them.
- Approach: A greedy, single-pass algorithm after sorting.
- Algorithm:
  1. Sort the given `intervals` array based on the start time of each interval.
  2. Initialize a `merged_intervals` list to store the results. Add the first
  interval from the sorted list to this result list.
  3. Iterate through the remaining intervals from the second one.
  4. For each interval, compare its start time with the end time of the last
  interval in the `merged_intervals` list.
  5. If there is an overlap (the current interval's start is less than or equal
  to the last merged interval's end), merge them by updating the end of the last
  merged interval to the maximum of its current end and the current interval's end.
  6. If there is no overlap, the current interval is non-overlapping and should
  be added as a new merged interval to the `merged_intervals` list.
- Time complexity: O(N log N) dominated by the sorting step.
- Space complexity: O(N) to store the merged intervals.

💡 Key Pattern:
- **Interval Problems with Sorting**: Many problems involving intervals can be
simplified by first sorting the intervals based on a key property (usually start
or end time). This transforms the problem from a complex search into a
straightforward linear scan.

ℹ️ Keywords:
- Greedy Algorithm, Interval Problems, Sorting, Two Pointers, Linear Scan

🗒️ Notes
- The initial data structure conversion from `vector<vector<int>>` to
`vector<pair<int, int>>` is not strictly necessary as C++'s `std::sort` can handle
sorting a `vector<vector<int>>` directly based on the first element. The core
logic remains the same. The provided code can be simplified by avoiding this
intermediate conversion.
-------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    /**
     * @brief Merges all overlapping intervals.
     * @param intervals A vector of vectors representing intervals.
     * @return A vector of vectors representing the merged, non-overlapping intervals.
     */
    vector<vector<int>> merge(vector<vector<int>> &intervals)
    {
        if (intervals.empty())
        {
            return {};
        }

        // Sort the intervals based on their start times.
        sort(intervals.begin(), intervals.end());

        vector<vector<int>> merged_intervals;

        // Start with the first interval.
        merged_intervals.push_back(intervals[0]);

        // Iterate through the remaining intervals.
        for (size_t i = 1; i < intervals.size(); ++i)
        {
            vector<int> &last_merged = merged_intervals.back();
            const vector<int> &current = intervals[i];

            // Check for overlap
            if (current[0] <= last_merged[1])
            {
                // Merge by updating the end time.
                last_merged[1] = max(last_merged[1], current[1]);
            }
            else
            {
                // No overlap, add a new interval.
                merged_intervals.push_back(current);
            }
        }

        return merged_intervals;
    }
};

int main()
{
    Solution sol;

    // Example 1
    vector<vector<int>> intervals1 = {{1, 3}, {2, 6}, {8, 10}, {15, 18}};
    vector<vector<int>> result1 = sol.merge(intervals1);
    cout << "Example 1 Output: ";
    for (const auto &interval : result1)
    {
        cout << "[" << interval[0] << ", " << interval[1] << "] ";
    }
    cout << endl; // Expected: [[1,6], [8,10], [15,18]]

    // Example 2
    vector<vector<int>> intervals2 = {{1, 4}, {4, 5}};
    vector<vector<int>> result2 = sol.merge(intervals2);
    cout << "Example 2 Output: ";
    for (const auto &interval : result2)
    {
        cout << "[" << interval[0] << ", " << interval[1] << "] ";
    }
    cout << endl; // Expected: [[1,5]]

    return 0;
}