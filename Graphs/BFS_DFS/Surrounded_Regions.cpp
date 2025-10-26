/*
File: Surrounded_Regions.cpp
Date: 2025-10-14 01:17

Problem: Surrounded Regions
Link: https://leetcode.com/problems/surrounded-regions/description/

Problem Statement:
Given an m x n matrix board containing 'X' and 'O', capture all regions that
are 4-directionally surrounded by 'X'.
A region is captured by flipping all contained 'O's to 'X's.
A region is NOT captured if it is on the border or connected to the border
(i.e., it is "safe").

Example:
Input: board = [["X","X","X","X"],
                ["X","O","O","X"],
                ["X","X","O","X"],
                ["X","O","X","X"]]
                
Output: [["X","X","X","X"],
         ["X","X","X","X"],
         ["X","X","X","X"],
         ["X","O","X","X"]]
----------------------------------------------------------------------------------
❌ Brute Force
- Idea: For every 'O' in the inner part of the board, run a separate BFS or DFS
  to check if it connects to any 'O' on the border.
- Time complexity: O((m*n)^2). Up to O(m*n) 'O' cells, each taking O(m*n) to
  check reachability.
- Space complexity: O(m*n) for recursion stack or auxiliary visited array.
- Limitations: Extremely inefficient due to redundant checks.

✅ Optimized Approach
- Idea: Instead of checking which regions are surrounded, identify which regions
  are NOT surrounded (i.e., safe) by starting a flood-fill from the boundary 'O's.
- Approach: Multi-Source BFS / Boundary Flood Fill
- Algorithm:
  1. Use 'B' (Boundary-safe) as a temporary marker.
  2. Initialize a queue with all 'O' cells located on the grid border. Change
     these border 'O's to 'B's.
  3. Run BFS/Flood Fill from these sources, changing all connected 'O's to 'B's.
  4. Finally, iterate through the entire board:
     - Flip remaining 'O's to 'X's (they are surrounded).
     - Flip all 'B's back to 'O's (they are safe).
- Time complexity: O(m*n). Each cell is visited and processed at most once.
- Space complexity: O(m*n) for the BFS queue.

💡 Key Pattern:
- Connectivity problems involving boundaries: Flood-fill/BFS/DFS from the
  boundaries inwards to mark "exposed" or "safe" areas first.

ℹ️ Keywords:
- BFS, Multi-Source, Grid Traversal, Flood Fill, In-place Modification

🗒️ Notes
- The temporary marker ('B' in this case) is crucial for distinguishing between
  surrounded 'O's and boundary-connected 'O's.
- The two-pass approach (boundary check then final flip) ensures correctness.
----------------------------------------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    /**
     * @brief Captures all regions ('O's) that are surrounded by 'X's.
     * @param board The input m x n board (modified in place).
     * @return void
     */
    void solve(vector<vector<char>> &board)
    {
        if (board.empty())
            return;

        int m = board.size();
        int n = board[0].size();

        // Queue for Multi-Source BFS
        queue<pair<int, int>> q;

        // 1. Initial Scan: Find all 'O's on the border and initialize BFS
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                // Check if the cell is on the border AND is 'O'
                if (board[i][j] == 'O' && (i == 0 || i == m - 1 || j == 0 || j == n - 1))
                {
                    // Mark as boundary-connected ('B') and add to queue
                    board[i][j] = 'B';
                    q.push({i, j});
                }
            }
        }

        // Standard directions for 4-directional movement (up, down, left, right)
        int dirs[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

        // 2. Multi-Source BFS: Flood-fill all 'O' regions connected to the border
        while (!q.empty())
        {
            // Use structured binding for cleaner coordinate access
            auto [x, y] = q.front();
            q.pop();

            // Explore 4 neighbors
            for (auto &d : dirs)
            {
                int nx = x + d[0];
                int ny = y + d[1];

                // Check boundary conditions and if the neighbor is an unvisited 'O'
                if (nx >= 0 && nx < m && ny >= 0 && ny < n && board[nx][ny] == 'O')
                {
                    // Mark as boundary-connected ('B')
                    board[nx][ny] = 'B';
                    q.push({nx, ny});
                }
            }
        }

        // 3. Final Pass: Flip 'O's to 'X's (captured) and 'B's back to 'O's (safe)
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (board[i][j] == 'O')
                {
                    // This 'O' was never reached from the border -> it is surrounded
                    board[i][j] = 'X';
                }
                else if (board[i][j] == 'B')
                {
                    // This 'B' was connected to the border -> restore it to 'O' (safe)
                    board[i][j] = 'O';
                }
            }
        }
    }
};

// Helper function to print the board for testing
void printBoard(const vector<vector<char>> &board)
{
    for (const auto &row : board)
    {
        for (char val : row)
        {
            cout << val << " ";
        }
        cout << endl;
    }
}

int main()
{
    Solution sol;

    // Test Case 1: Example provided in problem statement
    // Input:
    // X X X X
    // X O O X
    // X X O X
    // X O X X
    // Expected Output:
    // X X X X
    // X X X X
    // X X X X
    // X O X X  (The bottom-left 'O' is safe)
    vector<vector<char>> board1 = {
        {'X', 'X', 'X', 'X'},
        {'X', 'O', 'O', 'X'},
        {'X', 'X', 'O', 'X'},
        {'X', 'O', 'X', 'X'}};
    cout << "Test Case 1 Input:" << endl;
    printBoard(board1);
    sol.solve(board1);
    cout << "Test Case 1 Output (Expected: 1 safe 'O'):" << endl;
    printBoard(board1);

    // Test Case 2: No surrounded regions (all 'O's are safe)
    // Input:
    // O O O
    // O X O
    // O O O
    // Expected Output: Same as input
    vector<vector<char>> board2 = {
        {'O', 'O', 'O'},
        {'O', 'X', 'O'},
        {'O', 'O', 'O'}};
    cout << "\nTest Case 2 Input:" << endl;
    printBoard(board2);
    sol.solve(board2);
    cout << "Test Case 2 Output (Expected: all 'O's):" << endl;
    printBoard(board2);

    return 0;
}
