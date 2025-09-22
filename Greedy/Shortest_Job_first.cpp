/*
File: Shortest_Job_first.cpp
Date: 2025-09-22 22:38

Problem: Shortest Job first
Link: https://www.geeksforgeeks.org/problems/shortest-job-first/1
Problem Statement:
Given an array of integers `bt` of size `n`. Array `bt` denotes the burst time of
each process. Calculate the average waiting time of all the processes and return
the nearest integer which is smaller or equal to the output.
Note: Consider all processes are available at time 0.

Example 1:
Input:
n = 5
bt = [4,3,7,1,2]
Output: 4
Explanation: After sorting burst times by shortest job policy, calculated average
waiting time is 4.

Example 2:
Input:
n = 4
arr = [1,2,3,4]
Output: 2
Explanation: After sorting burst times by shortest job policy, calculated average
waiting time is 2.
-------------------------------------------------
❌ Brute Force
- Idea: A brute-force approach would be to calculate the waiting time for every
possible permutation of the processes and then find the minimum average waiting
time.
- Time complexity: O(N! * N), which is highly inefficient.
- Space complexity: O(N) for storing permutations.
- Limitations: Infeasible for any but the smallest number of processes.

✅ Optimized Approach
- Idea: This problem is a classic **greedy algorithm**. To minimize the total
waiting time, the scheduler should always process the job with the **shortest
burst time** first. This is because a short job will quickly free up the CPU,
minimizing the wait time for all subsequent jobs.
- Approach: A greedy algorithm using sorting and a single pass.
- Algorithm:
  1. Sort the `bt` (burst time) array in non-decreasing order.
  2. Initialize `total_waiting_time` to 0 and `current_completion_time` to 0.
  3. Iterate through the sorted `bt` array. For each burst time `b`:
     - The waiting time for this process is the `current_completion_time`. Add this
     to `total_waiting_time`.
     - Update `current_completion_time` by adding the current burst time `b` to it.
  4. The average waiting time is `total_waiting_time` divided by the number of
  processes, `n`.
  5. The problem requires returning the floor of this average.
- Time complexity: O(N log N) dominated by the sorting step.
- Space complexity: O(1) if sorting is done in-place.

💡 Key Pattern:
- **Greedy Scheduling**: When dealing with scheduling problems where all items
are available at the same time, a greedy approach based on a key property (like
shortest job, earliest deadline, or highest profit) is often the optimal strategy.


ℹ️ Keywords:
- Greedy Algorithm, Scheduling, Shortest Job First, SJF, Sorting, Average Waiting Time

🗒️ Notes
- This implementation assumes a non-preemptive SJF schedule with all processes
arriving at time 0. If arrival times were different, the problem would be more
complex and require a different approach (e.g., a priority queue to simulate the
scheduler).
-------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    /**
     * @brief Calculates the average waiting time using the SJF scheduling algorithm.
     * @param bt A vector of integers representing burst times.
     * @return The floor of the average waiting time.
     */
    long long SJF_solve(vector<int>& bt) {
        int n = bt.size();
        
        // Sort burst times in non-decreasing order.
        sort(bt.begin(), bt.end());
        
        long long total_waiting_time = 0;
        long long current_completion_time = 0;
        
        // Calculate waiting time for each process.
        for (int burst_time : bt)
        {
            total_waiting_time += current_completion_time;
            current_completion_time += burst_time; 
        }
        
        // Calculate the average and return the floor.
        return total_waiting_time / n;
    }

};

int main() {
    Solution sol;
    
    // Example 1
    vector<int> bt1 = {4, 3, 7, 1, 2};
    cout << "Example 1: Average waiting time = " << sol.SJF_solve(bt1) << endl; 
    // Expected: 4

    // Example 2
    vector<int> bt2 = {1, 2, 3, 4};
    cout << "Example 2: Average waiting time = " << sol.SJF_solve(bt2) << endl; 
    // Expected: 2
    
    return 0;
}