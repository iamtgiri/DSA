/*
File: Topological_sort.cpp
Date: 2025-10-16 17:55

Problem: Topological sort
Link: https://www.geeksforgeeks.org/problems/topological-sort/1

Problem Statement:
Given a Directed Acyclic Graph (DAG) with V vertices and E edges, find a
topological sorting of the graph. A topological sort is a linear ordering of
its vertices such that for every directed edge from node u to node v, u comes
before v in the ordering.

----------------------------------------------------------------------------------
❌ Brute Force
- Idea: Iterating through all possible permutations of vertices and checking if
  any permutation satisfies the topological ordering criteria (i.e., for every
  edge u -> v, u appears before v in the permutation).
- Time complexity: O(V! * E). Highly inefficient due to checking every permutation.
- Space complexity: O(V) to store the current permutation.
- Limitations: Completely infeasible for graphs with more than a few nodes.

✅ Optimized Approachs
- Idea: Topological sort can be found by ensuring that we visit a node only
  after all its prerequisites (incoming nodes) have been visited.
- Approach: Depth First Search (DFS) or Kahn's Algorithm (BFS). This solution
  uses DFS.
- Algorithm (DFS):
  1. Initialize `visited` array and a `stack` to store the result.
  2. Iterate through all nodes (0 to V-1). If a node is unvisited, start a DFS
     from that node.
  3. The DFS function:
     a. Mark the current node as visited.
     b. Recursively call DFS for all adjacent neighbors.
     c. After all recursive calls return (meaning all dependencies of the current
        node are processed), push the current node onto the result stack.
  4. Finally, pop all elements from the stack to get the topological order. The
     stack automatically holds the nodes in reverse topological order (post-order
     of DFS finish times).
- Time complexity: O(V + E). The time complexity is dominated by traversing all
  vertices (V) and all edges (E) exactly once.
- Space complexity: O(V + E) for the adjacency list and O(V) for the visited
  array and the recursion stack/result stack. Total space complexity is O(V + E).

💡 Key Pattern:
- **DFS Post-Order:** In a DAG, the finish time of a node (the time it's popped
  off the recursion stack) determines its position. Placing nodes onto a stack
  upon completion (post-order) yields the reverse topological sort.

ℹ️ Keywords:
- Directed Acyclic Graph (DAG), DFS, Post-Order Traversal, Stack, Ordering, Prerequisites

🗒️ Notes
- If the graph contains a cycle, no topological sort exists. This DFS approach
  will still return a result, but it won't be a true topological sort. A cycle
  detection step is typically required before or during topological sort.
----------------------------------------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution
{
private:
    /**
     * @brief Performs DFS and pushes the node to the stack upon completion
     * (post-order traversal).
     * @param adj The adjacency list of the graph.
     * @param node The current node being visited.
     * @param visited Boolean array to track visited nodes.
     * @param s Stack to store the nodes in reverse topological order.
     */
    void dfs(const vector<vector<int>> &adj, int node, vector<bool> &visited, stack<int> &s)
    {
        // No need to check visited[node] here if the call site handles it,
        // but it's safe to keep for robust recursion termination.
        if (visited[node])
            return;

        visited[node] = true;

        // Visit all neighbors
        for (auto nei : adj[node])
            if (!visited[nei])
                dfs(adj, nei, visited, s);

        // Push the node onto the stack only after all its dependencies are processed.
        s.push(node);
    }

public:
    /**
     * @brief Computes the topological sort of a Directed Acyclic Graph (DAG) using DFS.
     * @param V The number of vertices (0 to V-1).
     * @param edges A vector of pairs [u, v] representing a directed edge from u to v.
     * @return A vector representing one possible topological ordering of the vertices.
     */
    vector<int> topoSort(int V, vector<vector<int>> &edges)
    {
        // 1. Build Adjacency List
        vector<vector<int>> adj(V);
        for (auto e : edges)
            adj[e[0]].push_back(e[1]);

        stack<int> s;
        vector<bool> visited(V, false);

        // 2. Iterate through all nodes to handle disconnected components
        for (int i = 0; i < V; ++i)
            if (!visited[i])
                dfs(adj, i, visited, s);

        // 3. Extract Result from Stack (reversing the post-order)
        vector<int> result;
        result.reserve(V);
        while (!s.empty())
        {
            result.push_back(s.top());
            s.pop();
        }
        return result;
    }
};

/**
 * @brief Helper function to print the result vector.
 */
void printResult(const vector<int> &result)
{
    for (int node : result)
    {
        cout << node << " ";
    }
    cout << endl;
}

int main()
{
    Solution sol;

    // Test Case 1: Standard Example (V=6, E=6)
    // Edges: 5->2, 5->0, 4->0, 4->1, 2->3, 3->1
    // Graph:
    // 5 -> 2 -> 3 -> 1
    // |    /
    // V   /
    // 0 <- 4 -> 1
    // Expected sort (one of many): 5 4 2 3 0 1 or 4 5 2 3 0 1
    int V1 = 6;
    vector<vector<int>> edges1 = {{5, 2}, {5, 0}, {4, 0}, {4, 1}, {2, 3}, {3, 1}};
    vector<int> result1 = sol.topoSort(V1, edges1);
    cout << "--- Test Case 1 (Standard DAG) ---" << endl;
    cout << "Vertices (V): " << V1 << endl;
    cout << "Topological Sort: ";
    printResult(result1);

    // Test Case 2: Simple Chain (V=4, E=3)
    // Edges: 0->1, 1->2, 2->3
    // Expected sort: 0 1 2 3
    int V2 = 4;
    vector<vector<int>> edges2 = {{0, 1}, {1, 2}, {2, 3}};
    vector<int> result2 = sol.topoSort(V2, edges2);
    cout << "--- Test Case 2 (Chain) ---" << endl;
    cout << "Vertices (V): " << V2 << endl;
    cout << "Topological Sort: ";
    printResult(result2);

    // Test Case 3: Disconnected Components (V=5, E=2)
    // Edges: 0->1, 2->3. Node 4 is isolated.
    // Expected sort (one of many): 4 2 3 0 1
    int V3 = 5;
    vector<vector<int>> edges3 = {{0, 1}, {2, 3}};
    vector<int> result3 = sol.topoSort(V3, edges3);
    cout << "--- Test Case 3 (Disconnected) ---" << endl;
    cout << "Vertices (V): " << V3 << endl;
    cout << "Topological Sort: ";
    printResult(result3);

    return 0;
}
