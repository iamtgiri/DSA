/*
File: Shortest_Path_in_WUG.cpp
Date: 2025-11-03 15:50

Problem: Shortest Path in Weighted Undirected Graph
Link: https://www.geeksforgeeks.org/problems/shortest-path-in-weighted-undirected-graph/1

Problem Statement:
Given a weighted, undirected, and connected graph of V vertices (1 to N) and
E edges. Find the shortest path from vertex 1 to vertex N and return it as
a vector where the first element is the total shortest distance, followed
by the nodes in the path. If no path exists, return {-1}.

-------------------------------------------------
❌ Brute Force
- Idea: Explore all possible simple paths from the start (1) to the end (N)
  using DFS or recursion. Calculate the total weight for each path.
- Time complexity: O(N!). In the worst case (dense graph), the number of paths
  can be exponential, making the approach intractable.
- Space complexity: O(N + M) for graph storage and recursion stack.
- Limitations: Infeasible for graphs with more than 15-20 nodes.

✅ Optimized Approachs
- Idea: Find the Single Source Shortest Path (SSSP) from vertex 1 to all other
  vertices, and simultaneously track the predecessor of each node to reconstruct
  the path to N.
- Approach: **Dijkstra's Algorithm with Path Reconstruction**.
- Algorithm:
    1. **Initialization:** Use a Priority Queue (Min-Heap) to store `{distance, node}`.
       Initialize distance array `dist` to infinity, `dist[1] = 0`. Initialize
       a `parent` array to track the predecessor on the shortest path.
    2. **Dijkstra's:** Use the standard relaxation technique: if a path through
       the current node `u` to a neighbor `v` is shorter than the currently
       known shortest path to `v`, update `dist[v]` and set `parent[v] = u`.
    3. **Path Reconstruction:** If `dist[N]` is not infinity, trace back from
       `N` to `1` using the `parent` array to build the path.
- Time complexity: **O(M log N)**, where N is the number of vertices and M is
  the number of edges. (E log V complexity).
- Space complexity: **O(N + M)** for the adjacency list, distance/parent arrays,
  and the priority queue.

💡 Key Pattern:
- **Dijkstra's for Path Tracing:** Using a `parent` or `predecessor` array in
  Dijkstra's to not only find the shortest distance but also the nodes forming
  that path.

ℹ️ Keywords:
- Dijkstra's Algorithm, Shortest Path, Weighted Graph, Path Reconstruction, Priority Queue.

🗒️ Notes
- **CRITICAL:** Distances and intermediate sums must use `long long` to prevent
  integer overflow, as total path weight can exceed INT_MAX (2 * 10^9).
- The result must be formatted as `{distance, node1, node2, ..., nodeN}`.
-------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

// Type alias for adjacency list: {neighbor, weight}
typedef pair<int, int> pi;
// Type alias for Priority Queue elements: {distance, node}
// CRITICAL: distance must be long long to prevent overflow.
typedef pair<long long, int> PQ_T;

class Solution
{
public:
    /**
     * @brief Finds the shortest path and total distance from node 1 to node N.
     * @param n The number of vertices (1 to n).
     * @param m The number of edges.
     * @param edges The list of edges [u, v, weight].
     * @return Vector containing {shortest_distance, node1, ..., nodeN} or {-1}.
     */
    vector<int> shortestPath(int n, int m, vector<vector<int>> &edges)
    {

        // 1. Build Adjacency List: {neighbor, weight}
        vector<vector<pi>> adj(n + 1); // 1-based indexing
        for (auto e : edges)
        {
            int u = e[0], v = e[1], w = e[2];
            adj[u].push_back({v, w});
            adj[v].push_back({u, w}); // Undirected graph
        }

        // 2. Initialization for Dijkstra's
        // CRITICAL: dist must be long long
        vector<long long> dist(n + 1, LLONG_MAX);
        vector<int> parent(n + 1, -1); // To reconstruct the path

        // Priority Queue: Min-Heap of {distance, node}
        priority_queue<PQ_T, vector<PQ_T>, greater<PQ_T>> pq;

        dist[1] = 0;
        pq.push({0, 1}); // Start at node 1 with distance 0

        // Note: We don't need a separate 'vis' array. The distance check handles revisits.

        // 3. Dijkstra's Algorithm
        while (!pq.empty())
        {
            // Use long long for distance extracted from PQ
            auto [dis, node] = pq.top();
            pq.pop();

            // Optimization: If extracted distance is worse than known, skip.
            if (dis > dist[node])
                continue;

            for (auto [nei, w] : adj[node])
            {
                // CRITICAL: Use long long for intermediate calculation
                long long currdist = dist[node] + w;

                // Relaxation
                if (dist[nei] > currdist)
                {
                    // Found a shorter path
                    dist[nei] = currdist;
                    parent[nei] = node; // Update predecessor
                    pq.push({currdist, nei});
                }
            }
        }

        // 4. Path Reconstruction
        if (dist[n] == LLONG_MAX)
        {
            // No path exists from 1 to n
            return {-1};
        }

        vector<int> result;
        int node = n;

        // Trace back from destination (n) to source (1) using the parent array
        // The path is stored in reverse order
        while (node != -1)
        {
            result.push_back(node);
            // MODIFICATION: Logic for parent array check ensures termination at source (1)
            // Original code used parent[1] = -1. This is the correct termination condition.
            node = parent[node];
        }

        // Format the output: {distance, node1, node2, ..., nodeN}
        // First, add the distance to the end of the reverse path
        result.push_back((int)dist[n]); // Cast distance back to int for the final result vector

        // Reverse the vector to get the path in the correct order {distance, node1...}
        reverse(result.begin(), result.end());

        return result;
    }
};

int main()
{
    Solution sol;

    cout << "--- Shortest Path in Weighted Undirected Graph ---\n";

    // Test Case 1: Standard shortest path with path reconstruction
    // Graph: 5 nodes (1 to 5), 6 edges
    // Edges: 1-2(2), 1-3(4), 2-3(1), 2-4(7), 3-5(3), 4-5(1)
    // Shortest path 1 -> 5: 1 -> 2 -> 3 -> 5. Total distance: 2 + 1 + 3 = 6.
    // Expected Output: {6, 1, 2, 3, 5}
    int n1 = 5, m1 = 6;
    vector<vector<int>> edges1 = {
        {1, 2, 2}, {1, 3, 4}, {2, 3, 1}, {2, 4, 7}, {3, 5, 3}, {4, 5, 1}};
    vector<int> result1 = sol.shortestPath(n1, m1, edges1);

    cout << "Test Case 1 (1 -> 5, distance 6): ";
    if (result1[0] == 6)
    {
        cout << "PASS. Path: ";
        for (int x : result1)
            cout << x << " ";
        cout << endl;
    }
    else
    {
        cout << "FAIL. Result: ";
        for (int x : result1)
            cout << x << " ";
        cout << " (Expected distance 6)" << endl;
    }
    cout << "------------------------------------------------\n";

    // Test Case 2: No path exists (N=5, but graph only connects 1-3)
    int n2 = 5, m2 = 2;
    vector<vector<int>> edges2 = {
        {1, 2, 10}, {2, 3, 5}};
    vector<int> result2 = sol.shortestPath(n2, m2, edges2);

    cout << "Test Case 2 (1 -> 5, no path): ";
    if (result2.size() == 1 && result2[0] == -1)
    {
        cout << "PASS. Result: -1" << endl;
    }
    else
    {
        cout << "FAIL. Result size: " << result2.size() << endl;
    }
    cout << "------------------------------------------------\n";

    return 0;
}
