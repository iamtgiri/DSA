/*
File: Cheapest_Flights_Within_K_Stops.cpp
Date: 2025-10-30 15:34

Problem: Cheapest Flights Within K Stops
Link: https://leetcode.com/problems/cheapest-flights-within-k-stops/description/

Problem Statement:
Given n cities connected by m flights, find the cheapest price to travel
from a source city (src) to a destination city (dst) with at most k stops.
If there is no such route, return -1.

-------------------------------------------------
❌ Brute Force
- Idea: Use Depth First Search (DFS) or standard recursion to explore all
  possible paths from 'src' to 'dst' that use K or fewer stops (K+1 edges),
  tracking the minimum cumulative cost.
- Time complexity: O(V^K * E) in the worst case, as the path exploration
  can branch significantly and stops are limited.
- Space complexity: O(V + E) for the graph and recursion stack.
- Limitations: Highly inefficient due to exponential path exploration.

✅ Optimized Approachs
- Idea: This problem is a **Single Source Shortest Path (SSSP)** problem where
  the path length is constrained by the number of edges ($K$ stops means $\le K+1$ edges).
  This structure is perfectly solved by a **Dynamic Programming** or **Bellman-Ford** style iteration,
  where each iteration represents one flight/stop.
- Approach: **Dynamic Programming / Bellman-Ford Adaptation**.
- Algorithm:
    1. **Initialization:** Initialize a distance array `dist[V]` where `dist[i]` is
       the minimum cost to reach city `i`. Set `dist[src] = 0` and others to `INT_MAX`.
    2. **Iteration (K+1 times):** Iterate exactly $K+1$ times (representing paths
       with $0, 1, ..., K$ stops).
    3. **Relaxation:** In each iteration, create a temporary distance array (`temp_dist`)
       copied from the current `dist`. Iterate through all flights:
        - For a flight $u \to v$ with price $w$:
        - Update `temp_dist[v] = min(temp_dist[v], dist[u] + w)`.
       Using `temp_dist` ensures that we only relax edges based on costs achieved
       in the *previous* step, correctly limiting the path length by one flight per iteration.
    4. **Update:** Set `dist = temp_dist` for the next iteration.
    5. **Result:** After $K+1$ iterations, `dist[dst]` holds the cheapest price
       with at most $K$ stops.
- Time complexity: **O(K * E)**, where $K$ is the number of stops and $E$ is
  the number of flights. This is faster than standard Dijkstra's $O(E \log V)$
  if $K$ is small.
- Space complexity: **O(V + E)** for the adjacency list and distance arrays.

💡 Key Pattern:
- **Constrained Shortest Path:** When the number of edges (or stops) is limited,
  Dynamic Programming or Bellman-Ford adaptation is the efficient way to solve SSSP.

ℹ️ Keywords:
- Dynamic Programming, Bellman-Ford, SSSP, Constrained Path, Graph.

🗒️ Notes
- This approach inherently handles cycles correctly since the maximum path length
  is strictly enforced by the outer loop ($K+1$ iterations).
-------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
  /**
   * @brief Finds the cheapest price to travel from source (src) to destination (dst)
   * with at most K stops using a DP/Bellman-Ford approach.
   * @param n The number of cities.
   * @param flights The list of flights [u, v, price].
   * @param src The source city.
   * @param dst The destination city.
   * @param k The maximum number of stops allowed.
   * @return The cheapest price, or -1 if the destination is unreachable within K stops.
   */
  int findCheapestPrice(int n, const vector<vector<int>> &flights, int src, int dst, int k)
  {

    // dist[i] stores the minimum cost to reach city i
    vector<int> dist(n, INT_MAX);
    dist[src] = 0;

    // The maximum number of flights (edges) allowed is K + 1 (0 to K stops)
    // We iterate K + 1 times (for 0 stops, 1 stop, ..., K stops)
    for (int i = 0; i <= k; ++i)
    {
      // Create a temporary distance array to store the results of the current iteration.
      // This is crucial: it prevents using a cost calculated in the current stop-level
      // relaxation to relax another edge *in the same step*, which would effectively
      // use more than 'i' stops in this step.
      vector<int> temp_dist = dist;

      // Relax all edges (flights)
      for (const auto &flight : flights)
      {
        int u = flight[0]; // source city
        int v = flight[1]; // destination city
        int w = flight[2]; // price

        // Only consider paths starting from a city 'u' that was reachable
        // in the previous stop-level (i-1 stops)
        if (dist[u] != INT_MAX)
        {
          int newCost = dist[u] + w;
          // Relaxation step: update v's cost if the path through u is cheaper
          temp_dist[v] = min(temp_dist[v], newCost);
        }
      }
      // Update the main distance array for the next iteration (i+1 stops)
      dist = temp_dist;
    }

    // Return the final cost to the destination. If still INT_MAX, it's unreachable.
    return dist[dst] == INT_MAX ? -1 : dist[dst];
  }

  // ------------------------ Alternative BFS Approach ------------------------
  /**
   * @brief Finds the cheapest price to travel from source (src) to destination (dst)
   * with at most K stops using a BFS approach.
   * @param n The number of cities.
   * @param flights The list of flights [u, v, price].
   * @param src The source city.
   * @param dst The destination city.
   * @param k The maximum number of stops allowed.
   * @return The cheapest price, or -1 if the destination is unreachable within K stops
   */
  int findCheapestPrice(int n, vector<vector<int>> &flights, int src, int dst, int k)
  {
    vector<vector<pair<int, int>>> adj(n);
    for (auto &f : flights)
    {
      adj[f[0]].push_back({f[1], f[2]});
    }

    // cost[i] = minimum cost to reach i
    vector<int> cost(n, INT_MAX);
    cost[src] = 0;

    // queue: {node, cost_so_far, stops}
    queue<tuple<int, int, int>> q;
    q.push({src, 0, 0});

    while (!q.empty())
    {
      auto [node, currCost, stops] = q.front();
      q.pop();

      if (stops > k)
        continue;

      for (auto [nei, wt] : adj[node])
      {
        int newCost = currCost + wt;
        if (newCost < cost[nei])
        {
          cost[nei] = newCost;
          q.push({nei, newCost, stops + 1});
        }
      }
    }

    return cost[dst] == INT_MAX ? -1 : cost[dst];
  }
};

// Helper function for clearer output
void runTest(Solution &sol, int n, const vector<vector<int>> &flights, int src, int dst, int k, int expected)
{
  int result = sol.findCheapestPrice(n, flights, src, dst, k);
  cout << "N=" << n << ", Src=" << src << ", Dst=" << dst << ", K=" << k
       << " | Result: " << result
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

  cout << "--- Cheapest Flights Within K Stops ---\n";

  // Test Case 1: Standard case with a cheaper long path
  // 0 -> 1 (100), 1 -> 2 (100), 0 -> 2 (500). Src=0, Dst=2, K=1
  // 0 stops: 0->0 (0)
  // 1 stop: 0->1 (100), 0->2 (500)
  // K=1 (max 1 stop): min(100+100, 500) = 200. NO, that's wrong.
  // K=1 means max 2 flights (0->1->2).
  // K=1: Path 0->1->2 has 1 stop (at city 1), cost 200.
  // Expected: 200
  int N1 = 3;
  vector<vector<int>> flights1 = {{0, 1, 100}, {1, 2, 100}, {0, 2, 500}};
  runTest(sol, N1, flights1, 0, 2, 1, 200);

  // Test Case 2: Short path preferred when K is large
  // Same as above, but K=0
  // K=0 (max 0 stops): Only direct flights (0->2) cost 500.
  // Expected: 500
  runTest(sol, N1, flights1, 0, 2, 0, 500);

  // Test Case 3: Impossible due to stop limit
  // 0 -> 1 (10), 1 -> 2 (10), 2 -> 3 (10). Src=0, Dst=3, K=1
  // Needs 3 flights (2 stops). K=1 allows max 2 flights.
  // K=1: Only reaches 2 (cost 20). Fails to reach 3.
  // Expected: -1
  int N3 = 4;
  vector<vector<int>> flights3 = {{0, 1, 10}, {1, 2, 10}, {2, 3, 10}};
  runTest(sol, N3, flights3, 0, 3, 1, -1);

  // Test Case 4: Long path works with sufficient K
  // Same as above, but K=2
  // K=2: Path 0->1->2->3 is 30.
  // Expected: 30
  runTest(sol, N3, flights3, 0, 3, 2, 30);

  // Test Case 5: Complex graph with a cycle
  // 0 -> 1 (10), 1 -> 2 (10), 2 -> 1 (1), 0 -> 3 (50). Src=0, Dst=2, K=1
  // K=1 (max 2 flights)
  // 0->1 (10) -> 2 (20).
  // Path 0->1->2 cost 20.
  // Expected: 20
  int N5 = 4;
  vector<vector<int>> flights5 = {{0, 1, 10}, {1, 2, 10}, {2, 1, 1}, {0, 3, 50}};
  runTest(sol, N5, flights5, 0, 2, 1, 20);

  // Test Case 6: Path to self
  // 0 -> 1 (1), 1 -> 0 (10), 0 -> 2 (100). Src=0, Dst=0, K=1
  // K=1: 0->1->0 cost 11.
  // Expected: 0 (The cost to the source is always 0)
  int N6 = 3;
  vector<vector<int>> flights6 = {{0, 1, 1}, {1, 0, 10}, {0, 2, 100}};
  runTest(sol, N6, flights6, 0, 0, 1, 0);

  return 0;
}
