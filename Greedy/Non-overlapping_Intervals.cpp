/*
File: Non-overlapping_Intervals.cpp
Date: 2025-09-24 10:59

Problem: Non-overlapping Intervals
Link: https://leetcode.com/problems/non-overlapping-intervals/

Problem Statement:
Given an array of intervals `intervals` where `intervals[i] = [start_i, end_i]`,
return the minimum number of intervals you need to remove to make the rest of the
intervals non-overlapping. Note that intervals which only touch at a point are
non-overlapping. For example, [1, 2] and [2, 3] are non-overlapping.

Example 1:
Input: intervals = [[1,2],[2,3],[3,4],[1,3]]
Output: 1
Explanation: [1,3] can be removed and the rest of the intervals are
non-overlapping.

Example 2:
Input: intervals = [[1,2],[1,2],[1,2]]
Output: 2
Explanation: You need to remove two [1,2] to make the rest of the intervals
non-overlapping.

Example 3:
Input: intervals = [[1,2],[2,3]]
Output: 0
Explanation: You don't need to remove any of the intervals since they're already
non-overlapping.
-------------------------------------------------
❌ Brute Force
- Idea: Generate all  2^N  subsets of intervals and check each subset for
non-overlapping properties. Find the largest valid subset, and the answer is
 N - |largest_subset| .
- Time complexity:  O(2^N * N) , which is highly inefficient.
- Space complexity:  O(N)  for storing subsets.
- Limitations: Infeasible for any significant number of intervals.

✅ Optimized Approach
- Idea: This problem is a classic greedy problem. To find the minimum number of
removals, we can instead find the **maximum number of non-overlapping
intervals** and subtract that from the total. The greedy choice is to always
select the interval that **finishes earliest**, as this leaves the most room
for subsequent intervals.
- Approach: A greedy, single-pass algorithm after sorting.
- Algorithm:
    1.  Sort the input `intervals` array in ascending order based on their end
    times.
    2.  Initialize `removed_count` to 0.
    3.  Set `prev_end` to the end time of the first interval in the sorted array.
    4.  Iterate through the rest of the intervals, starting from the second one.
    5.  For each current interval, if its start time is greater than or equal to
    `prev_end`, it does not overlap. We accept this interval and update `prev_end`
    to its end time.
    6.  If its start time is less than `prev_end`, it overlaps. We must remove
    this interval to maintain our non-overlapping set, so we increment
    `removed_count`.
    7.  Return `removed_count`.
- Time complexity:  O(Nlog N)  due to the sorting step. The subsequent linear
scan is  O(N) .
- Space complexity:  O(1)  if the sort is in-place, otherwise  O(N)  for a copy.

💡 Key Pattern:
- **Greedy with Sorting on End Times**: Many interval-related problems,
especially those involving maximizing a set or minimizing removals, can be
solved by sorting intervals by their end times and then making a series of
greedy choices. This is a common pattern in activity selection and scheduling
problems.

ℹ️ Keywords:
- Greedy Algorithm, Interval Scheduling, Sorting, Non-overlapping Intervals,
Activity Selection

🗒️ Notes
- The logic works because by selecting the interval that ends earliest, we leave
the maximum possible time for subsequent intervals, thereby ensuring we can fit
in as many non-overlapping intervals as possible.
-------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

// Custom comparator for sorting based on the end time of intervals.
bool comp(const vector<int> &a, const vector<int> &b)
{
    return a[1] < b[1];
}

class Solution
{
public:
    /**
     * @brief Calculates the minimum number of intervals to remove to make the rest
     * non-overlapping.
     * @param intervals A vector of intervals.
     * @return The minimum number of intervals to remove.
     */
    int eraseOverlapIntervals(vector<vector<int>> &intervals)
    {
        if (intervals.empty())
        {
            return 0;
        }

        // Sort intervals by their end times.
        sort(intervals.begin(), intervals.end(), comp);

        // Initialize count of removed intervals and the end of the first interval.
        int removed_count = 0;
        int prev_end = intervals[0][1];

        // Iterate through the rest of the intervals.
        for (size_t i = 1; i < intervals.size(); ++i)
        {
            int current_start = intervals[i][0];

            // If the current interval does not overlap with the previous one,
            // we can keep it.
            if (current_start >= prev_end)
            {
                prev_end = intervals[i][1]; // Update the end time for the next comparison.
            }
            // If there's an overlap, we must remove the current interval
            // because the previous one ends earlier, leaving more room for future
            // intervals.
            else
            {
                removed_count++;
            }
        }
        return removed_count;
    }
};

int main()
{
    Solution sol;

    // Example 1
    vector<vector<int>> intervals1 = {{1, 2}, {2, 3}, {3, 4}, {1, 3}};
    cout << "Example 1 Output: " << sol.eraseOverlapIntervals(intervals1) << endl;
    // Expected: 1

    // Example 2
    vector<vector<int>> intervals2 = {{1, 2}, {1, 2}, {1, 2}};
    cout << "Example 2 Output: " << sol.eraseOverlapIntervals(intervals2) << endl;
    // Expected: 2

    // Example 3
    vector<vector<int>> intervals3 = {{1, 2}, {2, 3}};
    cout << "Example 3 Output: " << sol.eraseOverlapIntervals(intervals3) << endl;
    // Expected: 0

    return 0;
}