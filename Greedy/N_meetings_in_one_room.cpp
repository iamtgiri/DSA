/*
File: N_meetings_in_one_room.cpp
Date: 2025-09-22 09:59

Problem: N meetings in one room
Link: https://www.geeksforgeeks.org/problems/n-meetings-in-one-room-1587115620/1
Problem Statement: There is one room and n meetings. You are given a list of start and end times for each meeting. Find the maximum number of meetings that can be accommodated in the room.

-------------------------------------------------
❌ Brute Force
- Idea: The brute-force approach would involve generating all possible subsets of meetings. For each subset, we would check if the meetings are non-overlapping. The largest valid subset would give the maximum number of meetings.
- Time complexity: O(2^N * N) - O(2^N) for all subsets and O(N) to check for overlap in each subset.
- Space complexity: O(N) for storing subsets.
- Limitations: Exponential time complexity, making it unfeasible for larger N.

✅ Optimized Approach
- Idea: This problem is a classic example of a **greedy algorithm**. The optimal strategy is to always choose the meeting that finishes earliest. By doing so, we free up the room as quickly as possible, allowing for the maximum number of subsequent meetings to be scheduled.
- Approach: A greedy algorithm.
- Algorithm:
  1. Combine the start and end times of each meeting into a single data structure, like a pair or a custom struct, to keep them associated.
  2. Sort all meetings in ascending order of their **end times**. This is the key greedy step.
  3. Initialize a count of meetings to 1 (for the first meeting) and set the `last_end_time` to the end time of the first meeting in the sorted list.
  4. Iterate through the remaining sorted meetings.
  5. For each meeting, check if its **start time** is greater than the `last_end_time`. If it is, this meeting can be scheduled without overlapping.
  6. If a meeting can be scheduled, increment the count and update `last_end_time` to the end time of this newly scheduled meeting.
  7. Return the final count.
- Time complexity: O(N log N) dominated by the sorting step.
- Space complexity: O(N) to store the combined meeting data.

💡 Key Pattern:
- **Greedy Algorithms**: The problem exhibits the greedy-choice property and optimal substructure. Selecting the meeting that finishes earliest is a locally optimal choice that leads to a globally optimal solution for the overall problem.

ℹ️ Keywords:
- Greedy Algorithm, Activity Selection, Interval Scheduling, Sorting

🗒️ Notes
- This problem is also known as the **Activity Selection Problem**. It demonstrates that greedy choices, when applied correctly, can solve certain optimization problems efficiently.
-------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    /**
     * @brief Finds the maximum number of meetings that can be scheduled in a single room.
     * @param start A vector of integers representing the start times of meetings.
     * @param end A vector of integers representing the end times of meetings.
     * @return The maximum number of non-overlapping meetings.
     */
    int maxMeetings(vector<int> &start, vector<int> &end)
    {
        int n = start.size();

        // Combine start and end times into pairs for sorting.
        // We sort by end time, so the pair is {end_time, start_time}.
        vector<pair<int, int>> meetings;
        for (int i = 0; i < n; ++i)
        {
            meetings.emplace_back(end[i], start[i]);
        }

        // Sort meetings based on their end times in ascending order.
        sort(meetings.begin(), meetings.end());

        int meeting_count = 0;
        int last_end_time = -1; // -1 ensures the first meeting is always picked.

        // Greedily select non-overlapping meetings.
        for (const auto &meeting : meetings)
        {
            int current_start_time = meeting.second;
            int current_end_time = meeting.first;

            // If the current meeting starts after the last one ended, it's valid.
            if (current_start_time > last_end_time)
            {
                meeting_count++;
                last_end_time = current_end_time;
            }
        }
        return meeting_count;
    }
};

int main()
{
    Solution sol;

    // Example 1
    vector<int> start1 = {1, 3, 0, 5, 8, 5};
    vector<int> end1 = {2, 4, 6, 7, 9, 9};
    cout << "Example 1: Max meetings = " << sol.maxMeetings(start1, end1) << endl; // Expected: 4

    // Example 2
    vector<int> start2 = {10, 12, 20};
    vector<int> end2 = {20, 25, 30};
    cout << "Example 2: Max meetings = " << sol.maxMeetings(start2, end2) << endl; // Expected: 1

    return 0;
}