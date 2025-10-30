/*
File: Network_Delay_Time.cpp
Date: 2025-10-30 21:11

Problem: Network Delay Time
Link: https://leetcode.com/problems/network-delay-time/description/

Problem Statement:
You are given a network of n nodes, labeled from 1 to n. You are given times,
a list of travel times as directed edges times[i] = (u, v, w), where u is the source
node, v is the target node, and w is the time it takes for a signal to travel
from u to v. A signal starts at a given node k. Return the minimum time it takes
for all n nodes to receive the signal. If it is impossible for all nodes to receive
the signal, return -1.

-------------------------------------------------
❌ Brute Force
- Idea: Exhaustive search (like DFS) from the source 'k' to find all possible
  paths to every other node. For each destination, keep track of the minimum time
  found so far.
- Time complexity: O(V!) or exponential in the worst case for dense graphs,
  due to exploring all simple paths.
- Space complexity: O(V + E) for graph storage and recursion stack.
- Limitations: Inefficient for finding shortest paths due to massive redundant
  calculations; prone to TLE.

✅ Optimized Approachs
- Idea: The problem is fundamentally asking for the **Single Source Shortest Path
  (SSSP)** to all nodes, and then finding the maximum of those shortest path times.
  Since edge weights (time) are non-negative, **Dijkstra's Algorithm** is the optimal choice.
- Approach: **Dijkstra's Algorithm with Priority Queue**.
- Algorithm:
    1. **Graph Setup:** Build an adjacency list `adj` where `adj[u]` stores pairs
       `{v, w}` (neighbor and weight/time).
    2. **Initialization:** Initialize a distance array `dist` of size `n+1` (since nodes are 1-indexed)
       with `INT_MAX`, and set `dist[src] = 0`.
    3. **Priority Queue:** Use a Min-Heap Priority Queue (PQ) storing `{time, node}`
       to efficiently extract the unvisited node with the smallest known travel time.
       Push `{0, src}` onto the PQ.
    4. **Relaxation:** While the PQ is not empty, extract the minimum time node `u`.
       For each neighbor `v` of `u`: if the path time through `u` (`t + wt`) is
       less than `dist[v]`, update `dist[v]` and push the new `{time, v}` onto the PQ.
    5. **Final Result:** After Dijkstra's finishes, iterate through `dist[1]` to `dist[n]`.
       If any distance is `INT_MAX`, it means the node is unreachable, so return -1.
       Otherwise, the result is the maximum value found in the `dist` array
       (the time for the signal to reach the furthest node).
- Time complexity: **O(E log V)**, where $E$ is the number of edges (times) and $V$
  is the number of nodes ($N$). This is achieved by using a Min-Heap Priority Queue.
- Space complexity: **O(N + E)** for the adjacency list and the distance array.

💡 Key Pattern:
- **Max of SSSP:** Problems asking for the time for something to reach *all* points
  is solved by finding the shortest path to *every* point, and then taking the maximum.

ℹ️ Keywords:
- Dijkstra's Algorithm, Single Source Shortest Path (SSSP), Weighted Graph, Priority Queue, Min-Heap.

🗒️ Notes
- The nodes are 1-indexed, so we use arrays of size N+1 and ignore index 0.
- Using a Priority Queue ensures O(E log V) complexity, which is often crucial for larger constraints.
-------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

// Define the pair type for the priority queue: {time, node}
using pi = pair<int, int>;

class Solution
{
public:
    /**
     * @brief Calculates the minimum time for a signal to reach all N nodes from source K
     * using Dijkstra's algorithm.
     * @param times The list of travel times (u, v, w).
     * @param n The number of nodes (1-indexed).
     * @param src The starting node.
     * @return The minimum time required for all nodes to receive the signal, or -1 if impossible.
     */
    int networkDelayTime(const vector<vector<int>> &times, int n, int src)
    {
        // Step 1: Build the adjacency list (1-indexed nodes)
        vector<vector<pair<int, int>>> adj(n + 1);
        for (auto &e : times)
        {
            // e[0] -> e[1] with weight e[2]
            adj[e[0]].push_back({e[1], e[2]});
        }

        // Step 2: Initialize distances (1-indexed) and Priority Queue
        vector<int> dist(n + 1, INT_MAX);
        // Priority Queue: {time, node}, min-heap for smallest time at top
        priority_queue<pi, vector<pi>, greater<pi>> pq;

        dist[src] = 0;
        pq.push({0, src}); // {time, node}

        // Step 3: Dijkstra's Algorithm
        while (!pq.empty())
        {
            auto [t, node] = pq.top(); // t is the time to reach 'node'
            pq.pop();

            if (t > dist[node])
                continue; // Skip outdated (stale) entry

            for (auto [nei, wt] : adj[node])
            {
                int newDist = t + wt;
                if (newDist < dist[nei])
                {
                    dist[nei] = newDist;
                    pq.push({newDist, nei});
                }
            }
        }

        // Step 4: Find the maximum shortest path time
        int maxTime = 0;
        // Check nodes 1 through N (ignore index 0)
        for (int i = 1; i <= n; ++i)
        {
            // If any node is unreachable, return -1
            if (dist[i] == INT_MAX)
                return -1;
            maxTime = max(maxTime, dist[i]);
        }
        return maxTime;
    }
};

// Helper function to run tests
void runTest(Solution &sol, const vector<vector<int>> &times, int n, int k, int expected)
{
    int result = sol.networkDelayTime(times, n, k);
    cout << "N=" << n << ", Src=" << k << " | Result: " << result
         << " | Expected: " << expected;
    if (result == expected)
    {
        cout << " (PASS)\n";
    }
    else
    {
        cout << " (FAIL)\n";
    }
}

int main()
{
    Solution sol;

    cout << "--- Network Delay Time (Dijkstra's) ---\n";

    // Test Case 1: Simple case, all reachable.
    // Graph: 1->2 (1), 1->3 (2), 2->3 (1). N=3, K=1.
    // Shortest times: 1->1(0), 1->2(1), 1->3(2) (via 1->2->3 is 1+1=2, via 1->3 is 2).
    // Max time: 2.
    int N1 = 3, K1 = 1;
    vector<vector<int>> times1 = {{1, 2, 1}, {1, 3, 2}, {2, 3, 1}};
    runTest(sol, times1, N1, K1, 2);
    cout << "--------------------------------\n";

    // Test Case 2: Standard example from LeetCode.
    // Graph: 2->1 (1), 2->3 (1), 3->4 (1). N=4, K=2.
    // Shortest times: 2->1(1), 2->2(0), 2->3(1), 2->4(2).
    // Max time: 2.
    int N2 = 4, K2 = 2;
    vector<vector<int>> times2 = {{2, 1, 1}, {2, 3, 1}, {3, 4, 1}};
    runTest(sol, times2, N2, K2, 2);
    cout << "--------------------------------\n";

    // Test Case 3: Unreachable node.
    // Graph: 1->2 (1). N=2, K=2. Node 1 is source, node 2 is unreachable from 2.
    // Node 1 is unreachable.
    // Max time: -1.
    int N3 = 2, K3 = 2;
    vector<vector<int>> times3 = {{1, 2, 1}};
    runTest(sol, times3, N3, K3, -1);
    cout << "--------------------------------\n";

    // Test Case 4: Larger graph.
    // 1->2(1), 2->3(7), 1->3(4), 4->5(1), 3->4(2). N=5, K=1.
    // Shortest times from 1: 1->1(0), 1->2(1), 1->3(4). Nodes 4 and 5 are unreachable.
    // Max time: -1.
    int N4 = 5, K4 = 1;
    vector<vector<int>> times4 = {{1, 2, 1}, {2, 3, 7}, {1, 3, 4}, {4, 5, 1}, {3, 4, 2}};
    runTest(sol, times4, N4, K4, -1);
    cout << "--------------------------------\n";

    // Test Case 5: Largest shortest path determines delay.
    // 1->2(1), 2->3(1), 3->4(10). N=4, K=1.
    // Times: 1->1(0), 1->2(1), 1->3(2), 1->4(12). Max time: 12.
    int N5 = 4, K5 = 1;
    vector<vector<int>> times5 = {{1, 2, 1}, {2, 3, 1}, {3, 4, 10}};
    runTest(sol, times5, N5, K5, 12);
    cout << "--------------------------------\n";

    return 0;
}
