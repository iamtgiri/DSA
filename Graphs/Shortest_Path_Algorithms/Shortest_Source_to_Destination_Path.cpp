/*
File: Shortest_Source_to_Destination_Path.cpp
Date: 2025-11-04 01:25

Problem: Shortest Source to Destination Path
Link: https://www.geeksforgeeks.org/problems/shortest-source-to-destination-path3544/1

Problem Statement:
Given a binary matrix A (1s are open paths, 0s are blocked walls), find the
minimum number of steps (path length) from the source (0, 0) to the destination (X, Y).
You can only move in four directions (up, down, left, right).

-------------------------------------------------
❌ Brute Force
- Idea: Recursively explore all possible valid paths from the source (0, 0)
  to the destination (X, Y) using Depth-First Search (DFS) while tracking the
  path length. The minimum length found across all successful paths is the answer.
- Time complexity: O(4^(N * M)). Exponential, as it explores every combination
  of steps and branches (up to 4 per cell) in the worst case.
- Space complexity: O(N * M) for the recursion stack and visited tracking.
- Limitations: Prone to Time Limit Exceeded (TLE) due to massive redundancy
  and its inability to prioritize shorter paths immediately.

✅ Optimized Approachs
- Idea: The problem asks for the **minimum number of steps** (shortest path)
  in an unweighted graph (the grid).
- Approach: **Breadth-First Search (BFS)**.
- Algorithm:
  1. **Source Check:** If the starting cell A[0][0] is 0, the path is impossible, return -1.
  2. **Initialization:** Use a distance matrix `dist` (or a `visited` set/matrix)
     to track the shortest distance from (0, 0) to every cell. Initialize
     `dist[0][0] = 0` and enqueue the source.
  3. **Traversal:** Use a queue to store `(r, c)` coordinates. In the main loop:
     a. Dequeue the current cell `(x, y)` and its distance `d`.
     b. Check the 4 neighbors (up, down, left, right).
     c. A move to `(nx, ny)` is valid only if:
        i. It's within bounds (0 to N-1, 0 to M-1).
        ii. The cell is open (`A[nx][ny] == 1`).
        iii. It hasn't been visited, or a shorter path hasn't been found
             (i.e., `dist[nx][ny] == INT_MAX`).
     d. If valid, update `dist[nx][ny] = d + 1` and enqueue `(nx, ny)`.
  4. **Termination:** If the destination (X, Y) is reached, immediately return
     the current distance `d`. If the queue empties before reaching (X, Y),
     return -1.
- Time complexity: **O(N * M)**. Every cell is visited and processed at most
  once, and each has 4 constant-time neighbor checks.
- Space complexity: **O(N * M)** for the distance/visited array and the queue.

💡 Key Pattern:
- **Grid Shortest Path in Unweighted Graphs:** Anytime a "minimum moves" or
  "shortest path" problem is encountered on a grid, where each step costs 1,
  **BFS** is the go-to solution.

ℹ️ Keywords:
- BFS, Grid Traversal, Shortest Path, Unweighted Graph, 2D Matrix.

🗒️ Notes
- Since we use a `dist` matrix initialized to `INT_MAX`, it serves both as a
  distance tracker and a `visited` set. If `dist[nx][ny]` is not `INT_MAX`, it
  means we've already found the shortest path to that cell due to the BFS order.
-------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    /**
     * @brief Computes the shortest distance from (0, 0) to (X, Y) on a binary grid.
     * @param N The number of rows in the grid.
     * @param M The number of columns in the grid.
     * @param A The binary grid (1s are paths, 0s are walls).
     * @param X The target row index.
     * @param Y The target column index.
     * @return The minimum distance, or -1 if unreachable.
     */
    int shortestDistance(int N, int M, vector<vector<int>> &A, int X, int Y)
    {
        // Edge case: Destination is source
        if (X == 0 && Y == 0)
            return (A[0][0] == 1) ? 0 : -1;

        // Edge case: Source is blocked
        if (A[0][0] == 0)
            return -1;

        // dist array serves as both distance tracker and visited marker
        vector<vector<int>> dist(N, vector<int>(M, INT_MAX));
        queue<pair<int, int>> q;

        dist[0][0] = 0;
        q.push({0, 0});

        // Directions: Up, Right, Left, Down
        static int dirs[4][2] = {{-1, 0}, {0, 1}, {0, -1}, {1, 0}};

        while (!q.empty())
        {
            auto [x, y] = q.front();
            q.pop();
            int d = dist[x][y];

            // Check if we reached the destination
            if (x == X && y == Y)
                return d;

            for (auto &dir : dirs)
            {
                int nx = x + dir[0], ny = y + dir[1];

                // 1. Check Bounds
                // 2. Check if path is open (A[nx][ny]==1)
                // 3. Check if we found a shorter path (implied by dist[nx][ny] == INT_MAX since this is BFS)
                if (nx >= 0 && nx < N && ny >= 0 && ny < M && A[nx][ny] == 1)
                {
                    if (dist[nx][ny] == INT_MAX) // Only proceed if unvisited
                    {
                        dist[nx][ny] = d + 1;
                        q.push({nx, ny});
                    }
                }
            }
        }

        // Destination unreachable
        return -1;
    }
};

int main()
{
    Solution sol;

    cout << "--- Shortest Source to Destination Path Test Cases ---\n";

    // Test Case 1: Simple Path
    // N=3, M=3. Destination (2, 2). Expected: 4
    vector<vector<int>> A1 = {
        {1, 1, 0},
        {1, 1, 0},
        {0, 1, 1}};
    int N1 = 3, M1 = 3, X1 = 2, Y1 = 2;
    int result1 = sol.shortestDistance(N1, M1, A1, X1, Y1);
    cout << "Test 1 (3x3, Target (2, 2)): Expected 4, Got " << result1 << endl;
    cout << "--------------------------------------------------------\n";

    // Test Case 2: Unreachable (Blocked at source)
    // N=3, M=4. Destination (2, 3). Expected: -1
    vector<vector<int>> A2 = {
        {0, 1, 1, 1},
        {1, 1, 1, 0},
        {1, 0, 1, 1}};
    int N2 = 3, M2 = 4, X2 = 2, Y2 = 3;
    int result2 = sol.shortestDistance(N2, M2, A2, X2, Y2);
    cout << "Test 2 (Source Blocked (0, 0) is 0): Expected -1, Got " << result2 << endl;
    cout << "--------------------------------------------------------\n";

    // Test Case 3: Destination Unreachable (Maze blocked)
    // Path blocked by 0s.
    vector<vector<int>> A3 = {
        {1, 1, 1},
        {0, 0, 0},
        {1, 1, 1}};
    int N3 = 3, M3 = 3, X3 = 2, Y3 = 2;
    int result3 = sol.shortestDistance(N3, M3, A3, X3, Y3);
    cout << "Test 3 (Maze Blocked): Expected -1, Got " << result3 << endl;
    cout << "--------------------------------------------------------\n";

    return 0;
}
