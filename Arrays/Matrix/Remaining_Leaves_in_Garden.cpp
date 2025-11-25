/*
File: Remaining_Leaves_in_Garden.cpp
Date: 2025-11-25 13:35

Problem: Remaining Leaves in Garden
Link: (Assuming a contest problem, no external GfG link found for this specific name)

Problem Statement:
A rectangular garden is represented by a grid of size `height` x `width`. The grid `leaves` stores the count of leaves at each cell (r, c). A string `winds` specifies a sequence of wind directions ('U', 'D', 'L', 'R'). For each wind direction, all leaves move one step in that direction simultaneously. Any leaves that move outside the grid boundaries are blown away and disappear. Calculate the total number of leaves remaining in the garden after all wind actions.

-------------------------------------------------
Brute Force (if any, ignore if not applicable)
- Idea: This problem inherently requires simulation. The 'brute force' is the necessary direct simulation of the leaf movement step by step.
- Time complexity: O(W * H * L) where W is width, H is height, and L is length of the winds string. (For each of L winds, we iterate over all W*H cells).
- Space complexity: O(W * H) for storing the two matrices (`leaves` and `next`).
- Limitations: None, as this is the direct, required simulation.

Current/Optimized Approachs
- Idea: Directly simulate the movement of leaves for each step in the `winds` string sequence. Since leaves from multiple source cells might land on the same destination cell, we must use a temporary matrix to accumulate the counts before updating the main matrix.
- Approach: **Matrix Simulation / Iterative Update**
- Algorithm:
  1. Initialize the total leaf count to the sum of all values in the initial `leaves` matrix.
  2. Iterate through each wind direction `w` in the `winds` string.
  3. Inside the loop, create a temporary matrix `next` (size `height` x `width`) initialized to zero.
  4. Iterate through every cell `(r, c)` of the current `leaves` matrix:
     a. If `leaves[r][c] > 0`, calculate the new position `(nr, nc)` based on wind `w`.
     b. Check bounds: If `(nr, nc)` is within the grid (0 <= nr < height, 0 <= nc < width):
        i. Accumulate the leaves: `next[nr][nc] += leaves[r][c]`.
        ii. (If the leaf is blown away, it is naturally ignored as we only update `next` for in-bounds positions).
     c. After iterating through all cells, update the main matrix: `leaves = next`.
  5. After all winds have passed, calculate and return the sum of all remaining leaves in the final `leaves` matrix.
- Time complexity: **O(W * H * L)** where W is width, H is height, and L is length of the winds string.
- Space complexity: O(W * H) for the matrices.

💡 Key Pattern:
- **State Transition Simulation:** Managing simultaneous, discrete state changes (movement on a grid) by using a temporary state (`next` matrix) to avoid using partially updated values during the current step.

ℹ️ Keywords:
- Grid Simulation, Matrix Manipulation, Discrete Time Steps, Boundary Check.

🗒️ Notes
- The use of the `next` matrix is crucial. If we updated `leaves[nr][nc]` directly, a leaf moving from (0,0) to (1,0) might incorrectly push a leaf from (1,0) to (2,0) in the *same* step if the wind is 'D', which violates the "simultaneously" rule.
-------------------------------------------------
*/

#include <iostream>
#include <vector>
#include <string>
#include <numeric>

using namespace std;

class Solution
{
public:
    /**
     * @brief Simulates the movement of leaves across a grid based on a sequence of wind directions.
     * @param width The width of the garden grid.
     * @param height The height of the garden grid.
     * @param leaves The initial grid where leaves[r][c] is the count of leaves at (r, c).
     * @param winds The sequence of wind directions ('U', 'D', 'L', 'R').
     * @return The total count of leaves remaining in the garden after all winds.
     */
    int remaining_leaves(int width, int height, vector<vector<int>> &leaves, string winds)
    {

        for (char w : winds)
        {
            // Create the next state matrix, initialized to zero.
            vector<vector<int>> next(height, vector<int>(width, 0));

            for (int r = 0; r < height; r++)
            {
                for (int c = 0; c < width; c++)
                {
                    // Only process cells that actually have leaves
                    if (leaves[r][c] == 0)
                        continue;

                    int nr = r, nc = c; // New coordinates

                    // Calculate the new position based on the wind direction
                    if (w == 'U')
                        nr--;
                    else if (w == 'D')
                        nr++;
                    else if (w == 'L')
                        nc--;
                    else if (w == 'R')
                        nc++;

                    // Check bounds: If the new position is within the grid
                    if (nr >= 0 && nr < height && nc >= 0 && nc < width)
                    {
                        // Accumulate the leaves in the new cell
                        next[nr][nc] += leaves[r][c];
                    }
                    // If out of bounds, the leaves are "blown away" and not copied to 'next'.
                }
            }

            // Update the state for the next wind step
            leaves = next;
        }

        // Sum all leaves left in the final state
        int total = 0;
        for (auto &row : leaves)
            for (int x : row)
                total += x;

        return total;
    }
};

int main()
{
    Solution sol;

    // Example 1: Basic movement and boundary loss
    int width1 = 3, height1 = 2;
    // Initial leaves:
    // [ [1, 0, 0],
    //   [0, 1, 0] ]
    vector<vector<int>> leaves1 = {{1, 0, 0}, {0, 1, 0}};
    string winds1 = "RU"; // R: 1->(0,1), 1->(1,2). U: 1->(-1,1) (lost), 1->(0,2)
    // Step R: [ [0, 1, 0], [0, 0, 1] ]
    // Step U: [ [0, 0, 1], [0, 1, 0] ]
    int res1 = sol.remaining_leaves(width1, height1, leaves1, winds1);
    cout << "Example 1 (W=3, H=2, Leaves={{1,0,0},{0,1,0}}, Winds='RU'): " << res1 << " (Expected: 2)" << endl;

    // Reset leaves for next test
    leaves1 = {{1, 0, 0}, {0, 1, 0}};
    string winds2 = "D"; // Both leaves move down: 1->(1,0), 1->(2,1) (lost)
    // Step D: [ [0, 0, 0], [1, 0, 0] ]
    int res2 = sol.remaining_leaves(width1, height1, leaves1, winds2);
    cout << "Example 2 (W=3, H=2, Leaves={{1,0,0},{0,1,0}}, Winds='D'): " << res2 << " (Expected: 1)" << endl;

    // Example 3: Accumulation
    int width3 = 3, height3 = 3;
    // Initial leaves:
    // [ [1, 0, 0],
    //   [1, 0, 0],
    //   [0, 0, 0] ]
    vector<vector<int>> leaves3 = {{1, 0, 0}, {1, 0, 0}, {0, 0, 0}};
    string winds3 = "R"; // Both leaves move right, but land on different cells
    // Step R: [ [0, 1, 0], [0, 1, 0], [0, 0, 0] ]
    // If winds was "DR", the leaf at (0,0) moves to (1,0) (D), then (1,1) (R).
    // The leaf at (1,0) moves to (2,0) (D), then (2,1) (R).
    int res3 = sol.remaining_leaves(width3, height3, leaves3, winds3);
    cout << "Example 3 (W=3, H=3, Leaves={{1,0,0},{1,0,0},{0,0,0}}, Winds='R'): " << res3 << " (Expected: 2)" << endl;

    return 0;
}