/*
File: Prerequisite_Tasks.cpp
Date: 2025-10-26 11:16

Problem: Prerequisite Tasks
Link: https://www.geeksforgeeks.org/problems/prerequisite-tasks/1

Problem Statement:
Given N tasks, labeled from 0 to N-1, and P prerequisites where a pair (task,
prerequisite) means that the task can only be performed if the prerequisite is
already completed. Determine if it is possible to complete all tasks.

-------------------------------------------------
❌ Brute Force
- Idea: Try every permutation of the N tasks and check if any permutation
  satisfies all P prerequisite conditions.
- Time complexity: O(N! * P).
- Space complexity: O(N) to store the permutation.
- Limitations: Factorial complexity is too slow for even small N.

✅ Optimized Approachs
- Idea: The tasks can be completed if and only if the dependency graph contains
  no circular dependencies (i.e., no cycles). This is a cycle detection problem
  in a directed graph.
- Approach: Depth-First Search (DFS) with state tracking.
- Algorithm:
    1. **Build Graph:** Construct a directed graph where an edge $B \rightarrow A$
       represents that task $B$ must be completed before task $A$. (Note: Based
       on the input structure $\langle task, prerequisite \rangle$, the edge is
       drawn from the prerequisite to the task).
    2. **State Tracking:** Use two boolean arrays:
       - `vis`: Global visited marker (was this node ever processed?).
       - `rec`: Recursion stack marker (is this node currently in the DFS path?).
    3. **DFS Cycle Check:** Traverse all unvisited nodes. If DFS enters a node
       that is already marked in the `rec` stack, a **cycle** is found.
    4. **Result:** If any cycle is found, return `false`. If all tasks are
       traversed without finding a cycle, return `true`.
- Time complexity: O(N + P). Linearly proportional to the number of vertices (N)
  plus the number of edges (P).
- Space complexity: O(N + P) for the adjacency list and O(N) for the DFS state
  arrays.

💡 Key Pattern:
- **Topological Sort / Cycle Detection:** Scheduling and dependency problems in
  directed graphs are solved by checking for DAG property.

ℹ️ Keywords:
- Directed Graph, Cycle Detection, DFS, Topological Sort, Prerequisite.

🗒️ Notes
- The implementation uses DFS to detect back edges (an edge to a node currently
  on the recursion stack), which immediately indicates a cycle.
-------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    /**
     * @brief DFS function to detect a cycle starting from 'node'.
     * @param node The current task (node) being visited.
     * @param adj The adjacency list (prerequisite -> task).
     * @param vis Global visited array.
     * @param rec Recursion stack array.
     * @return true if a cycle is found, false otherwise.
     */
    bool dfs(int node, vector<vector<int>> &adj, vector<bool> &vis, vector<bool> &rec)
    {
        vis[node] = true; // Mark as visited globally
        rec[node] = true; // Mark as currently in the recursion stack

        for (int nei : adj[node])
        {
            if (!vis[nei])
            {
                // Neighbor not visited: continue DFS
                if (dfs(nei, adj, vis, rec))
                    return true;
            }
            // Neighbor visited AND in the current recursion stack: CYCLE FOUND
            else if (rec[nei])
            {
                return true;
            }
        }

        // Backtrack: Remove node from recursion stack
        rec[node] = false;
        return false;
    }

    /**
     * @brief Checks if all tasks can be completed without circular dependencies.
     * @param N The total number of tasks (0 to N-1).
     * @param P The number of prerequisite pairs.
     * @param prerequisites Vector of {task, prerequisite} pairs.
     * @return true if possible, false otherwise.
     */
    bool isPossible(int N, int P, vector<pair<int, int>> &prerequisites)
    {
        // adj[i] holds all tasks that i is a prerequisite for (i -> task)
        vector<vector<int>> adj(N);
        for (auto e : prerequisites)
        {
            // Edge from prerequisite (e.second) to task (e.first)
            adj[e.second].push_back(e.first);
        }

        vector<bool> vis(N, false); // Global visited status
        vector<bool> rec(N, false); // Recursion stack status

        // Iterate through all tasks to ensure all components are checked
        for (int i = 0; i < N; ++i)
        {
            // If the node hasn't been visited and DFS finds a cycle, return false
            if (!vis[i] && dfs(i, adj, vis, rec))
            {
                return false;
            }
        }

        // No cycle found
        return true;
    }
};

// Helper function to print boolean result
string boolToString(bool b)
{
    return b ? "true (Possible)" : "false (Impossible)";
}

int main()
{
    Solution sol;

    cout << "--- Prerequisite Tasks (Cycle Detection) ---\n";

    // Test Case 1: Linear dependency (No cycle)
    // 3 tasks. (1 requires 0), (2 requires 1). Graph: 0 -> 1 -> 2
    int N1 = 3, P1 = 2;
    vector<pair<int, int>> prereqs1 = {{1, 0}, {2, 1}};
    bool result1 = sol.isPossible(N1, P1, prereqs1);
    cout << "Test 1 | N=3, P=2. Prereqs: (1 requires 0), (2 requires 1)\n";
    cout << "Result: " << boolToString(result1) << " (Expected: true)\n";
    cout << "--------------------------------\n";

    // Test Case 2: Circular dependency (Cycle 0->1->0)
    // 2 tasks. (1 requires 0), (0 requires 1). Graph: 0 <-> 1
    int N2 = 2, P2 = 2;
    vector<pair<int, int>> prereqs2 = {{1, 0}, {0, 1}};
    bool result2 = sol.isPossible(N2, P2, prereqs2);
    cout << "Test 2 | N=2, P=2. Prereqs: (1 requires 0), (0 requires 1)\n";
    cout << "Result: " << boolToString(result2) << " (Expected: false)\n";
    cout << "--------------------------------\n";

    // Test Case 3: Complex Cycle
    // 4 tasks. (1 requires 0), (2 requires 1), (0 requires 2). Graph: 0->1->2->0 (Cycle)
    int N3 = 4, P3 = 3;
    vector<pair<int, int>> prereqs3 = {{1, 0}, {2, 1}, {0, 2}};
    bool result3 = sol.isPossible(N3, P3, prereqs3);
    cout << "Test 3 | N=4, P=3. Prereqs: (1 req 0), (2 req 1), (0 req 2)\n";
    cout << "Result: " << boolToString(result3) << " (Expected: false)\n";
    cout << "--------------------------------\n";

    // Test Case 4: Disconnected components (Possible)
    // 4 tasks. (1 requires 0). (2 and 3 are independent). Graph: 0->1, 2, 3
    int N4 = 4, P4 = 1;
    vector<pair<int, int>> prereqs4 = {{1, 0}};
    bool result4 = sol.isPossible(N4, P4, prereqs4);
    cout << "Test 4 | N=4, P=1. Prereqs: (1 requires 0). Others independent.\n";
    cout << "Result: " << boolToString(result4) << " (Expected: true)\n";
    cout << "--------------------------------\n";

    return 0;
}
