/*
File: Dijkstra_Algorithm.cpp
Date: 2025-10-30 01:30

Problem: Dijkstra Algorithm
Link: https://www.geeksforqeeks.org/problems/implementing-dijkstra-set-1-adjacency-matrix/1

Problem Statement:
Given a weighted, undirected graph with non-negative edge weights, find the
shortest distance from a given source node (src) to all other nodes.
Return the distance array, where the distance to unreachable nodes remains
as a large value (INT_MAX or -1, depending on context; here we return the
calculated distance or INT_MAX).

-------------------------------------------------
❌ Brute Force
- Idea: Explore all possible paths from the source node to every other node
  using a recursive DFS or iterative brute force, keeping track of the
  minimum distance found so far.
- Time complexity: O(N!) or exponential, as the number of simple paths can grow
  rapidly, especially with cycles (which we must handle with visited checks).
- Space complexity: O(V) for the recursion stack and distance tracking.
- Limitations: Highly inefficient and impractical for any graph of significant size.

✅ Optimized Approachs
- Idea: Dijkstra's algorithm uses a **greedy** approach. It maintains a set of
  vertices whose shortest distance from the source is finalized. At each step,
  it selects the unfinalized vertex with the smallest current distance and
  updates (relaxes) the distances of its neighbors.
- Approach: **Dijkstra's Algorithm with a Min-Heap (Priority Queue)**.
- Algorithm:
    1. **Initialization:** Initialize a distance array `dist[V]` with `INT_MAX`,
       and set `dist[src] = 0`. Build the weighted adjacency list.
    2. **Min-Heap Setup:** Use a `priority_queue` to store `{distance, node}`,
       initialized with `{0, src}`.
    3. **Iteration (Relaxation):** While the priority queue is not empty:
        - Extract the node `u` with the minimum distance (`wt`).
        - If `u` has already been processed (i.e., `vis[u]` is true), skip.
        - Mark `u` as visited (`vis[u] = true`).
        - For every neighbor `v` of `u` with edge weight `d`:
            - **Relaxation:** If the path through `u` is shorter than the currently
              known shortest path to `v` (`dist[u] + d < dist[v]`), update
              `dist[v] = dist[u] + d` and push `{dist[v], v}` into the PQ.
- Time complexity: **O(E log V)**. Each edge relaxation involves a potential
  push/update to the Priority Queue (E operations), and each operation takes O(log V) time.
- Space complexity: **O(V + E)** for the adjacency list, distance array, and priority queue.

💡 Key Pattern:
- **Single Source Shortest Path (SSSP):** Applied to graphs with non-negative edge weights.

ℹ️ Keywords:
- Weighted Graph, Greedy Algorithm, Priority Queue, Min-Heap, Relaxation, SSSP.

🗒️ Notes
- Dijkstra's algorithm *must not* be used on graphs with negative edge weights;
  it will fail to find the correct shortest path. For graphs with negative
  weights, the Bellman-Ford algorithm or SPFA should be used.
- The use of `vis` array is an optimization to prevent processing the same node
  multiple times once its shortest distance has been confirmed.
-------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    /**
     * @brief Computes the shortest path distance from a source node to all other
     * nodes in a weighted undirected graph using Dijkstra's algorithm.
     * @param V The number of vertices.
     * @param edges A vector of triplets {u, v, w} representing an edge between
     * u and v with weight w.
     * @param src The source node (0-based index).
     * @return A vector of integers representing the shortest distance from src to
     * every other node. Unreachable nodes will have INT_MAX.
     */
    vector<int> dijkstra(int V, vector<vector<int>> &edges, int src)
    {
        // Initialize distances to infinity
        vector<int> dist(V, INT_MAX);
        // Adjacency list: adj[u] = {{v, w}, ...}
        vector<vector<pair<int, int>>> adj(V);

        // 1. Build the weighted adjacency list (undirected graph)
        for (auto &e : edges)
        {
            int u = e[0], v = e[1], w = e[2];
            adj[u].push_back({v, w});
            adj[v].push_back({u, w});
        }

        // Min-Heap (Priority Queue): stores {distance, node}
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

        // Initialization
        pq.push({0, src});
        dist[src] = 0;
        vector<bool> vis(V, false); // Optimization to track finalized nodes

        // 2. Main Dijkstra's Loop
        while (!pq.empty())
        {
            // Get the node with the current minimum distance
            auto [wt, node] = pq.top();
            pq.pop();

            // Skip if this node's shortest path has already been finalized/processed
            if (vis[node])
                continue;
            vis[node] = true;

            // Relax neighbors
            for (auto [nei, d] : adj[node])
            {
                // Relaxation check: is path through 'node' shorter than current path to 'nei'?
                if (dist[node] != INT_MAX && dist[node] + d < dist[nei])
                {
                    dist[nei] = dist[node] + d;
                    // Push the updated distance to the priority queue
                    pq.push({dist[nei], nei});
                }
            }
        }

        return dist;
    }
};

// Helper function to print a vector of integers (for INT_MAX, prints "INF")
void printDistanceVector(const vector<int> &vec)
{
    cout << "[";
    for (size_t i = 0; i < vec.size(); ++i)
    {
        if (vec[i] == INT_MAX)
        {
            cout << "INF";
        }
        else
        {
            cout << vec[i];
        }
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

    cout << "--- Dijkstra's Algorithm Shortest Path ---\n";

    // Test Case 1: Simple Path
    // V=3, Edges: 0-1(5), 1-2(2), 0-2(10). Source=0
    // Path: 0->1 (5), 0->2 (10), 0->1->2 (5+2=7). Shortest to 2 is 7.
    int V1 = 3;
    vector<vector<int>> edges1 = {{0, 1, 5}, {1, 2, 2}, {0, 2, 10}};
    int src1 = 0;
    vector<int> res1 = sol.dijkstra(V1, edges1, src1);
    cout << "Test 1 | V=" << V1 << ", Edges: 0-1(5), 1-2(2), 0-2(10). Source: " << src1 << "\n";
    cout << "Result: ";
    printDistanceVector(res1);
    cout << " (Expected: [0, 5, 7])\n";
    cout << "--------------------------------\n";

    // Test Case 2: Standard Graph with Unreachable Node
    // V=6, Edges: 0-1(4), 0-2(4), 1-2(2), 2-3(3), 2-4(1), 2-5(6), 3-5(2), 4-5(3). Source=0
    // Node 3 is part of the graph but has no direct path to 0, 1, 2, 4, 5. Wait,
    // the problem is undirected and 0-5 are connected. Let's make one node unreachable.
    // Let's use 7 vertices (0 to 6). Node 6 is disconnected.
    // 0-1(4), 0-2(4), 1-2(2), 2-3(3), 2-4(1), 3-5(2), 4-5(3).
    // Shortest paths from 0:
    // 0: 0
    // 1: 4 (0->1)
    // 2: 4 (0->2) or 0->1->2 (4+2=6). Shortest to 2 is 4 (0->2)
    // 3: 4->3 = 7
    // 4: 4->4 = 5
    // 5: 4->4->5 = 5+3=8. 4->3->5 = 7+2=9. Shortest to 5 is 8.
    // 6: INF (Unreachable)
    int V2 = 7;
    vector<vector<int>> edges2 = {{0, 1, 4}, {0, 2, 4}, {1, 2, 2}, {2, 3, 3}, {2, 4, 1}, {3, 5, 2}, {4, 5, 3}};
    int src2 = 0;
    // Expected: [0, 4, 4, 7, 5, 8, INF]
    vector<int> res2 = sol.dijkstra(V2, edges2, src2);
    cout << "Test 2 | V=" << V2 << ". Source: " << src2 << ". Node 6 is unreachable.\n";
    cout << "Result: ";
    printDistanceVector(res2);
    cout << " (Expected: [0, 4, 4, 7, 5, 8, INF])\n";
    cout << "--------------------------------\n";

    // Test Case 3: Graph where direct edge is longer than a path
    // V=4, Edges: 0-1(10), 0-2(1), 2-3(1), 3-1(1). Source=0
    // Path: 0->1 (10). Path: 0->2->3->1 (1+1+1=3). Shortest to 1 is 3.
    int V3 = 4;
    vector<vector<int>> edges3 = {{0, 1, 10}, {0, 2, 1}, {2, 3, 1}, {3, 1, 1}};
    int src3 = 0;
    // Expected: [0, 3, 1, 2]
    vector<int> res3 = sol.dijkstra(V3, edges3, src3);
    cout << "Test 3 | V=" << V3 << ", Edges: 0-1(10), 0-2(1), 2-3(1), 3-1(1). Source: " << src3 << "\n";
    cout << "Result: ";
    printDistanceVector(res3);
    cout << " (Expected: [0, 3, 1, 2])\n";
    cout << "--------------------------------\n";

    return 0;
}
