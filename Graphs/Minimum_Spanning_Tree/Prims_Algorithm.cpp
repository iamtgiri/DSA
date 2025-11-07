/*
File: Prims_Algorithm.cpp
Date: 2025-11-07 10:59

Problem: Minimum Spanning Tree
Link: https://www.geeksforgeeks.com/problems/minimum-spanning-tree/1

Problem Statement:
Given a weighted, connected, undirected graph with V vertices and E edges,
find the sum of weights of the edges of a Minimum Spanning Tree (MST).

-------------------------------------------------
❌ Brute Force
- Idea: Examine every possible spanning tree of the graph. A spanning tree is a
  subgraph that connects all vertices with V-1 edges and contains no cycles. For
  each candidate spanning tree, calculate the sum of its edge weights.
- Time complexity: Highly inefficient, generally exponential, $O(E^{V-1} \cdot V)$
  in the worst case for dense graphs, as the number of possible spanning trees is vast.
- Space complexity: O(V + E).
- Limitations: Impractical for any graph of meaningful size due to exponential time
  complexity.

✅ Optimized Approachs
- Idea: **Prim's Algorithm** is a greedy algorithm that builds the MST incrementally.
  It starts at an arbitrary vertex and repeatedly adds the minimum-weight edge that
  connects a vertex already in the MST to a vertex not yet in the MST.
- Approach: **Prim's Algorithm using a Priority Queue (Min-Heap)**.
- Algorithm:
  1. Initialize a Priority Queue (min-heap) to store (weight, node).
  2. Start by pushing (0, start_node) into the PQ.
  3. Maintain a boolean array 'vis' (visited) to track nodes included in the MST.
  4. While the PQ is not empty:
     a. Extract the edge with the minimum weight (w, node).
     b. If 'node' is already visited, continue (this handles redundant entries).
     c. Mark 'node' as visited and add 'w' to the total MST weight.
     d. For all unvisited neighbors 'nei' of 'node', push their connecting edge
        weight (d, nei) into the PQ.
- Time complexity: **O(E log V)**, where V is the number of vertices and E is the
  number of edges. This is because we push up to E edges into the PQ, and each
  insertion/extraction takes O(log V) time (or O(log E), which is often similar).
- Space complexity: **O(V + E)** for the adjacency list and priority queue storage.

💡 Key Pattern:
- **Greedy Strategy in Graphs:** Always picking the locally optimal choice (the smallest
  available edge to an unvisited component) to guarantee a globally optimal solution (the MST).

ℹ️ Keywords:
- Minimum Spanning Tree (MST), Prim's Algorithm, Greedy Algorithm, Priority Queue, Graph.

🗒️ Notes
- Prim's Algorithm works best when the graph is dense (E is closer to $V^2$).
  For sparse graphs, Kruskal's Algorithm (using Disjoint Set Union) might be faster.
-------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

// Define a common alias for pair<int, int> used for (weight, node) or (neighbor, weight)
using pii = pair<int, int>;

class Solution
{
public:
    /**
     * @brief Calculates the total weight of the Minimum Spanning Tree (MST) using Prim's Algorithm.
     * @param V The number of vertices (0 to V-1).
     * @param edges The list of edges, where each element is [u, v, w].
     * @return The sum of weights of the edges in the MST.
     */
    int spanningTree(int V, vector<vector<int>> &edges)
    {

        // Step 1: Build the Adjacency List
        // adj[u] stores pairs of {v, w}, representing an edge from u to v with weight w
        vector<vector<pii>> adj(V);

        for (auto &e : edges)
        {
            int u = e[0], v = e[1], w = e[2];
            // Since the graph is undirected, add edges in both directions
            adj[u].push_back({v, w});
            adj[v].push_back({u, w});
        }

        // Step 2: Initialize Priority Queue (Min-Heap) and Visited Array
        // PQ stores {weight, node} pairs. 'greater' makes it a min-heap based on weight.
        // We push {0, 0} to start at node 0 with 0 cost.
        priority_queue<pii, vector<pii>, greater<pii>> pq;
        vector<bool> vis(V, false);

        // Start from node 0 with a weight of 0
        pq.push({0, 0});
        long long total_weight = 0; // Use long long to prevent potential overflow

        // Step 3: Main Prim's Loop
        while (!pq.empty())
        {
            // Get the minimum weight edge from the set of candidate edges
            auto [w, node] = pq.top();
            pq.pop();

            // Skip if the node is already included in the MST
            if (vis[node])
                continue;

            // Include the current node and its connecting edge (w) into the MST
            vis[node] = true;
            total_weight += w;

            // Explore neighbors
            for (auto [nei, d] : adj[node])
            {
                // 'nei' is the neighbor, 'd' is the weight of the edge (node, nei)

                // If the neighbor is not yet in the MST, push the edge connecting
                // the current MST to the neighbor onto the PQ.
                if (!vis[nei])
                {
                    pq.push({d, nei});
                }
            }
        }

        // Note: For a disconnected graph, this would only return the weight of
        // the MST of the component containing the starting node. Since the problem
        // usually assumes a connected graph, this is sufficient.
        return static_cast<int>(total_weight);
    }
};

int main()
{
    Solution sol;
    cout << "--- Prim's Algorithm MST Test Cases ---\n";

    // Test Case 1: Simple 4-node graph
    // Edges: (0,1,10), (1,2,5), (2,3,15), (3,0,12), (0,2,8)
    // MST edges should be: (0,1,10) or (0,2,8), (2,1,5), (0,3,12) -> Total 25
    // MST edges should be: (0,2,8), (2,1,5), (0,3,12) -> Total 25
    // MST edges should be: (0,2,8), (2,1,5), (3,0,12) -> Total: 8 + 5 + 12 = 25
    int V1 = 4;
    vector<vector<int>> edges1 = {
        {0, 1, 10}, {1, 2, 5}, {2, 3, 15}, {3, 0, 12}, {0, 2, 8}};
    cout << "Test 1 (V=4, MST=25): Expected 25, Got " << sol.spanningTree(V1, edges1) << endl;

    // Test Case 2: Standard 5-node graph (from common examples)
    // Edges: (0,1,2), (0,3,6), (1,2,3), (1,3,8), (1,4,5), (2,4,7), (3,4,9)
    // Expected MST: (0,1,2), (1,2,3), (1,4,5), (0,3,6). Total = 2 + 3 + 5 + 6 = 16
    int V2 = 5;
    vector<vector<int>> edges2 = {
        {0, 1, 2}, {0, 3, 6}, {1, 2, 3}, {1, 3, 8}, {1, 4, 5}, {2, 4, 7}, {3, 4, 9}};
    cout << "Test 2 (V=5, MST=16): Expected 16, Got " << sol.spanningTree(V2, edges2) << endl;

    // Test Case 3: Disconnected graph (Prim's will only find the component MST)
    // Since the problem assumes a connected graph, this test demonstrates the behavior.
    // Component 1: (0,1,1), (1,2,1). Component 2: (3,4,10).
    // Starting at 0, only the first component is included. MST = 2.
    int V3 = 5;
    vector<vector<int>> edges3 = {
        {0, 1, 1}, {1, 2, 1}, {3, 4, 10}};
    cout << "Test 3 (V=5, Two Components, MST of Comp 1=2): Expected 2, Got " << sol.spanningTree(V3, edges3) << endl;

    return 0;
}