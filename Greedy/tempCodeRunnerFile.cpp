/*
File: Non-overlapping_Intervals.cpp
Date: 2025-09-24 10:59

Problem: Non-overlapping Intervals
Link: https://leetcode.com/problems/non-overlapping-intervals/

Problem Statement:
Given an array of intervals intervals where intervals[i] = [starti, endi], return the minimum number of intervals you need to remove to make the rest of the intervals non-overlapping.
Note that intervals which only touch at a point are non-overlapping. For example, [1, 2] and [2, 3] are non-overlapping.

Example 1:
Input: intervals = [[1,2],[2,3],[3,4],[1,3]]
Output: 1
Explanation: [1,3] can be removed and the rest of the intervals are non-overlapping.

Example 2:
Input: intervals = [[1,2],[1,2],[1,2]]
Output: 2
Explanation: You need to remove two [1,2] to make the rest of the intervals non-overlapping.

Example 3:
Input: intervals = [[1,2],[2,3]]
Output: 0
Explanation: You don't need to remove any of the intervals since they're already non-overlapping.
-------------------------------------------------
❌ Brute Force
- Idea:
- Time complexity:
- Space complexity:
- Limitations:

✅ Optimized Approachs
- Idea:
- Approach:
- Algorithm:
- Time complexity:
- Space complexity:

💡 Key Pattern:
-

ℹ️ Keywords:
-

🗒️ Notes
- (What did I learn? Similar problems? Mistakes I made?)
-------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

bool comp(vector<int> &a, vector<int> &b)
{
    return a[1] < b[1]; // sort by end time
}
class Solution
{
public:
    /**
     * @brief
     * @param
     * @return
     */

    int eraseOverlapIntervals(vector<vector<int>> &intervals)
    {
        sort(intervals.begin(), intervals.end(), comp);
        int prev_end = intervals[0][1]; // take the first interval
        int count = 0;

        for (int i = 1; i < intervals.size(); i++)
        {
            if (intervals[i][0] >= prev_end)
            {
                prev_end = intervals[i][1]; // no overlap, accept interval
            }
            else
            {
                count++; // overlap → remove this interval
            }
        }
        return count;
    }
};

int main()
{
    Solution sol;
    // Example test cases

    return 0;
}