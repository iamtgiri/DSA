/*
File: Single-Threaded_CPU.cpp
Date: 2025-09-24 17:56

Problem: Single-Threaded CPU
Link: https://leetcode.com/problems/single-threaded-cpu/

Problem Statement:
You are given n tasks labeled from 0 to n - 1 represented by a 2D integer
array `tasks`, where `tasks[i] = [enqueueTime_i, processingTime_i]` means
that the i-th task will be available to process at `enqueueTime_i` and will
take `processingTime_i` to finish.

You have a single-threaded CPU that can process at most one task at a time.
The CPU's behavior is as follows:
- If idle with no available tasks, it remains idle.
- If idle with available tasks, it chooses the one with the shortest
  processing time. If there's a tie, it chooses the task with the smallest
  index.
- Once a task starts, it runs to completion without interruption.
- A new task can be started instantly after one finishes.

Return the order in which the CPU will process the tasks.

Example 1:
Input: tasks = [[1,2],[2,4],[3,2],[4,1]]
Output: [0,2,3,1]
Explanation: The events go as follows:
- At time = 1, task 0 is available. CPU is idle and starts task 0.
- At time = 2, task 1 is available.
- At time = 3, CPU finishes task 0. Task 2 is also available.
- CPU is idle, available tasks are {1, 2}. Task 2 has a shorter processing
  time (2 < 4), so it's chosen.
- At time = 4, task 3 is available.
- At time = 5, CPU finishes task 2. Available tasks are {1, 3}. Task 3 is
  chosen (1 < 4).
- At time = 6, CPU finishes task 3 and starts task 1.
- At time = 10, CPU finishes task 1.

Example 2:
Input: tasks = [[7,10],[7,12],[7,5],[7,4],[7,2]]
Output: [4,3,2,0,1]
Explanation: All tasks become available at time 7. The CPU processes them
in increasing order of their processing times, with ties broken by index.
-------------------------------------------------
❌ Brute Force
- Idea: Simulate the CPU's behavior second by second. At each time step, check
  for available tasks and process according to the rules. This is inefficient.
- Time complexity: O(max(E, T_total)), where E is the max enqueue time and
  T_total is the sum of all processing times. This can be very large.
- Space complexity: O(N) to store tasks.
- Limitations: Time-based simulation is too slow for large time values.

✅ Optimized Approach
- Idea: Instead of simulating time second by second, we can jump from one
  event to the next. The events are when a task becomes available or when the
  CPU finishes a task. The problem rules for picking the next task (shortest
  processing time, then smallest index) scream for a **priority queue**.
- Approach: Event-driven simulation using a sorted array and a priority queue.
- Algorithm:
    1.  Augment the input `tasks` array to include the original index.
    2.  Sort the `tasks` array based on `enqueueTime`.
    3.  Initialize a `timer` to track the current time, a `pointer` to the
        sorted tasks, and an empty **min-priority queue** to store available
        tasks. The priority queue should order by `(processingTime, originalIndex)`.
    4.  Initialize an empty list `order` to store the result.
    5.  Loop while there are still tasks to process (`pointer < n`) or the
        priority queue is not empty.
    6.  **Add Available Tasks**: In each loop iteration, move the `pointer`
        forward to add all tasks with `enqueueTime <= timer` into the priority
        queue.
    7.  **Process Task**: If the priority queue is not empty, extract the top
        task (the one with the shortest processing time/smallest index). Add
        its original index to `order` and update the `timer` by adding its
        processing time.
    8.  **Handle Idle CPU**: If the priority queue is empty but there are
        still tasks to process (i.e., `pointer < n`), it means the CPU is
        idle. Jump the `timer` forward to the `enqueueTime` of the next
        available task to avoid unnecessary loops.
- Time complexity: O(N log N). Sorting the tasks takes O(N log N). The main
  while loop processes each task once. Each `push` and `pop` on the priority
  queue takes O(log N).
- Space complexity: O(N) for the priority queue and the result array.

💡 Key Pattern:
- **Event Simulation with Priority Queue**: This is a classic pattern for
  scheduling problems where events occur at discrete times and the choice
  of the next event depends on a dynamic priority.

ℹ️ Keywords:
- Scheduling, Greedy Algorithm, Priority Queue, Event Simulation, Sorting,
  Shortest Job First (SJF)

🗒️ Notes
- The problem is a variant of the Shortest Job First (SJF) scheduling
  algorithm, but with a twist: tasks arrive over time, not all at once. This
  necessitates a priority queue to handle the dynamic set of available tasks.
-------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    /**
     * @brief Determines the processing order of tasks by a single-threaded CPU
     * based on arrival and processing times.
     * @param tasks A vector of tasks where each task is [enqueueTime,
     * processingTime].
     * @return A vector of integers representing the order of task indices.
     */
    vector<int> getOrder(vector<vector<int>> &tasks)
    {
        int n = tasks.size();

        // Step 1: Augment each task with its original index.
        for (int i = 0; i < n; ++i)
            tasks[i].push_back(i);

        // Step 2: Sort tasks based on their enqueue time.
        sort(tasks.begin(), tasks.end());

        // `timer` tracks the current time. Use long long to prevent overflow.
        long long timer = 0;

        // The result array.
        vector<int> order;

        // A min-priority queue to store available tasks.
        // It's ordered by: 1) processing time (min-heap)
        //                 2) original index (for tie-breaking)
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> available_tasks;

        int task_idx = 0;

        // Loop until all tasks are processed.
        while (task_idx < n || !available_tasks.empty())
        {

            // Phase 1: Add all newly available tasks to the queue.
            while (task_idx < n && tasks[task_idx][0] <= timer)
            {
                available_tasks.emplace(tasks[task_idx][1], tasks[task_idx][2]);
                task_idx++;
            }

            // Phase 2: Process a task if the CPU is not idle.
            if (!available_tasks.empty())
            {
                auto [processing_t, original_idx] = available_tasks.top();
                available_tasks.pop();

                order.push_back(original_idx);
                timer += processing_t;
            }
            // Phase 3: Handle idle CPU. Jump the timer to the next available task.
            else
            {
                if (task_idx < n)
                {
                    timer = tasks[task_idx][0];
                }
            }
        }
        return order;
    }
};

int main()
{
    Solution sol;

    // Example 1
    vector<vector<int>> tasks1 = {{1, 2}, {2, 4}, {3, 2}, {4, 1}};
    vector<int> result1 = sol.getOrder(tasks1);
    cout << "Example 1 Output: ";
    for (int idx : result1)
        cout << idx << " ";
    cout << endl; // Expected: [0, 2, 3, 1]

    // Example 2
    vector<vector<int>> tasks2 = {{7, 10}, {7, 12}, {7, 5}, {7, 4}, {7, 2}};
    vector<int> result2 = sol.getOrder(tasks2);
    cout << "Example 2 Output: ";
    for (int idx : result2)
        cout << idx << " ";
    cout << endl; // Expected: [4, 3, 2, 0, 1]

    return 0;
}