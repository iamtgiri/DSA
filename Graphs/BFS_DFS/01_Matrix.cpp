/*
File: 01_Matrix.cpp
Date: 2025-10-14 00:27

Problem: 01 Matrix
Link: https://leetcode.com/problems/01-matrix/description/

Problem Statement:
Given an m x n binary matrix mat, return the distance of the nearest 0 for
each cell. The distance between two cells sharing a common edge is 1.

Example 1:
Input: mat = [[0,0,0],[0,1,0],[0,0,0]]
Output: [[0,0,0],[0,1,0],[0,0,0]]

Example 2:
Input: mat = [[0,0,0],[0,1,0],[1,1,1]]
Output: [[0,0,0],[0,1,0],[1,2,1]]
----------------------------------------------------------------------------------
❌ Brute Force
- Idea: For every cell (i, j) containing a 1, perform a separate BFS to find
  the closest 0.
- Time complexity: O(m^2 * n^2) since we run O(m*n) BFS searches, each taking
  O(m*n) time.
- Space complexity: O(m*n) for storing the distance matrix and visited set.
- Limitations: Too slow for large matrices.

✅ Optimized Approach
- Idea: Use Multi-Source Breadth-First Search (BFS). Starting from all 0s
  simultaneously, BFS calculates the shortest distance layer by layer.
- Approach: Multi-Source BFS
- Algorithm:
  1. Initialize a queue with all cells containing 0. Mark them as visited.
  2. Use the input `mat` to store results; distances for 0s are 0.
  3. While the queue is not empty, dequeue a cell (x, y).
  4. For each unvisited neighbor (nx, ny), set its distance to mat[x][y] + 1,
     mark it visited, and enqueue it.
- Time complexity: O(m*n). Each cell is visited and processed exactly once.
- Space complexity: O(m*n) for the BFS queue and the visited array.

💡 Key Pattern:
- Shortest path in an unweighted grid: Always use Breadth-First Search (BFS).
- Finding distance from multiple sources: Use Multi-Source BFS.

ℹ️ Keywords:
- BFS, Multi-Source, Grid, Shortest Path, Distance

🗒️ Notes
- The initial `mat` is reused to store the results, which is a common optimization.
- The `visited` array is necessary to ensure we process cells only once.
----------------------------------------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    /**
     * @brief Computes the distance of the nearest 0 for every cell in the matrix.
     * @param mat The input m x n binary matrix (will be modified in place).
     * @return The updated matrix containing the shortest distance to the nearest 0.
     */
    vector<vector<int>> updateMatrix(vector<vector<int>> &mat)
    {
        int m = mat.size();
        int n = mat[0].size();

        // Queue for Multi-Source BFS, storing coordinates {row, col}
        queue<pair<int, int>> q;

        // Visited array to prevent cycles and redundant processing
        vector<vector<bool>> visited(m, vector<bool>(n, false));

        // 1. Initialize BFS: Add all '0' cells as starting points
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (mat[i][j] == 0)
                {
                    q.push({i, j});
                    visited[i][j] = true;
                }
                // We don't need to initialize '1' cells to infinity if we rely
                // solely on the 'visited' array and the BFS layers.
            }
        }

        // Standard directions for 4-directional movement (up, down, left, right)
        int dirs[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

        // 2. Multi-Source BFS
        while (!q.empty())
        {
            // Use structured binding for cleaner coordinate access
            auto [x, y] = q.front();
            q.pop();

            // Explore 4 neighbors
            for (auto &d : dirs)
            {
                int nx = x + d[0], ny = y + d[1];

                // Check boundary conditions and visited status
                if (nx >= 0 && nx < m && ny >= 0 && ny < n &&
                    !visited[nx][ny])
                {
                    // Distance is 1 + distance of the current cell
                    mat[nx][ny] = mat[x][y] + 1;

                    // Enqueue the new cell and mark it visited
                    q.push({nx, ny});
                    visited[nx][ny] = true;
                }
            }
        }

        return mat;
    }
};

// Helper function to print the matrix for testing
void printMatrix(const vector<vector<int>> &mat)
{
    for (const auto &row : mat)
    {
        for (int val : row)
        {
            cout << val << " ";
        }
        cout << endl;
    }
}

int main()
{
    Solution sol;

    // Example 2 Test Case
    vector<vector<int>> mat2 = {{0, 0, 0}, {0, 1, 0}, {1, 1, 1}};
    cout << "Input Matrix:" << endl;
    printMatrix(mat2);

    vector<vector<int>> result2 = sol.updateMatrix(mat2);

    cout << "\nOutput Matrix (Expected: [[0,0,0],[0,1,0],[1,2,1]]):" << endl;
    printMatrix(result2);

    return 0;
}
