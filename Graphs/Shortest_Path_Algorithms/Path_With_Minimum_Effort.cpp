/*
File: Path_With_Minimum_Effort.cpp
Date: 2025-11-02 15:56

Problem: Path With Minimum Effort
Link: https://leetcode.com/problems/path-with-minimum-effort/description/

Problem Statement:
You are given a 2D array of heights. A path's effort is defined as the
maximum absolute difference in heights between any two consecutive cells.
Return the minimum effort required to travel from the top-left cell (0, 0)
to the bottom-right cell (row-1, col-1).

-------------------------------------------------
// MODIFICATION NOTE: Replaced LaTeX math notation with standard code comments/ASCII symbols.

❌ Brute Force
- Idea: Use Depth-First Search (DFS) or Breadth-First Search (BFS) to explore
  every single possible path from (0, 0) to (R-1, C-1). For each path, calculate
  its effort (the maximum edge weight encountered) and track the minimum effort
  found across all paths.
- Time complexity: O(4^(R*C)), where R and C are dimensions. Exponential, as it
  explores all paths, including redundant loops and branches.
- Space complexity: O(R*C) for path storage and recursion stack.
- Limitations: Completely infeasible for grids larger than about 4x4.

✅ Optimized Approachs
- Idea: This problem is equivalent to finding the path from source to destination
  that minimizes the *maximum* edge weight (cost) on the path. This is a classic
  application of the **Single Source Shortest Path (SSSP)** algorithm adapted for a min-max cost function.
- Approach: **Dijkstra's Algorithm (Min-Max Pathfinding)**.
- Algorithm:
    1. **Effort Array:** Initialize a 2D array `effort[R][C]` (our distance array)
       to infinity, representing the minimum maximum effort required to reach each cell.
       Set `effort[0][0] = 0`.
    2. **Priority Queue:** Use a Min-Heap Priority Queue (PQ) to store `(e, r, c)`,
       prioritized by the minimum effort `e`. Push `{0, 0, 0}`.
    3. **Relaxation:** While the PQ is not empty, extract the cell `(r, c)` with the minimum
       effort `e`.
    4. **Destination Check:** If `(r, c)` is the destination, return `e`.
    5. **Neighbor Update:** For each neighbor `(nr, nc)`:
        - Calculate the effort of the new path:
          `new_effort = max(e, abs(heights[r][c] - heights[nr][nc]))`.
        - If `new_effort < effort[nr][nc]`, update the array:
          `effort[nr][nc] = new_effort` and push `{new_effort, nr, nc}` to the PQ.
- Time complexity: **O(R * C * log(R * C))** (where V = R * C is the number of vertices).
  This is highly efficient, similar to standard Dijkstra's (O(E log V)).
- Space complexity: **O(R * C)** for the `effort` array and the priority queue.

💡 Key Pattern:
- **Minimizing Maximum Edge Weight:** When the path cost is determined by the largest
  cost of any single step, use Dijkstra's Algorithm, where the relaxation formula is
  `new_distance = max(current_path_cost, new_edge_cost)`.

ℹ️ Keywords:
- Dijkstra's Algorithm, Min-Max Path, Grid Search, Priority Queue, Shortest Path.

🗒️ Notes
- The logic here requires the `effort` array to store the minimum maximum effort to
  reach a cell, not the total summed cost.
- Unlike a BFS/DFS where a simple `visited` array works, here we must be able to
  revisit a cell if we find a path to it with a strictly lower maximum effort.
-------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

// Type alias for Priority Queue: {effort, row, col}
typedef tuple<int, int, int> ti;
#define isbtwn(a, b, c) ((a) >= (b) && (a) < (c))

class Solution
{
public:
    /**
     * @brief Finds the path from (0, 0) to (R-1, C-1) with the minimum required effort.
     * @param heights The 2D grid of cell heights.
     * @return The minimum maximum effort required.
     */
    int minimumEffortPath(const vector<vector<int>> &heights)
    {
        int row = heights.size(), col = heights[0].size();

        // 1. Effort Array (Distance array for min-max effort)
        // Initialize with a large value representing infinity
        vector<vector<int>> effort(row, vector<int>(col, INT_MAX));
        effort[0][0] = 0;

        // 2. Priority Queue: <effort, row, col> - Min-Heap for Dijkstra's
        priority_queue<ti, vector<ti>, greater<ti>> pq;
        pq.push({0, 0, 0}); // Start at (0, 0) with 0 effort

        // Directions: Up, Down, Left, Right
        static const int dir[][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

        while (!pq.empty())
        {
            // e: current max effort to reach r, c
            auto [e, r, c] = pq.top();
            pq.pop();

            // Optimization: Skip if we found a better path already
            if (e > effort[r][c])
                continue;

            // Destination reached! Since we use a Min-Heap, this is the minimum max effort.
            if (r == row - 1 && c == col - 1)
                return e;

            // 3. Relaxation for Neighbors
            for (auto d : dir)
            {
                int nr = r + d[0], nc = c + d[1];

                // Check boundary conditions
                if (isbtwn(nr, 0, row) && isbtwn(nc, 0, col))
                {

                    // Calculate the maximum effort of the path through (r, c)
                    int new_edge_effort = abs(heights[r][c] - heights[nr][nc]);
                    int new_max_effort = max(e, new_edge_effort);

                    // Relaxation step: If this new path is better, update and push
                    if (new_max_effort < effort[nr][nc])
                    {
                        effort[nr][nc] = new_max_effort;
                        pq.push({new_max_effort, nr, nc});
                    }
                }
            }
        }

        // Should be unreachable if path exists, but for completeness
        return -1;
    }
};

// Helper function to run tests
void runTest(Solution &sol, const vector<vector<int>> &heights, int expected)
{
    int result = sol.minimumEffortPath(heights);
    cout << "Grid size: " << heights.size() << "x" << heights[0].size()
         << " | Result: " << result << " | Expected: " << expected;
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

    cout << "--- Path With Minimum Effort (Dijkstra's Min-Max) ---\n";

    // Test Case 1: Standard case (LeetCode example 1)
    // Path: 1 -> 3 -> 5 -> 3 -> 5
    // Efforts: max(2, 2, 2, 2) = 2
    vector<vector<int>> h1 = {{1, 2, 2}, {3, 8, 2}, {5, 3, 5}};
    runTest(sol, h1, 2);
    cout << "--------------------------------\n";

    // Test Case 2: Max effort is in the first step
    // Path: 1 -> 2 -> 1 -> 1 -> 7
    // Efforts: 1 -> 8 (effort 7) -> 8 (effort 0) -> 9 (effort 1) -> 5 (effort 4)
    // Path 1 -> 10 -> 10 -> 10 -> 10 (Efforts: 9, 0, 0, 0) Max effort: 9
    // Path 1 -> 8 -> 8 -> 9 -> 5 (Efforts: 7, 0, 1, 4) Max effort: 7
    vector<vector<int>> h2 = {{1, 2, 3}, {3, 8, 4}, {5, 3, 5}};
    runTest(sol, h2, 1); // Path: 1->2->3->4->5 Max effort is 1 (2-3=1, 3-4=1, 4-5=1)
    cout << "--------------------------------\n";

    // Test Case 3: No path
    vector<vector<int>> h3 = {{10}}; // Single cell
    runTest(sol, h3, 0);
    cout << "--------------------------------\n";

    // Test Case 4: Larger grid
    vector<vector<int>> h4 = {{1, 10, 6, 7}, {2, 11, 5, 9}, {4, 12, 3, 1}};
    runTest(sol, h4, 8); // Path with effort 8 exists

    return 0;
}
