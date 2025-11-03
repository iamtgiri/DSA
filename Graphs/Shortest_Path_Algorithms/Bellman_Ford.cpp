/*
File: Bellman_Ford.cpp
Date: 2025-11-03 18:12

Problem: Bellman-Ford (Distance from the Source)
Link: https://www.geeksforgeeks.org/problems/distance-from-the-source-bellman-ford-algorithm/1

Problem Statement:
Given a weighted directed graph and a source node `src`, find the shortest
distance from `src` to all other nodes. The graph may contain negative edge
weights, but no negative cycles (unless the problem explicitly asks for detection).
If a node is unreachable, its distance should be represented by a large value.

-------------------------------------------------
❌ Brute Force
- Idea: Exploring all possible simple paths from the source to every other
  node and keeping track of the minimum path weight found.
- Time complexity: O(V!) (Exponential), as the number of simple paths can be factorial.
- Space complexity: O(V + E) for graph storage and recursion stack.
- Limitations: Infeasible for any practical graph size (V > 15-20).

✅ Optimized Approachs
- Idea: Repeatedly relax all edges in the graph. Since the shortest path in a graph
  without negative cycles can have at most V-1 edges, V-1 passes of relaxation
  are sufficient to find all shortest distances.
- Approach: **Bellman-Ford Algorithm**.
- Algorithm:
    1. **Initialization:** Set `dist[src] = 0` and all other `dist[i] = INF`.
    2. **Relaxation (V-1 Passes):** Repeat the relaxation step for all edges (V-1) times.
       Relaxation: For every edge (u, v) with weight w, if dist[u] + w < dist[v],
       update dist[v] = dist[u] + w.
    3. **Negative Cycle Check (Vth Pass):** Perform one final pass over all edges.
       If any distance can still be reduced, it means a **negative cycle** is reachable
       from the source, and shortest paths are undefined.
- Time complexity: **O(V * E)**, where V is the number of vertices and E is the number of edges.
- Space complexity: **O(V)** for the distance array, plus O(E) if the graph is stored
  in an adjacency list, but here we use the input edge list O(1) additional space.

💡 Key Pattern:
- **Relaxation Repetition:** The core idea is that k passes guarantee the shortest
  path using at most k edges. V-1 passes is sufficient for all paths.
- **Negative Weights:** The ability to correctly calculate shortest paths even with
  negative edge weights (as long as no negative cycles are present).

ℹ️ Keywords:
- Bellman-Ford, Shortest Path, Negative Weights, Negative Cycle Detection, Graph Theory.

🗒️ Notes
- **Safety First:** We use `long long` for the distance array (`dist`) internally
  to prevent integer overflow when dealing with large edge weights or many edges,
  especially in the presence of negative weights.
- The return type is `vector<int>`, so the `long long` distances are cast back to `int`
  or replaced by a placeholder (like $10^9$) for unreachable nodes.
-------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution
{
private:
    // Define a large constant for infinity that fits within long long
    // but is distinct from LLONG_MAX, allowing safe addition.
    const long long LLINF = 1e18;
    // Define a placeholder for the final return type (vector<int>)
    const int INF_INT = 1e9;

public:
    /**
     * @brief Implements the Bellman-Ford algorithm to find shortest distances from a source.
     * @param V The number of vertices (0 to V-1).
     * @param edges The list of edges [u, v, weight].
     * @param src The source node.
     * @return Vector of shortest distances from src, or {-1} if a negative cycle is detected.
     */
    vector<int> bellmanFord(int V, vector<vector<int>> &edges, int src)
    {

        // Use long long for internal distance array to prevent overflow
        vector<long long> dist(V, LLINF);
        dist[src] = 0;

        // V-1 passes for relaxation
        for (int i = 1; i < V; ++i)
        {
            bool relaxed = false; // Optimization: stop if no relaxation occurs
            for (auto e : edges)
            {
                int u = e[0], v = e[1];
                long long w = e[2]; // Edge weight can be negative

                // Only relax if node u is reachable
                if (dist[u] != LLINF)
                {
                    if (dist[u] + w < dist[v])
                    {
                        dist[v] = dist[u] + w;
                        relaxed = true;
                    }
                }
            }
            if (!relaxed)
            {
                break; // Optimization: If no distance changes, we are done
            }
        }

        // Vth pass: Negative Cycle Detection
        for (auto e : edges)
        {
            int u = e[0], v = e[1];
            long long w = e[2];

            // If a distance can still be reduced, a negative cycle exists
            if (dist[u] != LLINF)
            {
                if (dist[u] + w < dist[v])
                {
                    // Negative cycle detected
                    return {-1};
                }
            }
        }

        // Convert long long distances back to vector<int> for the result
        vector<int> result_dist(V);
        for (int i = 0; i < V; ++i)
        {
            if (dist[i] == LLINF)
            {
                result_dist[i] = INF_INT; // Use large int for unreachable nodes
            }
            else
            {
                // Since the problem usually guarantees the shortest path fits in int if no NC exists
                result_dist[i] = (int)dist[i];
            }
        }

        return result_dist;
    }
};

int main()
{
    Solution sol;

    cout << "--- Bellman-Ford Algorithm Test Cases ---\n";

    // Test Case 1: Simple graph with negative weights (No negative cycle)
    // V=4, Src=0. Edges: 0->1(5), 0->2(4), 1->3(3), 2->1(-6), 3->2(1)
    // Shortest Distances: 0->0(0), 0->1(-2), 0->2(4), 0->3(1)
    int v1 = 4, src1 = 0;
    vector<vector<int>> edges1 = {
        {0, 1, 5}, {0, 2, 4}, {1, 3, 3}, {2, 1, -6}, {3, 2, 4}};
    vector<int> result1 = sol.bellmanFord(v1, edges1, src1);

    cout << "Test Case 1 (No Negative Cycle): \n";
    cout << "Expected Distances: 0, -2, 4, 1" << endl;
    cout << "Result Distances: ";
    for (int d : result1)
        cout << d << " ";
    cout << endl;
    cout << "-------------------------------------------\n";

    // Test Case 2: Graph with a Negative Cycle (Expected: {-1})
    // V=3, Src=0. Edges: 0->1(1), 1->2(2), 2->0(-4) -> Negative cycle 0->1->2->0 (1+2-4 = -1)
    int v2 = 3, src2 = 0;
    vector<vector<int>> edges2 = {
        {0, 1, 1}, {1, 2, 2}, {2, 0, -4}};
    vector<int> result2 = sol.bellmanFord(v2, edges2, src2);

    cout << "Test Case 2 (Negative Cycle): \n";
    cout << "Expected Result: {-1}" << endl;
    cout << "Result: ";
    for (int d : result2)
        cout << d << " ";
    cout << endl;
    cout << "-------------------------------------------\n";

    return 0;
}
