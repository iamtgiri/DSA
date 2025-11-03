/*
File: Knight_Tour_Configuration.cpp
Date: 2025-11-04 02:11

Problem: Check Knight Tour Configuration
Link: https://leetcode.com/problems/check-knight-tour-configuration/description/

Problem Statement:
Given an N x N grid containing a sequence of numbers from 0 to N*N - 1,
determine if this sequence represents a valid Knight's Tour, where 0 is the start
and each subsequent number (k to k+1) is reachable by a single Knight move.

-------------------------------------------------
❌ Brute Force
- Idea: Simulate the tour starting from the position of '0'. In each step (k=0 to N*N - 2),
  iterate through all 8 possible knight moves from the current position (k) and
  check if any of those 8 moves land exactly on the position of the next number (k+1).
- Time complexity: O((N*N) * 8). For each of the N-squared steps, we check up to 8 neighbors.
  This is still O(N*N), which is the same complexity as the optimized approach.
- Space complexity: O(1) extra space if we find the position of k+1 dynamically,
  or O(N*N) if we store the grid.
- Limitations: Although the time complexity is the same, dynamically searching the
  grid for the position of k+1 in each step would make the brute-force significantly slower
  (O(N^4)) if not optimized.

✅ Optimized Approachs
- Idea: A valid knight's tour means the position of move k and the position of
  move k+1 must be exactly one knight move apart for all k from 0 to N*N-2.
- Approach: **Pre-process and Validate Adjacency**.
- Algorithm:
  1. **Initial Check:** Verify that the starting number, **0**, is at grid[0][0]. If not, return false.
  2. **Pre-processing (Position Mapping):** Create a mapping (an array or map, pos)
     to store the (r, c) coordinates for *every* number k from 0 to N*N-1.
     This takes O(N*N) time.
  3. **Sequential Validation:** Iterate through the sequence from k=1 to N*N-1.
     a. Get the coordinates of the previous step: (x1, y1) = pos[k-1].
     b. Get the coordinates of the current step: (x2, y2) = pos[k].
     c. Calculate the absolute row difference Delta X = absolute value of (x1 - x2) and column difference Delta Y = absolute value of (y1 - y2).
     d. A valid knight move is one where {Delta X, Delta Y} is either {1, 2} or {2, 1}.
     e. If this condition fails for *any* step k, the tour is invalid, return false.
  4. **Success:** If the loop completes, all N*N-1 consecutive moves were valid, return true.
- Time complexity: **O(N*N)**. O(N*N) for pre-processing the positions + O(N*N) for validating all N*N-1 steps.
- Space complexity: **O(N*N)** to store the position map/array (pos).

💡 Key Pattern:
- **Sequence Validation on Grids:** When checking if a sequence of cells forms a
  valid path (like a tour), it is often more efficient to **pre-calculate** the
  positions of all elements and then iterate through the sequence checking the
  step-by-step distance constraints, rather than simulating the path.

ℹ️ Keywords:
- Knight's Tour, Path Validation, Adjacency Check, Grid Traversal, Coordinate Mapping.

🗒️ Notes
- The core of the knight's move check is verifying that the absolute differences in
  coordinates are {1, 2} in any order. This is a very robust check for knight moves.
- The use of vector<pair<int,int>> pos(n * n) is efficient because N-squared is the
  exact number of cells and we can use the move number k directly as the index.
-------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    /**
     * @brief Checks if the given grid represents a valid Knight's Tour configuration.
     * @param grid The N x N grid containing the sequence of moves (0 to N*N - 1).
     * @return true if it is a valid tour, false otherwise.
     */
    bool checkValidGrid(vector<vector<int>> &grid)
    {
        int n = grid.size();
        int total_moves = n * n;

        // 1. Initial Check: The tour must start at (0, 0) with value 0
        if (grid[0][0] != 0)
            return false;

        // 2. Pre-processing: Store coordinates of each number (move k)
        // pos[k] = {row, col}
        vector<pair<int, int>> pos(total_moves);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                pos[grid[i][j]] = {i, j};

        // 3. Sequential Validation: Check consecutive knight moves
        // k iterates from 1 up to N*N - 1, checking the move from k-1 to k
        for (int k = 1; k < total_moves; ++k)
        {
            auto [x1, y1] = pos[k - 1]; // Position of move k-1 (previous)
            auto [x2, y2] = pos[k];     // Position of move k (current)

            // Calculate absolute difference in coordinates
            int dx = abs(x1 - x2);
            int dy = abs(y1 - y2);

            // A move is valid if and only if {dx, dy} is {1, 2} or {2, 1}
            if (!((dx == 1 && dy == 2) || (dx == 2 && dy == 1)))
                return false;
        }

        // 4. Success: All N*N - 1 steps were valid
        return true;
    }
};

int main()
{
    Solution sol;

    cout << "--- Check Knight Tour Configuration Test Cases ---\n";

    // Test Case 1: Valid Tour (5x5)
    vector<vector<int>> grid1 = {
        {0, 11, 16, 5, 20},
        {17, 4, 19, 10, 15},
        {12, 1, 24, 21, 6},
        {3, 18, 23, 14, 9},
        {8, 13, 2, 7, 22}};
    int result1 = sol.checkValidGrid(grid1);
    cout << "Test 1 (Valid 5x5 Tour): Expected 1 (true), Got " << result1 << endl;
    cout << "--------------------------------------------------------\n";

    // Test Case 2: Invalid Tour (Missing starting 0 at (0,0))
    vector<vector<int>> grid2 = {
        {1, 11, 16},
        {17, 0, 19},
        {12, 1, 24}};
    int result2 = sol.checkValidGrid(grid2);
    cout << "Test 2 (Invalid - 0 is not at (0,0)): Expected 0 (false), Got " << result2 << endl;
    cout << "--------------------------------------------------------\n";

    // Test Case 3: Invalid Move (3 to 4 is not a knight move)
    vector<vector<int>> grid3 = {
        {0, 3, 2},
        {1, 4, 5},
        {6, 7, 8}};
    // Move 3(0,1)->4(1,1) is invalid: dx=1, dy=0.
    int result3 = sol.checkValidGrid(grid3);
    cout << "Test 3 (Invalid - Move 3 to 4 is illegal): Expected 0 (false), Got " << result3 << endl;
    cout << "--------------------------------------------------------\n";

    return 0;
}
