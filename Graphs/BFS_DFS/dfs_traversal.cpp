/*
File: dfs_traversal.cpp
Date: 2025-10-13 14:58

Problem: DFS Traversal
Link: https://www.geeksforgeeks.org/problems/depth-first-traversal-for-a-graph/1

Problem Statement:
Given a graph (represented by an adjacency list) and a starting node, traverse all
reachable nodes using the Depth-First Search (DFS) algorithm and return the order
in which the nodes are visited.

-------------------------------------------------
❌ Brute Force (N/A)
- Idea: DFS is already an efficient graph traversal technique. Any "brute force"
  would involve redundant operations, but the core time complexity $O(V+E)$ is optimal.
- Time complexity: N/A
- Space complexity: N/A
- Limitations: N/A

✅ Optimized Approachs
- Idea: **Depth-First Search (DFS)**. Explore branches as deeply as possible before
  backtracking. This is typically implemented using recursion or an explicit stack.
- Approach: **Recursive and Iterative Implementations**.
- Algorithm (General):
    1. Start at a given vertex $s$.
    2. Mark $s$ as visited and add it to the result list.
    3. For every unvisited neighbor $v$ of $s$, recursively (or iteratively via stack)
       call the traversal function on $v$.
- Time complexity: **O(V + E)**. Every vertex is visited once, and every edge is examined once.
- Space complexity: **O(V)**. Required for the visited array and the recursion stack (or explicit stack), which in the worst case can hold all $V$ vertices (e.g., a line graph).

💡 Key Pattern:
- **LIFO Exploration:** DFS utilizes a Last-In, First-Out (LIFO) structure (stack/recursion)
  to prioritize the deepest nodes in the path before exploring sibling branches.

ℹ️ Keywords:
- Depth-First Search, Graph Traversal, Stack, Recursion, Adjacency List

🗒️ Notes
- The problem provides both a recursive approach (clean and idiomatic) and an iterative
  approach (avoids stack overflow for very deep graphs). Both yield the same traversal order.
- In the iterative approach, neighbors must be pushed onto the stack in **reverse order** of processing preference (or the adjacency list order) to ensure the LIFO behavior
  matches the path of the recursive version.
-------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    // --- Recursive DFS Implementation ---

    /**
     * @brief Initiates the recursive Depth-First Traversal from node 0.
     * @param adj The adjacency list of the graph.
     * @return A vector<int> containing the nodes in the order they were visited.
     */
    vector<int> dfsRecursive(vector<vector<int>> &adj)
    {
        if (adj.empty())
            return {};
        int V = adj.size();
        // Assuming V vertices, starting from node 0.
        vector<bool> visited(V, false);
        vector<int> result;

        // Start DFS from vertex 0 (Assuming a connected graph or only interested in the component of 0)
        dfsRec(adj, visited, 0, result);
        return result;
    }

private:
    /**
     * @brief Helper function for recursive DFS.
     * @param adj The adjacency list.
     * @param visited Array to track visited nodes.
     * @param s The current node.
     * @param res The vector to store the traversal result.
     */
    void dfsRec(vector<vector<int>> &adj, vector<bool> &visited, int s, vector<int> &res)
    {
        visited[s] = true;
        res.push_back(s); // Visit node when first entered

        // Recur for all unvisited neighbors
        for (int i : adj[s])
            if (visited[i] == false)
                dfsRec(adj, visited, i, res);
    }

public:
    // --- Iterative DFS Implementation (using explicit stack) ---

    /**
     * @brief Performs iterative Depth-First Traversal using an explicit stack from node 0.
     * @param adj The adjacency list of the graph.
     * @return A vector<int> containing the nodes in the order they were visited.
     */
    vector<int> dfsIterative(vector<vector<int>> &adj)
    {
        if (adj.empty())
            return {};
        int V = adj.size();
        vector<bool> visited(V, false);
        vector<int> result;
        stack<int> s;

        // Start from node 0
        int startNode = 0;

        s.push(startNode);
        visited[startNode] = true;

        while (!s.empty())
        {
            int u = s.top();
            s.pop();

            // The node is "visited" (added to result) when it is popped from the stack.
            // Note: If you add to result when pushing, the order will be slightly different
            // but still a valid traversal. Popping typically yields the classic DFS discovery order.
            result.push_back(u);

            // Iterate over neighbors in reverse order.
            // This ensures that the neighbor with the smallest index (which would be visited
            // first in the recursive call) is the LAST one pushed, and thus the FIRST one POPPED
            // (LIFO), preserving the canonical DFS order.
            for (int i = adj[u].size() - 1; i >= 0; --i)
            {
                int v = adj[u][i];
                if (!visited[v])
                {
                    visited[v] = true;
                    s.push(v);
                }
            }
        }

        return result;
    }
};

int main()
{
    Solution sol;

    // Example Graph (Undirected):
    // V=6, Edges: 0-1, 0-2, 1-3, 1-4, 2-5
    // Graph Structure:
    // 0 is connected to 1 and 2
    // 1 is connected to 0, 3, and 4
    // 2 is connected to 0, 5

    // Setup adjacency list
    vector<vector<int>> adj(6);
    auto addEdge = [&](int u, int v)
    {
        adj[u].push_back(v);
        adj[v].push_back(u);
    };

    addEdge(0, 1);
    addEdge(0, 2);
    addEdge(1, 3);
    addEdge(1, 4);
    addEdge(2, 5);

    // IMPORTANT: Sort neighbors for deterministic traversal order
    // (ensures recursive and iterative results match)
    for (auto &neighbors : adj)
    {
        sort(neighbors.begin(), neighbors.end());
    }

    // Expected DFS Traversal (Start at 0, neighbors sorted ascending: [1, 2]):
    // Recursive Path: 0 -> 1 (neighbors 3, 4) -> 3 -> 4 -> 2 -> 5
    // Output: {0, 1, 3, 4, 2, 5}

    cout << "--- DFS Traversal on Undirected Graph (Starting at 0) ---" << endl;
    cout << "Graph Edges: 0-1, 0-2, 1-3, 1-4, 2-5" << endl;

    // Test 1: Recursive DFS
    vector<int> resRec = sol.dfsRecursive(adj);
    cout << "\nRecursive DFS Result: {";
    for (size_t i = 0; i < resRec.size(); ++i)
    {
        cout << resRec[i] << (i == resRec.size() - 1 ? "" : ", ");
    }
    cout << "} (Expected: {0, 1, 3, 4, 2, 5})" << endl;

    // Test 2: Iterative DFS
    vector<int> resIte = sol.dfsIterative(adj);
    cout << "Iterative DFS Result: {";
    for (size_t i = 0; i < resIte.size(); ++i)
    {
        cout << resIte[i] << (i == resIte.size() - 1 ? "" : ", ");
    }
    cout << "} (Expected: {0, 1, 3, 4, 2, 5})" << endl;

    return 0;
}
