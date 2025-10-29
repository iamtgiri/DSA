/*
File: Shortest_path_in_DAG.cpp
Date: 2025-10-30 01:44

Problem: Shortest path in Directed Acyclic Graph

Link: https://www.geeksforgeeks.org/problems/shortest-path-in-undirected-graph/1

Problem Statement:
Given a weighted, directed acyclic graph (DAG) and a source node (src),
find the shortest distance from the source node to all other nodes.
If a node is unreachable, return -1 for its distance.

-------------------------------------------------
❌ Brute Force
- Idea: DFS or recursive exploration of all paths from the source to every
  other node, tracking the minimum distance.
- Time complexity: O(V!) or exponential in the worst case (e.g., dense DAG).
- Space complexity: O(V) for recursion stack and distance tracking.
- Limitations: Inefficient due to massive redundant calculations.

✅ Optimized Approachs
- Idea: Since the graph is a **DAG**, we can process nodes in a **Topological Order**.
  By processing a node $u$ only after all its predecessors have been processed,
  we ensure that when we relax the edges outgoing from $u$, the distance $\text{dist}[u]$
  is already the shortest possible distance from the source. This is the fastest
  known method for SSSP in a DAG.
- Approach: **Topological Sort followed by Distance Relaxation**.
- Algorithm:
    1. **Adjacency List & Topo Sort Setup:** Build the directed, weighted adjacency list.
       Use Kahn's Algorithm (based on in-degrees and a queue) to determine the
       Topological Sort order.
    2. **Initialization:** Initialize a distance array `dist[V]` with `INT_MAX`
       (representing infinity) and set `dist[src] = 0$.
    3. **Relaxation in Order:** Iterate through the nodes in the Topological Sort order.
       For each node $u$, check if $\text{dist}[u]$ is reachable (`!= INT_MAX`). If so,
       relax all outgoing edges $(u, v)$ with weight $w$:
       $\text{dist}[v] = \min(\text{dist}[v], \text{dist}[u] + w)$.
    4. **Final Result:** Replace any remaining `INT_MAX` values in the distance array with $-1$.
- Time complexity: **O(V + E)**. Topological sort takes $O(V+E)$, and the
  subsequent relaxation phase iterates over every edge exactly once, also $O(V+E)$.
- Space complexity: **O(V + E)** for the adjacency list, in-degree array, queue,
  Topological Sort array, and distance array.

💡 Key Pattern:
- **Shortest Path in DAG (SSSP):** Always use Topological Sort + Relaxation for $O(V+E)$ speed.

ℹ️ Keywords:
- Directed Acyclic Graph (DAG), Topological Sort, Kahn's Algorithm, Relaxation,
  Single Source Shortest Path (SSSP), Directed Weighted Graph.

🗒️ Notes
- This approach works for graphs with **negative weights** as long as there are
  no negative cycles (which is guaranteed in a DAG). Dijkstra's cannot handle
  negative weights, making this method superior for DAGs.
-------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    /**
     * @brief Computes the shortest path distance from a source node to all other
     * nodes in a weighted Directed Acyclic Graph (DAG) using Topological Sort.
     * @param V The number of vertices.
     * @param E The number of edges (used for problem signature, not explicitly needed internally).
     * @param edges A vector of triplets {u, v, w} representing a directed edge
     * from u to v with weight w.
     * @return A vector of integers representing the shortest distance from node 0
     * to every other node. Unreachable nodes are represented by -1.
     */
    vector<int> shortestPath(int V, int E, vector<vector<int>> &edges)
    {
        // Source is implicitly node 0 based on problem constraints/typical implementation
        int src = 0;

        // Adjacency list: adj[u] = {{v, w}, ...}
        vector<vector<pair<int, int>>> adj(V);
        for (auto &e : edges)
        {
            int u = e[0], v = e[1], w = e[2];
            // Graph is directed
            adj[u].push_back({v, w});
        }

        // --- Step 1: Topological Sort (Kahn's Algorithm) ---

        // In-degree array for Kahn's algorithm
        vector<int> indeg(V, 0);
        for (int u = 0; u < V; ++u)
            for (auto [v, w] : adj[u])
                indeg[v]++;

        queue<int> q;
        for (int i = 0; i < V; ++i)
            if (indeg[i] == 0)
                q.push(i);

        vector<int> topo;
        while (!q.empty())
        {
            int node = q.front();
            q.pop();
            topo.push_back(node);

            // Decrement in-degree of neighbors
            for (auto [v, w] : adj[node])
                if (--indeg[v] == 0)
                    q.push(v);
        }

        // --- Step 2: Relax Edges in Topological Order ---

        // Initialize distances to infinity
        vector<int> dist(V, INT_MAX);
        dist[src] = 0;

        for (int u : topo)
        {
            // Only relax edges from reachable nodes
            if (dist[u] != INT_MAX)
            {
                for (auto [v, w] : adj[u])
                {
                    // Relaxation step
                    if (dist[u] + w < dist[v])
                        dist[v] = dist[u] + w;
                }
            }
        }

        // --- Step 3: Replace INF with -1 for unreachable nodes ---
        for (int i = 0; i < V; ++i)
            if (dist[i] == INT_MAX)
                dist[i] = -1;

        return dist;
    }
};

// Helper function to print a vector of integers
void printVector(const vector<int> &vec)
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

    cout << "--- Shortest Path in Directed Acyclic Graph (DAG) ---\n";

    // Test Case 1: Simple Directed Path
    // Graph: 0 -> 1 (2), 1 -> 2 (3), 0 -> 2 (6). Source=0
    // Topo order: 0, 1, 2 (or 0, 2, 1)
    // Shortest Path to 2: 0->1->2 (2+3=5) is shorter than 0->2 (6)
    int V1 = 3, E1 = 3;
    vector<vector<int>> edges1 = {{0, 1, 2}, {1, 2, 3}, {0, 2, 6}};
    // Expected: [0, 2, 5]
    vector<int> res1 = sol.shortestPath(V1, E1, edges1);
    cout << "Test 1 | V=" << V1 << ", Edges: 0->1(2), 1->2(3), 0->2(6)\n";
    cout << "Result: ";
    printVector(res1);
    cout << " (Expected: [0, 2, 5])\n";
    cout << "--------------------------------\n";

    // Test Case 2: Disconnected Component and Unreachable Node
    // Graph: 1 -> 2 (10), 0 -> 3 (5), 3 -> 4 (1), 4 -> 2 (2). Source=0
    // Node 1 is unreachable from 0.
    // Shortest paths from 0:
    // 0: 0
    // 1: -1 (Unreachable)
    // 2: 0->3->4->2 (5+1+2=8). Note: 1->2 is 10, but 1 is unreachable.
    // 3: 5 (0->3)
    // 4: 6 (0->3->4)
    int V2 = 5, E2 = 4;
    vector<vector<int>> edges2 = {{1, 2, 10}, {0, 3, 5}, {3, 4, 1}, {4, 2, 2}};
    // Expected: [0, -1, 8, 5, 6]
    vector<int> res2 = sol.shortestPath(V2, E2, edges2);
    cout << "Test 2 | V=" << V2 << ", Edges: Disconnected. 0->3->4->2. Node 1 is src=0\n";
    cout << "Result: ";
    printVector(res2);
    cout << " (Expected: [0, -1, 8, 5, 6])\n";
    cout << "--------------------------------\n";

    // Test Case 3: Graph with longer paths from node 0 to a node via another node (negative weight example, demonstrating DAG strength)
    // Graph: 0 -> 1 (5), 0 -> 2 (3), 1 -> 3 (4), 2 -> 3 (10), 1 -> 4 (2), 4 -> 5 (-1)
    // Node 5 is reachable. Source=0
    // Path to 3: 0->1->3 (5+4=9). 0->2->3 (3+10=13). Shortest to 3 is 9.
    // Path to 5: 0->1->4->5 (5+2-1=6)
    int V3 = 6, E3 = 6;
    vector<vector<int>> edges3 = {{0, 1, 5}, {0, 2, 3}, {1, 3, 4}, {2, 3, 10}, {1, 4, 2}, {4, 5, -1}};
    // Expected: [0, 5, 3, 9, 7, 6]
    vector<int> res3 = sol.shortestPath(V3, E3, edges3);
    cout << "Test 3 | V=" << V3 << ", Edges: Includes a negative weight (-1) on 4->5\n";
    cout << "Result: ";
    printVector(res3);
    cout << " (Expected: [0, 5, 3, 9, 7, 6])\n";
    cout << "--------------------------------\n";

    return 0;
}
