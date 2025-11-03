/*
File: City_With_the_Smallest_Number_of_Neighbors.cpp
Date: 2025-11-03 22:50

Problem: Find the City With the Smallest Number of Neighbors at a Threshold Distance
Link: https://leetcode.com/problems/find-the-city-with-the-smallest-number-of-neighbors-at-a-threshold-distance/description/

Problem Statement:
Given a weighted, undirected graph representing cities and routes, find the city
that has the smallest number of reachable cities within a given 'distanceThreshold'.
If there are multiple such cities, return the city with the largest index.

-------------------------------------------------
❌ Brute Force
- Idea: For every city, run a Single-Source Shortest Path algorithm (like Dijkstra's)
  to find the distance to every other city. Then, count the cities within the
  threshold.
- Time complexity: O(V * (E + V log V)). V runs of Dijkstra's algorithm. For a
  dense graph (E approx V^2), this is approximately O(V^3 log V).
- Space complexity: O(V^2) to store the final distance results.
- Limitations: Inefficient for dense graphs where the complexity approaches O(V^4)
  if using a simpler Dijkstra's implementation.

✅ Optimized Approachs
- Idea: This is an All-Pairs Shortest Path (APSP) problem. Use a dedicated
  APSP algorithm to efficiently calculate all distances at once.
- Approach: **Floyd-Warshall Algorithm**.
- Algorithm:
  1. **Initialization:** Build an adjacency matrix `dist` initialized with direct
     edge weights (or INF for no direct edge, 0 for self-loops).
  2. **Relaxation:** Use three nested loops (k, i, j) to iteratively update the
     shortest path: dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]).
  3. **Tally:** After finding all shortest paths, iterate through the final
     `dist` matrix. For each city `i`, count how many other cities `j` satisfy
     `dist[i][j] <= distanceThreshold`.
  4. **Selection:** Choose the city `i` that yields the minimum count. In case of
     a tie, choose the city with the largest index.
- Time complexity: **O(V^3)** (dominated by the Floyd-Warshall phase).
- Space complexity: **O(V^2)** for the adjacency/distance matrix.

💡 Key Pattern:
- **All-Pairs Shortest Path (APSP):** When a problem requires the shortest distance
  between *every* pair of nodes, use Floyd-Warshall (if up to 400 nodes and negative
  weights) or repeated Dijkstra's (if only positive weights and sparse graph).

ℹ️ Keywords:
- Floyd-Warshall, All-Pairs Shortest Path, Dynamic Programming, Weighted Graph, Tie-breaker

🗒️ Notes
- Tie-breaker logic: The requirement to return the city with the **largest index** in case of a tie is critical. This means we should update the best city when
  `new_count <= min_count` (using `<=` instead of `<`).
- **Overflow:** Although distance threshold and weights are typically small, always use
  a `long long` intermediate sum in the relaxation step to avoid overflow if path
  lengths approach 2.1 billion.
-------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

// Represents Infinity (INF) for unreachable paths. Must be large enough but
// small enough to prevent overflow when added to another weight.
static const int maxv = 100000000;

class Solution
{
public:
    /**
     * @brief Finds the city with the smallest number of neighbors within the distance threshold.
     * @param n The number of cities.
     * @param edges The list of weighted, undirected edges.
     * @param distanceThreshold The maximum allowed distance to be considered a neighbor.
     * @return The city index (0 to n-1) with the smallest neighbor count (largest index on tie).
     */
    int findTheCity(int n, vector<vector<int>> &edges, int distanceThreshold)
    {
        // Initialize the distance matrix with INF
        vector<vector<int>> dist(n, vector<int>(n, maxv));

        // 1. Initialization from edges
        for (auto &e : edges)
        {
            int u = e[0], v = e[1], w = e[2];
            dist[u][v] = w;
            dist[v][u] = w; // Undirected graph
        }
        for (int i = 0; i < n; ++i)
            dist[i][i] = 0;

        // 2. Floyd-Warshall Algorithm (APSP)
        // k: intermediate node, i: source, j: destination
        for (int k = 0; k < n; ++k)
        {
            for (int i = 0; i < n; ++i)
            {
                for (int j = 0; j < n; ++j)
                {

                    // Skip if any segment is unreachable (INF)
                    if (dist[i][k] == maxv || dist[k][j] == maxv)
                        continue;

                    // Use long long for intermediate sum to prevent potential overflow
                    long long new_dist = (long long)dist[i][k] + dist[k][j];

                    // Relaxation step
                    if (new_dist < dist[i][j])
                    {
                        dist[i][j] = (int)new_dist;
                    }
                }
            }
        }

        // 3. Tally and Selection
        int resultCity = -1;
        int minReachableCount = INT_MAX;

        for (int i = 0; i < n; ++i)
        {
            int currentReachableCount = 0;
            // Count neighbors within the threshold for city i
            for (int j = 0; j < n; ++j)
            {
                // i != j check is implicit since dist[i][i]=0 is always <= threshold
                if (i != j && dist[i][j] <= distanceThreshold)
                {
                    ++currentReachableCount;
                }
            }

            // Check for minimum count, breaking ties by choosing the larger index
            // If the current count is less than or EQUAL to the min count, update
            // the result (since the index 'i' is naturally increasing).
            if (currentReachableCount <= minReachableCount)
            {
                minReachableCount = currentReachableCount;
                resultCity = i;
            }
        }

        return resultCity;
    }
};

int main()
{
    Solution sol;

    cout << "--- City With Smallest Neighbors Test Cases ---\n";

    // Test Case 1: Tie resolved by index
    // N=4, Threshold=4. Cities 0 and 3 both have 2 reachable neighbors. Return 3 (largest index).
    int n1 = 4;
    vector<vector<int>> edges1 = {{0, 1, 3}, {1, 2, 1}, {1, 3, 4}, {2, 3, 1}};
    int threshold1 = 4;
    int result1 = sol.findTheCity(n1, edges1, threshold1);
    cout << "Test 1 (N=4, T=4): Expected 3, Got " << result1 << endl;
    cout << "--------------------------------------------------------\n";

    // Test Case 2: No tie, city 4 has the absolute minimum count (1).
    // N=5, Threshold=2. City 4 has 1 reachable neighbor (City 3).
    int n2 = 5;
    vector<vector<int>> edges2 = {{0, 1, 1}, {0, 2, 2}, {1, 3, 1}, {2, 3, 1}, {3, 4, 1}};
    int threshold2 = 2;
    int result2 = sol.findTheCity(n2, edges2, threshold2);
    cout << "Test 2 (N=5, T=2): Expected 4, Got " << result2 << endl;
    cout << "--------------------------------------------------------\n";

    // Test Case 3: All isolated
    // N=3, Threshold=1. All cities have 0 reachable neighbors. Return 2 (largest index).
    int n3 = 3;
    vector<vector<int>> edges3 = {{0, 1, 2}, {1, 2, 2}};
    int threshold3 = 1;
    int result3 = sol.findTheCity(n3, edges3, threshold3);
    cout << "Test 3 (N=3, T=1): Expected 2, Got " << result3 << endl;
    cout << "--------------------------------------------------------\n";

    return 0;
}
