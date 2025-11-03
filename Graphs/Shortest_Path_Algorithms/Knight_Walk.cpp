/*
File: Knight_Walk.cpp
Date: 2025-11-04 01:48

Problem: Knight Walk

Link: https://www.geeksforgeeks.org/problems/knight-walk4521/1

Problem Statement:
Given a chessboard of size N x N, a starting position for a Knight, and a target
position, find the minimum number of steps the Knight needs to reach the target.

-------------------------------------------------
❌ Brute Force
- Idea: Use Depth-First Search (DFS) to explore all possible sequences of knight
  moves from the start to the target. Track the path length and keep the minimum
  found so far.
- Time complexity: Exponential, O(8^(N^2)). The worst-case branching factor is 8
  at every step, leading to excessive exploration of long, non-optimal paths.
- Space complexity: O(N^2) for the recursion stack and visited tracking.
- Limitations: Inefficient and guaranteed to time out for large N due to redundant
  work and failure to find the shortest path efficiently.

✅ Optimized Approachs
- Idea: The problem is equivalent to finding the **shortest path** between two
  nodes in an unweighted graph, where each cell is a node and a valid knight move
  is an edge of cost 1.
- Approach: **Breadth-First Search (BFS)**.
- Algorithm:
  1. **Coordinate Conversion:** Convert the given 1-based coordinates (1 to N)
     into 0-based coordinates (0 to N-1) for array indexing.
  2. **Initialization:** Use a `visited` matrix `vis[N][N]` to track cells that
     have been added to the queue. Start a queue containing the initial position.
  3. **BFS Traversal:** Use an iterative BFS, keeping track of the current step count.
     a. The queue will store `(x, y)` coordinates.
     b. In each layer/step: Dequeue all nodes currently in the queue for the current
        step count.
     c. For each dequeued cell, explore the **8 possible knight moves**.
     d. A move to `(nx, ny)` is valid if:
        i. It's within the board boundaries (0 to N-1).
        ii. It has **not been visited** (`!vis[nx][ny]`).
     e. If valid, mark as visited, and enqueue `(nx, ny)`.
     f. If the target `(tx, ty)` is reached, return the current step count.
  4. **Termination:** If the target is reached, return the steps. If the queue
     empties, the target is unreachable (though highly unlikely on a standard board), return -1.
- Time complexity: **O(N^2)**. Since the board has $N^2$ cells, and each cell
  is visited and processed at most once with 8 constant-time neighbor checks,
  the complexity is proportional to the size of the state space.
- Space complexity: **O(N^2)** for the visited matrix and the queue.

💡 Key Pattern:
- **Shortest Path on a Grid (Non-Adjacent Moves):** This is a variation of grid
  BFS where the allowed moves are non-adjacent (the 'L' shape). The general BFS
  principle remains: explore layer by layer to guarantee the shortest path is found first.

ℹ️ Keywords:
- BFS, Chessboard, Knight's Tour, Shortest Path, Grid Traversal, Unweighted Graph.

🗒️ Notes
- The use of `steps` incremented *outside* the inner loop (level-by-level processing)
  is the classic way to find the shortest path length in BFS without a separate
  distance matrix, although a distance matrix could also be used.
- The 1-based indexing in the problem statement must be converted to 0-based
  for array/vector access in C++.
-------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    /**
     * @brief Finds the minimum steps a Knight takes to reach the target position on an N x N board.
     * @param KnightPos The starting coordinates (1-based).
     * @param TargetPos The target coordinates (1-based).
     * @param N The size of the N x N chessboard.
     * @return The minimum number of steps.
     */
    int minStepToReachTarget(vector<int> &KnightPos, vector<int> &TargetPos, int N)
    {
        // Convert 1-based positions to 0-based for easier indexing
        int sx = KnightPos[0] - 1, sy = KnightPos[1] - 1;
        int tx = TargetPos[0] - 1, ty = TargetPos[1] - 1;

        // If already at target
        if (sx == tx && sy == ty)
            return 0;

        // 8 possible knight moves (L-shaped)
        int dir[8][2] = {
            {-2, -1}, {-2, 1}, {-1, -2}, {-1, 2}, {1, -2}, {1, 2}, {2, -1}, {2, 1}};

        // Use a visited matrix to avoid cycles and redundant processing
        vector<vector<bool>> vis(N, vector<bool>(N, false));
        queue<pair<int, int>> q;

        q.push({sx, sy});
        vis[sx][sy] = true;

        int steps = 0;

        // BFS traversal
        while (!q.empty())
        {
            int sz = q.size();
            // Process all nodes at the current step level
            while (sz--)
            {
                auto [x, y] = q.front();
                q.pop();

                // Check for termination condition
                if (x == tx && y == ty)
                    return steps;

                // Explore 8 neighbors
                for (auto &d : dir)
                {
                    int nx = x + d[0], ny = y + d[1];

                    // Check bounds and visited status
                    if (nx >= 0 && nx < N && ny >= 0 && ny < N && !vis[nx][ny])
                    {
                        vis[nx][ny] = true;
                        q.push({nx, ny});
                    }
                }
            }
            // Increment steps after processing the entire level
            steps++;
        }

        // Target unreachable
        return -1;
    }
};

int main()
{
    Solution sol;

    cout << "--- Knight Walk Test Cases ---\n";

    // Test Case 1: Standard small board (8x8)
    // Start (4, 5), Target (1, 1). Should take 3 steps.
    vector<int> start1 = {4, 5};
    vector<int> target1 = {1, 1};
    int N1 = 8;
    int result1 = sol.minStepToReachTarget(start1, target1, N1);
    cout << "Test 1 (8x8, (4,5) -> (1,1)): Expected 3, Got " << result1 << endl;
    cout << "--------------------------------------------------------\n";

    // Test Case 2: Large board, minimal move (2 steps)
    // Start (1, 1), Target (2, 3).
    vector<int> start2 = {1, 1};
    vector<int> target2 = {2, 3};
    int N2 = 30; // Board size doesn't matter for 2 steps
    int result2 = sol.minStepToReachTarget(start2, target2, N2);
    cout << "Test 2 (30x30, (1,1) -> (2,3)): Expected 1, Got " << result2 << endl;
    cout << "--------------------------------------------------------\n";

    // Test Case 3: Start == Target
    // Expected 0 steps
    vector<int> start3 = {6, 6};
    vector<int> target3 = {6, 6};
    int N3 = 10;
    int result3 = sol.minStepToReachTarget(start3, target3, N3);
    cout << "Test 3 (10x10, (6,6) -> (6,6)): Expected 0, Got " << result3 << endl;
    cout << "--------------------------------------------------------\n";

    return 0;
}
