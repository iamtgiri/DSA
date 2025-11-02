/*
File: Number_of_Ways_to_Arrive_at_Destination.cpp
Date: 2025-11-02 16:37

Problem: Number of Ways to Arrive at Destination
Link: https://leetcode.com/problems/number-of-ways-to-arrive-at-destination/description/

Problem Statement:
You are given n intersections and a list of roads. Return the number of ways
you can arrive at the destination (intersection n-1) in the shortest amount
of time. Since the answer can be huge, return it modulo 10^9 + 7.

-------------------------------------------------
❌ Brute Force
- Idea: Use Depth-First Search (DFS) or recursion to explore every path from
  the start (0) to the destination (n-1). Calculate the time taken for each
  path and keep track of the minimum time found so far, along with a count
  of paths achieving that minimum time.
- Time complexity: O(V!) or O(V^V) in the worst-case scenario (fully connected graph),
  as it explores all possible paths.
- Space complexity: O(V + E) for graph storage and O(V) for the recursion stack.
- Limitations: Exponential complexity, making it infeasible for typical constraints (n <= 200).

✅ Optimized Approachs
- Idea: This is a **Single-Source Shortest Path (SSSP)** problem that requires
  counting how many paths achieve the minimum distance. This is an extension
  of Dijkstra's Algorithm.
- Approach: **Dijkstra's Algorithm with Path Counting** (Dynamic Programming on the Graph).
- Algorithm:
    1. **Initialization:** Use a standard Dijkstra setup with two arrays:
       - `dist[i]`: Minimum time to reach node `i`. (Initialize to infinity, `dist[0] = 0`).
       - `ways[i]`: Number of ways to reach node `i` in `dist[i]` time.
         (Initialize to 0, `ways[0] = 1`).
    2. **Relaxation Logic (Critical):** When considering an edge from `u` to `v`
       with weight `w` (time):
       - **Case 1: Shorter Path Found (`nd < dist[v]`):**
         Update `dist[v] = nd`. The number of ways to reach `v` is now *only* the ways
         to reach `u`, so `ways[v] = ways[u]`.
       - **Case 2: Equal Path Found (`nd == dist[v]`):**
         We found a new, equally short path. Increment `ways[v]` by `ways[u]`.
         `ways[v] = (ways[v] + ways[u]) % MOD`.
- Time complexity: **O(E log V)** or **O(E + V log V)**, typical for Dijkstra's
  with a binary heap, where V is the number of intersections and E is the number of roads.
- Space complexity: **O(V + E)** for the adjacency list, distance and ways arrays,
  and the priority queue.

💡 Key Pattern:
- **Dijkstra's for Counting:** Modifying Dijkstra's relaxation step to incorporate
  counting (DP) when an equally optimal path is discovered.

ℹ️ Keywords:
- Dijkstra's Algorithm, Shortest Path, Dynamic Programming on Graph, Path Counting, Modulo.

🗒️ Notes
- Using `long long` for distance and ways is crucial to prevent overflow before the modulo operation.
- The use of the priority queue ensures nodes are processed in order of increasing
  shortest time, which is essential for the path counting DP. [Image of Dijkstra's algorithm for path counting]
-------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    /**
     * @brief Computes the number of paths that arrive at the destination in the shortest time.
     * @param n The number of intersections (nodes).
     * @param roads The list of roads [u, v, time].
     * @return The number of shortest time paths, modulo 10^9 + 7.
     */
    int countPaths(int n, vector<vector<int>> &roads)
    {
        const long long MOD = 1e9 + 7;
        using P = pair<long long, int>; // <time, node>

        // Build Adjacency List: {neighbor, time_to_neighbor}
        vector<vector<pair<int, int>>> adj(n);
        for (auto &e : roads)
        {
            adj[e[0]].push_back({e[1], e[2]});
            adj[e[1]].push_back({e[0], e[2]}); // Roads are bidirectional
        }

        // dist: Minimum time to reach node i from node 0
        vector<long long> dist(n, LLONG_MAX);
        // ways: Number of paths to reach node i in dist[i] time
        vector<long long> ways(n, 0);

        // Priority Queue: Min-Heap based on time
        priority_queue<P, vector<P>, greater<P>> pq;

        dist[0] = 0;
        ways[0] = 1; // 1 way to be at the starting node (0) at time 0
        pq.push({0, 0});

        while (!pq.empty())
        {
            auto [d, u] = pq.top();
            pq.pop();

            // Skip if a shorter path to u has already been processed
            if (d > dist[u])
                continue;

            for (auto [v, w] : adj[u])
            {
                long long nd = d + w; // New time to reach neighbor v

                if (nd < dist[v])
                {
                    // Case 1: Found a strictly shorter path to v
                    dist[v] = nd;
                    // The number of ways is reset to the ways of the current node u
                    ways[v] = ways[u];
                    pq.push({nd, v});
                }
                else if (nd == dist[v])
                {
                    // Case 2: Found an equally short path to v
                    // Add the ways from u to the existing count for v
                    ways[v] = (ways[v] + ways[u]) % MOD;
                }
            }
        }

        // The result is the number of shortest paths to the destination (n-1)
        return ways[n - 1];
    }
};

// Main function for testing
int main()
{
    Solution sol;

    cout << "--- Number of Ways to Arrive at Destination (Dijkstra's Path Counting) ---\n";

    //  Test Case 1: Official LeetCode Example
    int n1 = 7;
    vector<vector<int>> roads1 = {
        {0, 6, 7}, {0, 1, 2}, {1, 2, 3}, {1, 3, 3},
        {6, 3, 3}, {3, 5, 1}, {6, 5, 1}, {2, 5, 1},
        {0, 4, 5}, {4, 6, 2}
    };

    cout << "Test Case 1 (n=7): Expected = 4" << endl;
    cout << "Result: " << sol.countPaths(n1, roads1) << endl << endl;

    //  Test Case 2: Simple sanity check
    int n2 = 6;
    vector<vector<int>> roads2 = {
        {0, 1, 1}, {1, 2, 1}, {2, 5, 1},
        {0, 3, 1}, {3, 4, 1}, {4, 5, 1}
    };

    cout << "Test Case 2 (n=6): Expected = 2" << endl;
    cout << "Result: " << sol.countPaths(n2, roads2) << endl;

    return 0;
}
