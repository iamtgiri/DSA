/*
File: Parallel_Courses_3.cpp
Date: 2025-10-28 22:09

Problem: Parallel Courses III
Link: https://leetcode.com/problems/parallel-courses-iii/description/

Problem Statement:
Given an integer n, which is the number of courses (1 to n), a list of
prerequisite relations, and an array time where time[i] is the duration
of course i+1. Find the minimum time required to complete all courses,
assuming any number of courses can be taken in parallel.

-------------------------------------------------
❌ Brute Force
- Idea: Simulate the course scheduling month by month. At each month, check
  which courses have completed their prerequisites and are not yet started.
  Assign them resources. Repeat until all courses are finished.
- Time complexity: O(N * (N + R) * T_max), where T_max is the maximum total time.
  This is slow as T_max can be large.
- Space complexity: O(N) to track course status (started/finished).
- Limitations: Inefficient due to step-by-step time simulation, especially for
  large course durations.

✅ Optimized Approachs
- Idea: The minimum time to finish all courses is determined by the **longest
  path** (or **critical path**) in the dependency graph. This can be solved
  efficiently using Topological Sort combined with Dynamic Programming.
- Approach: **Kahn's Algorithm (BFS-based Topological Sort) with DP**.
- Algorithm:
    1. **Graph Setup:** Build the adjacency list and calculate the initial indegree
       for all N courses (adjusting for 0-based indexing: course X is index X-1).
    2. **DP Initialization:** Create a DP array, `reqtime`, where `reqtime[i]`
       stores the minimum time required to finish course `i` and all its prerequisites.
       Initialize the queue `q` with all courses having `indegree = 0`, setting
       their `reqtime[i] = time[i]`.
    3. **BFS/DP Iteration:** While `q` is not empty, process the current `node`:
        - For each neighbor `nei`:
            - **DP Transition:** Update the time for `nei` based on the longest
              prerequisite path: `reqtime[nei] = max(reqtime[nei], reqtime[node] + time[nei])`.
            - Decrement `indegree[nei]`.
            - If `indegree[nei]` drops to 0, enqueue `nei`.
    4. **Result:** The final answer is the maximum value in the `reqtime` array.
- Time complexity: **O(N + R)**, where N is the number of courses and R is the
  number of relations. This is standard complexity for Topological Sort.
- Space complexity: **O(N + R)** for adjacency list, indegree, queue, and DP array.

💡 Key Pattern:
- **Longest Path in a DAG:** Solved by Topological Sort combined with Dynamic
  Programming. Critical path analysis.

ℹ️ Keywords:
- Topological Sort, Dynamic Programming (DP), Critical Path, Longest Path in DAG.

🗒️ Notes
- The time array is 0-indexed corresponding to course 1 to N. The relations are 1-indexed.
- The use of `max` in the DP transition is crucial because all prerequisites must
  be finished before a course can start, meaning the start time is determined by
  the latest finishing prerequisite.
-------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    /**
     * @brief Calculates the minimum time required to complete all courses using
     * Kahn's algorithm (Topological Sort) and Dynamic Programming.
     * @param n The number of courses (1 to n).
     * @param relations A vector of prerequisites, where [u, v] means course u must
     * be taken before course v (1-based indexing).
     * @param time A vector where time[i] is the duration of course i+1 (0-based indexing).
     * @return The minimum total time to complete all courses.
     */
    int minimumTime(int n, vector<vector<int>> &relations, vector<int> &time)
    {
        // reqtime[i] stores the minimum time to finish course i
        vector<int> reqtime(n, 0);
        vector<vector<int>> adj(n);
        vector<int> indeg(n, 0);

        // 1. Build Graph and Indegree Array
        for (auto r : relations)
        {
            // Adjust to 0-based indexing: r[0]-1 -> r[1]-1
            int u = r[0] - 1;
            int v = r[1] - 1;
            adj[u].push_back(v);
            indeg[v]++;
        }

        queue<int> q;
        // 2. Initialize Queue and Base Case DP
        for (int i = 0; i < n; ++i)
        {
            if (indeg[i] == 0)
            {
                q.push(i);
                // Time required for starting courses is just their own duration
                reqtime[i] = time[i];
            }
        }

        // 3. BFS/DP Iteration
        while (!q.empty())
        {
            int node = q.front();
            q.pop();

            for (int nei : adj[node])
            {
                // DP Transition: Update time for neighbor 'nei'
                // The time to finish 'nei' is max(current time, time via 'node' path)
                // where time via 'node' path is (time to finish prerequisite 'node') + (duration of 'nei').
                reqtime[nei] = max(reqtime[nei], reqtime[node] + time[nei]);

                // Topological Sort update
                indeg[nei]--;
                if (indeg[nei] == 0)
                    q.push(nei);
            }
        }

        // 4. Result
        // The maximum time in reqtime is the critical path time
        return *max_element(reqtime.begin(), reqtime.end());
    }
};

int main()
{
    Solution sol;

    cout << "--- Parallel Courses III Time Calculator ---\n";

    // Test Case 1: Simple linear chain
    // Courses: 3. Time: [1, 2, 3]. Relations: 1->2, 2->3
    // Path: 1 (1) -> 2 (1+2=3) -> 3 (3+3=6). Max time = 6
    int n1 = 3;
    vector<vector<int>> r1 = {{1, 2}, {2, 3}};
    vector<int> t1 = {1, 2, 3};
    int res1 = sol.minimumTime(n1, r1, t1);
    cout << "Test 1 | Courses: " << n1 << ", Time: {1, 2, 3}, Relations: 1->2, 2->3\n";
    cout << "Result: " << res1 << " (Expected: 6)\n";
    cout << "--------------------------------\n";

    // Test Case 2: Parallel execution (Max Time is the bottleneck)
    // Courses: 4. Time: [10, 20, 30, 40]. Relations: None
    // All run in parallel. Max time is 40.
    int n2 = 4;
    vector<vector<int>> r2 = {};
    vector<int> t2 = {10, 20, 30, 40};
    int res2 = sol.minimumTime(n2, r2, t2);
    cout << "Test 2 | Courses: " << n2 << ", Time: {10, 20, 30, 40}, Relations: None\n";
    cout << "Result: " << res2 << " (Expected: 40)\n";
    cout << "--------------------------------\n";

    // Test Case 3: Diverging and Converging paths (Critical Path)
    // Courses: 5. Time: [1, 1, 1, 1, 1]
    // Relations: 1->5, 2->5, 3->5, 4->5
    // All paths take 1+1=2 time. Max total time = 2.
    int n3 = 5;
    vector<vector<int>> r3 = {{1, 5}, {2, 5}, {3, 5}, {4, 5}};
    vector<int> t3 = {1, 1, 1, 1, 1};
    int res3 = sol.minimumTime(n3, r3, t3);
    cout << "Test 3 | Courses: " << n3 << ", Time: {1, 1, 1, 1, 1}, Relations: 1,2,3,4 -> 5\n";
    cout << "Result: " << res3 << " (Expected: 2)\n";
    cout << "--------------------------------\n";

    // Test Case 4: Weighted Critical Path (complex)
    // Courses: 5. Time: [5, 10, 2, 3, 1]
    // Relations: 1->3, 2->3, 3->4, 4->5
    // Course 3 (Time=2) depends on 1 (5) and 2 (10). Longest path to 3 is 10+2=12.
    // Course 5 (Time=1) finishes at 12+3+1 = 16.
    int n4 = 5;
    vector<vector<int>> r4 = {{1, 3}, {2, 3}, {3, 4}, {4, 5}};
    vector<int> t4 = {5, 10, 2, 3, 1};
    int res4 = sol.minimumTime(n4, r4, t4);
    cout << "Test 4 | Courses: " << n4 << ", Time: {5, 10, 2, 3, 1}, Relations: 1,2->3->4->5\n";
    cout << "Result: " << res4 << " (Expected: 16)\n";
    cout << "--------------------------------\n";

    return 0;
}
