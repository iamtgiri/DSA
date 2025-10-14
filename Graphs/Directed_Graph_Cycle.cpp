/*
File: Directed_Graph_Cycle.cpp
Date: 2025-10-14 18:48

Problem: Directed Graph Cycle

Link: https://www.geeksforgeeks.org/problems/detect-cycle-in-a-directed-graph/1

Problem Statement:
Given a directed graph with V vertices and E edges, determine whether a cycle
exists in the graph.

Example:
Input: V=4, Edges=[[0,1],[0,2],[1,2],[2,3]]
Output: false (No cycle)
Input: V=4, Edges=[[0,1],[1,2],[2,3],[3,1]]
Output: true (Cycle 1 -> 2 -> 3 -> 1)
----------------------------------------------------------------------------------
❌ Brute Force
- Idea: Try to enumerate all possible simple paths in the graph up to V vertices
  long and check if any path starts and ends at the same vertex.
- Time complexity: Exponential, highly inefficient, potentially O(V!).
- Space complexity: O(V + E) for storing the graph structure.
- Limitations: Infeasible for any graph with more than a handful of vertices.

✅ Optimized Approach
- Idea: Use Depth First Search (DFS) and track nodes currently in the recursion
  path (recursion stack). A back edge to a node in the recursion stack indicates
  a cycle.
- Approach: Depth First Search (DFS) with state tracking.
- Algorithm:
  1. Use two arrays: `visited` (node has been seen) and `recStack` (node is in
     the current DFS path).
  2. For each unvisited node, call DFS.
  3. Inside DFS, mark the current node as visited and set `recStack` to true.
  4. If a neighbor is found to be true in `recStack`, a cycle exists.
  5. If the node finishes its traversal, unset `recStack` (backtrack).
- Time complexity: O(V + E). Every vertex and edge is processed exactly once.
- Space complexity: O(V) for the `visited` and `recStack` arrays, plus O(V) for
  the recursion stack.

💡 Key Pattern:
- Cycle detection in directed graphs: Use DFS with a recursion stack tracker.
- Cycle detection in undirected graphs: Use DFS and check for edges to an
  already-visited node, excluding the parent node.

ℹ️ Keywords:
- DFS, Directed Graph, Cycle Detection, Back Edge, Recursion Stack

🗒️ Notes
- The difference between `visited` and `recStack` is crucial: `visited` prevents
  re-processing components; `recStack` detects cycles within a component.
----------------------------------------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    /**
     * @brief Recursive DFS helper to detect a cycle in the current path.
     * @param node The current vertex being visited.
     * @param adj The adjacency list of the graph.
     * @param visited Array to track if a node has ever been visited (globally).
     * @param recStack Array to track if a node is currently in the recursion stack (locally).
     * @return True if a cycle is detected, false otherwise.
     */
    bool dfs(int node, vector<vector<int>> &adj, vector<int> &visited, vector<int> &recStack)
    {
        // Mark the current node as globally visited and part of the current path
        visited[node] = 1;
        recStack[node] = 1;

        for (int nei : adj[node])
        {
            if (!visited[nei])
            {
                // If unvisited, recurse
                if (dfs(nei, adj, visited, recStack))
                    return true;
            }
            else if (recStack[nei])
            {
                // If visited AND still in the current recursion stack (recStack is 1)
                // then a back edge is found, indicating a cycle.
                return true;
            }
        }

        // Backtrack: remove the node from the current recursion path
        recStack[node] = 0;
        return false;
    }

    /**
     * @brief Checks if the directed graph contains any cycle.
     * @param V The number of vertices in the graph.
     * @param edges A list of edges in the format [[u, v], ...].
     * @return True if a cycle exists, false otherwise.
     */
    bool isCyclic(int V, vector<vector<int>> &edges)
    {
        // Convert edge list into adjacency list representation
        vector<vector<int>> adj(V);
        for (auto &e : edges)
            adj[e[0]].push_back(e[1]);

        // visited: 0 (unvisited), 1 (visited)
        // recStack: 0 (not in current path), 1 (in current path)
        vector<int> visited(V, 0), recStack(V, 0);

        // Check every node, ensuring all disconnected components are covered
        for (int i = 0; i < V; i++)
        {
            if (!visited[i])
            {
                if (dfs(i, adj, visited, recStack))
                    return true;
            }
        }
        return false;
    }
};

int main()
{
    Solution sol;

    // --- Test Case 1: Graph with a Cycle (0 -> 1 -> 2 -> 0)
    int V1 = 3;
    vector<vector<int>> edges1 = {{0, 1}, {1, 2}, {2, 0}};
    bool result1 = sol.isCyclic(V1, edges1);
    cout << "Graph 1 (Cycle: 0-1-2-0): " << (result1 ? "True" : "False") << endl;
    // Expected: True

    // --- Test Case 2: Graph without a Cycle (Topological sort possible)
    int V2 = 4;
    vector<vector<int>> edges2 = {{0, 1}, {0, 2}, {1, 3}, {2, 3}};
    bool result2 = sol.isCyclic(V2, edges2);
    cout << "Graph 2 (Acyclic): " << (result2 ? "True" : "False") << endl;
    // Expected: False

    // --- Test Case 3: Graph with a self-loop (a simple cycle)
    int V3 = 2;
    vector<vector<int>> edges3 = {{0, 0}};
    bool result3 = sol.isCyclic(V3, edges3);
    cout << "Graph 3 (Self-loop 0-0): " << (result3 ? "True" : "False") << endl;
    // Expected: True

    return 0;
}
