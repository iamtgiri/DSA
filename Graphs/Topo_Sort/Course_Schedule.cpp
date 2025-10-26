/*
File: Course_Schedule.cpp
Date: 2025-10-26 11:40

Problem: Course Schedule
Link: https://www.geeksforgeeks.org/problems/course-schedule/1

Problem Statement:
There are N courses, labeled from 0 to N-1. Some courses may have prerequisites,
for example to take course A, you have to first take course B, which is expressed
as a pair [A, B]. Given the total number of courses and a list of prerequisite
pairs, return the ordering of courses you should take to finish all courses.
If it is impossible to finish all courses, return an empty array.

-------------------------------------------------
❌ Brute Force
- Idea: Try every possible permutation of the N courses and check if the order
  satisfies all P prerequisite conditions.
- Time complexity: O(N! * P).
- Space complexity: O(N) to store the result permutation.
- Limitations: Factorial complexity is too slow for any meaningful number of
  courses.

✅ Optimized Approachs
- Idea: The problem requires finding a valid sequence in a directed graph (a
  dependency graph). This is a classic **Topological Sort** problem. If a valid
  topological order exists, the graph is a Directed Acyclic Graph (DAG).
- Approach: **Kahn's Algorithm (BFS-based Topological Sort)**.
- Algorithm:
    1. **Build Graph & Indegree:** Represent the dependencies as a directed graph.
       An edge u -> v means u is a prerequisite for v. Calculate
       the **indegree** (number of prerequisites) for every course v.
    2. **Initialize Queue:** Add all courses (nodes) with indegree = 0
       to a queue. These are the courses that can be taken first.
    3. **Process BFS:** While the queue is not empty:
        a. Dequeue a course, add it to the result list.
        b. For every neighbor (dependent course) v of the dequeued course u:
           Decrement v's indegree.
           If v's indegree becomes 0, enqueue v.
    4. **Cycle Check:** If the size of the resulting topological order is less
       than N, a cycle exists (a deadlock), and no valid order is possible.
- Time complexity: O(N + P). Linearly proportional to the number of courses (N)
  plus the number of prerequisites (P).
- Space complexity: O(N + P) for the adjacency list, indegree array, queue,
  and result vector.

💡 Key Pattern:
- **Topological Sort:** Essential for scheduling, dependency resolution, and
  build processes where ordering matters.

ℹ️ Keywords:
- Topological Sort, Kahn's Algorithm, Indegree, BFS, Directed Acyclic Graph (DAG).

🗒️ Notes
- The input format is [course, prerequisite]. The graph edge must be drawn from
  the prerequisite to the course.
-------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    /**
     * @brief Finds a valid order of courses to take to finish all courses.
     * @param n The total number of courses (0 to n-1).
     * @param prerequisites A vector of pairs [course, prerequisite].
     * @return A vector representing a valid course order, or an empty vector if impossible.
     */
    vector<int> findOrder(int n, vector<vector<int>> &prerequisites)
    {
        vector<vector<int>> adj(n);
        vector<int> indegree(n, 0);

        // Step 1: Build adjacency list and indegree array
        // Input: [v, u] (take v after u). Edge: u -> v
        for (auto &e : prerequisites)
        {
            int v = e[0]; // Course to take (destination)
            int u = e[1]; // Prerequisite (source)
            adj[u].push_back(v);
            indegree[v]++;
        }

        queue<int> q;
        // Step 2: Start with courses having no prerequisites (indegree 0)
        for (int i = 0; i < n; ++i)
            if (indegree[i] == 0)
                q.push(i);

        vector<int> topo; // The resulting course order

        // Step 3: Process BFS (Kahn's Algorithm)
        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            topo.push_back(u);

            // Process all dependent courses (neighbors)
            for (int v : adj[u])
            {
                indegree[v]--;
                // If a course's prerequisites are all met, it can be taken next
                if (indegree[v] == 0)
                    q.push(v);
            }
        }

        // Step 4: Cycle Check
        // If the number of courses in the topological order is less than N, a cycle exists
        if (topo.size() != n)
            return {}; // Impossible to complete all courses

        return topo;
    }
};

// Helper function to print a vector
template <typename T>
void printVector(const vector<T> &vec)
{
    cout << "[";
    for (size_t i = 0; i < vec.size(); ++i)
    {
        cout << vec[i];
        if (i < vec.size() - 1)
        {
            cout << ", ";
        }
    }
    cout << "]";
}

int main()
{
    Solution sol;

    cout << "--- Course Schedule (Topological Sort) ---\n";

    // Test Case 1: Valid linear order
    // Courses: 4. Prereqs: [1, 0], [2, 1], [3, 2]. Order: 0 -> 1 -> 2 -> 3
    int N1 = 4;
    vector<vector<int>> prereqs1 = {{1, 0}, {2, 1}, {3, 2}};
    vector<int> result1 = sol.findOrder(N1, prereqs1);
    cout << "Test 1 | N=4. Prereqs: [[1, 0], [2, 1], [3, 2]]\n";
    cout << "Result: ";
    printVector(result1);
    cout << " (Expected: [0, 1, 2, 3])\n";
    cout << "--------------------------------\n";

    // Test Case 2: Valid complex order (multiple possible orders)
    // Courses: 4. Prereqs: [1, 0], [0, 2], [3, 1]. Graph: 2 -> 0 -> 1 -> 3
    int N2 = 4;
    vector<vector<int>> prereqs2 = {{1, 0}, {0, 2}, {3, 1}};
    vector<int> result2 = sol.findOrder(N2, prereqs2);
    cout << "Test 2 | N=4. Prereqs: [[1, 0], [0, 2], [3, 1]]\n";
    cout << "Result: ";
    printVector(result2);
    // 2 (indegree 0) -> 0 (indegree 1) -> 1 (indegree 1) -> 3 (indegree 0)
    // Start with 2. Then 0. Then 1. Then 3.
    cout << " (Expected: [2, 0, 1, 3] or similar valid order)\n";
    cout << "--------------------------------\n";

    // Test Case 3: Impossible (Cycle)
    // Courses: 2. Prereqs: [1, 0], [0, 1]. Graph: 0 <-> 1
    int N3 = 2;
    vector<vector<int>> prereqs3 = {{1, 0}, {0, 1}};
    vector<int> result3 = sol.findOrder(N3, prereqs3);
    cout << "Test 3 | N=2. Prereqs: [[1, 0], [0, 1]] (Cycle)\n";
    cout << "Result: ";
    printVector(result3);
    cout << " (Expected: [])\n";
    cout << "--------------------------------\n";

    // Test Case 4: Disconnected components
    // Courses: 5. Prereqs: [1, 0], [4, 3]. Graph: 0->1, 3->4, 2 isolated.
    int N4 = 5;
    vector<vector<int>> prereqs4 = {{1, 0}, {4, 3}};
    vector<int> result4 = sol.findOrder(N4, prereqs4);
    cout << "Test 4 | N=5. Prereqs: [[1, 0], [4, 3]]. Disconnected.\n";
    cout << "Result: ";
    printVector(result4);
    cout << " (Expected: [0, 3, 2, 1, 4] or similar valid order)\n";
    cout << "--------------------------------\n";

    return 0;
}
