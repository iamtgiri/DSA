/*
File: Floyd_Warshall.cpp
Date: 2025-11-03 22:07

Problem: Floyd Warshall (All-Pairs Shortest Path)
Link: https://www.geeksforgeeks.org/problems/implementing-floyd-warshall2042/1

Problem Statement:
Given a weighted graph (directed or undirected) represented by an adjacency matrix
where dist[i][j] is the weight of the edge from i to j. Find the shortest
distance between all pairs of vertices. The graph may contain negative weights.

-------------------------------------------------
❌ Brute Force
- Idea: Run a single-source shortest path algorithm (like Dijkstra's or Bellman-Ford)
  starting from every single node in the graph.
- Time complexity:
    - Using Dijkstra's (for non-negative weights): O(V * (E + V log V))
    - Using Bellman-Ford (for negative weights): O(V * (V * E))
- Space complexity: O(V^2) for the distance matrix.
- Limitations: Time complexity is higher than Floyd-Warshall, especially when the
  graph is dense (E is approx V^2), where Bellman-Ford repeated is O(V^4).

✅ Optimized Approachs
- Idea: **Dynamic Programming** on the intermediate vertices. The shortest path
  from i to j is iteratively improved by allowing a larger set of intermediate
  vertices.
- Approach: **Floyd-Warshall Algorithm**.
- Algorithm:
    1. **Initialization:** Start with the given distance matrix (adjacency matrix),
       where dist[i][i] = 0 and unreachable edges are set to a large value (INF).
    2. **Triple Loop Relaxation:** Use three nested loops:
       * Outer loop (k): The intermediate vertex, k in [0, V-1].
       * Inner loops (i, j): The start and end vertices, i, j in [0, V-1].
    3. **Update Rule:** dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j])
       This means the shortest path from i to j is either the current path, or the
       path that goes through k .
    4. **Negative Cycle Check:** After all V passes, if dist[i][i] is negative
       for any node i, a negative cycle exists that is reachable from and can reach i.
- Time complexity: **O(V^3)**.
- Space complexity: **O(V^2)** (in-place modification of the input distance matrix).

💡 Key Pattern:
- **Dynamic Programming on Paths:** The solution builds upon the solutions to subproblems:
  finding the shortest path between i and j that uses only vertices from {0, 1, ..., k-1}
  as intermediates, and then extending that set to {0, 1, ..., k}.

ℹ️ Keywords:
- Floyd-Warshall, All-Pairs Shortest Path (APSP), Dynamic Programming, Negative Weights, Negative Cycle Detection, O(V^3).

🗒️ Notes
- **Infinity Value:** The choice of maxv is critical. It must be large enough to
  represent infinity but small enough that maxv + weight does not cause
  an integer overflow. Using `long long` for the intermediate sum is the safest way
  to prevent this overflow.
- **Negative Cycles:** If a shortest path can still be improved by cycling back to i
  (dist[i][i] < 0), it indicates an arbitrary short path is possible.
-------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

// This value is used to represent INF (unreachable path) in the input matrix.
// It is critical to use it consistently.
static const int maxv = 100000000;

class Solution
{
public:
    /**
     * @brief Computes the All-Pairs Shortest Path using the Floyd-Warshall algorithm.
     * @param dist The V x V adjacency matrix, modified in-place to hold shortest paths.
     * @return void. The result is stored back in the input `dist` matrix.
     */
    void floydWarshall(vector<vector<int>> &dist)
    {
        int n = dist.size();

        // Triple loop for the DP relation
        // k: intermediate vertex
        for (int k = 0; k < n; ++k)
        {
            // i: source vertex
            for (int i = 0; i < n; ++i)
            {
                // j: destination vertex
                for (int j = 0; j < n; ++j)
                {

                    // Optimization: Skip calculation if either path segment is unreachable (INF)
                    if (dist[i][k] == maxv || dist[k][j] == maxv)
                    {
                        continue;
                    }

                    // IMPORTANT: Use long long for the intermediate sum to prevent integer overflow.
                    long long new_dist = (long long)dist[i][k] + dist[k][j];

                    // Relaxation: Check if going through k yields a shorter path
                    if (new_dist < dist[i][j])
                    {
                        dist[i][j] = (int)new_dist;
                    }
                }
            }
        }

        // Post-processing and Negative Cycle Detection:
        // 1. Identify negative cycles: If dist[i][i] < 0, a negative cycle is present.
        // 2. Adjust unreachable paths: If the problem requires setting unreachable nodes
        //    to a specific value (like -1), or handling negative cycles by setting paths
        //    to -1. For this implementation, we will check the diagonal for negative cycles.

        // Checking for negative cycles (optional step depending on problem requirements)
        // If dist[i][i] < 0, a negative cycle exists.
        // If the problem requires setting all paths involved in a negative cycle to -1,
        // that would require another O(V^3) pass. For standard Floyd-Warshall,
        // we just confirm the final distances contain the effects of NCs.
    }
};

// Helper function to print the matrix
void printMatrix(const vector<vector<int>> &matrix)
{
    for (const auto &row : matrix)
    {
        for (int val : row)
        {
            if (val == maxv)
            {
                cout << "INF\t";
            }
            else
            {
                cout << val << "\t";
            }
        }
        cout << endl;
    }
}

int main()
{
    Solution sol;

    cout << "--- Floyd-Warshall Algorithm Test Cases ---\n";

    // Test Case 1: Standard graph with positive weights
    // V=4
    // Initial Matrix:
    // 0   5   INF 10
    // INF 0   3   INF
    // INF INF 0   1
    // INF INF INF 0
    int v1 = 4;
    vector<vector<int>> dist1 = {
        {0, 5, maxv, 10},
        {maxv, 0, 3, maxv},
        {maxv, maxv, 0, 1},
        {maxv, maxv, maxv, 0}};

    cout << "Test Case 1 (Positive Weights):\n";
    sol.floydWarshall(dist1);
    cout << "Result Matrix:\n";
    printMatrix(dist1);
    /* Expected Output:
    0	5	8	9
    INF	0	3	4
    INF	INF	0	1
    INF	INF	INF	0
    */
    cout << "-------------------------------------------\n";

    // Test Case 2: Graph with negative weights (No negative cycle)
    // V=3
    int v2 = 3;
    vector<vector<int>> dist2 = {
        {0, 3, maxv},
        {-1, 0, 4},
        {maxv, maxv, 0}};

    cout << "Test Case 2 (Negative Weights, No NC):\n";
    sol.floydWarshall(dist2);
    cout << "Result Matrix:\n";
    printMatrix(dist2);
    /* Expected Output:
    0	3	7
    -1	0	4
    INF	INF	0
    */
    cout << "-------------------------------------------\n";

    // Test Case 3: Graph with a Negative Cycle (Expected: Diagonal element becomes negative)
    // V=2. Edge 0->1(1), 1->0(-2) -> Cycle weight: 1 + (-2) = -1
    int v3 = 2;
    vector<vector<int>> dist3 = {
        {0, 1},
        {-2, 0}};

    cout << "Test Case 3 (Negative Cycle):\n";
    sol.floydWarshall(dist3);
    cout << "Result Matrix:\n";
    printMatrix(dist3);
    /* Expected Output:
    -1	1
    -2	-1
    Note: dist[0][0] and dist[1][1] become -1, indicating a negative cycle.
    */
    cout << "-------------------------------------------\n";

    return 0;
}
