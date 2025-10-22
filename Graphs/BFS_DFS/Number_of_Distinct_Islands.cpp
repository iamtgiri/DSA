/*
File: Number_of_Distinct_Islands.cpp
Date: 2025-10-22 15:16

Problem: Number of Distinct Islands
Link: https://www.geeksforgeeks.org/problems/number-of-distinct-islands/1

Problem Statement:
Given a boolean 2D matrix (grid) where 1 represents land and 0 represents water.
An island is a group of connected 1s (horizontally or vertically). Two islands are
considered distinct if they cannot be entirely translated to overlap with each other.
Return the number of distinct island shapes.

-------------------------------------------------
❌ Brute Force
- Idea: Find all islands using DFS/BFS and store their raw absolute coordinates.
- Time complexity: O(N * M)
- Space complexity: O(N * M)
- Limitations: Fails to recognize two identical shapes located at different positions as the same island. Requires coordinate normalization.

✅ Optimized Approachs
- Idea: Normalize the shape of each island by recording the coordinates of its cells relative to a fixed origin (the first cell found). This makes the shape translation-invariant.
- Approach: Depth First Search (DFS) or Breadth First Search (BFS) with Coordinate Normalization.
- Algorithm:
    1. Iterate over the grid. When an unvisited land cell (r0, c0) is found, start traversal.
    2. During traversal, for every cell (r, c), record the relative coordinate (r - r0, c - c0).
    3. Store the resulting sequence of relative coordinates (the shape) in a `std::set`.
    4. The size of the set gives the count of distinct islands.
- Time complexity: O(N * M), as every cell is visited once.
- Space complexity: O(N * M) for the visited array and storing the distinct shapes in the set.

💡 Key Pattern:
- **Normalization for Shape Uniqueness:** To ensure translation invariance, map all component coordinates to be relative to a canonical origin point (the starting cell of the island).

ℹ️ Keywords:
- Grid Traversal, DFS, BFS, Connected Components, Coordinate Offset, Set.

🗒️ Notes
- The order of coordinates pushed into the `shape` vector must be consistent (e.g., guaranteed by the fixed order of neighbor exploration in DFS/BFS) for the set to correctly identify identical shapes.
-------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    /**
     * @brief Helper function to traverse the island and record the shape relative to (r0, c0).
     */
    void dfs(int r, int c, vector<vector<int>> &grid, vector<vector<int>> &vis, vector<pair<int, int>> &shape, int r0, int c0)
    {
        int n = grid.size(), m = grid[0].size();
        vis[r][c] = 1;
        // Normalize coordinates and record the offset
        shape.push_back({r - r0, c - c0});

        // Directions: Down, Up, Right, Left (fixed order for consistent shape representation)
        int dr[] = {1, -1, 0, 0};
        int dc[] = {0, 0, 1, -1};

        for (int i = 0; i < 4; i++)
        {
            int nr = r + dr[i];
            int nc = c + dc[i];
            if (nr >= 0 && nr < n && nc >= 0 && nc < m &&
                !vis[nr][nc] && grid[nr][nc] == 1)
            {
                dfs(nr, nc, grid, vis, shape, r0, c0);
            }
        }
    }

    /**
     * @brief Counts distinct islands using Depth First Search (DFS).
     * @param grid The 2D matrix representing land (1) and water (0).
     * @return The count of distinct island shapes.
     */
    int countDistinctIslandsDFS(vector<vector<int>> &grid)
    {
        if (grid.empty() || grid[0].empty())
            return 0;
        int n = grid.size(), m = grid[0].size();

        vector<vector<int>> visited(n, vector<int>(m, 0));
        set<vector<pair<int, int>>> shapes;

        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < m; ++j)
            {
                if (grid[i][j] == 1 && !visited[i][j])
                {
                    vector<pair<int, int>> shape;
                    // i and j are the root coordinates (r0, c0) for this island
                    dfs(i, j, grid, visited, shape, i, j);
                    shapes.insert(shape);
                }
            }
        }
        return shapes.size();
    }

    /**
     * @brief Counts distinct islands using Breadth First Search (BFS).
     * @param grid The 2D matrix representing land (1) and water (0).
     * @return The count of distinct island shapes.
     */
    int countDistinctIslandsBFS(vector<vector<int>> &grid)
    {
        if (grid.empty() || grid[0].empty())
            return 0;
        int n = grid.size(), m = grid[0].size();
        vector<vector<int>> vis(n, vector<int>(m, 0));
        set<vector<pair<int, int>>> shapes;

        // Directions: up, down, left, right (fixed order for consistent shape)
        int dr[] = {1, -1, 0, 0};
        int dc[] = {0, 0, 1, -1};

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (grid[i][j] == 1 && !vis[i][j])
                {
                    vector<pair<int, int>> shape;
                    queue<pair<int, int>> q;
                    q.push({i, j});
                    vis[i][j] = 1;
                    int r0 = i, c0 = j; // Root coordinates for normalization

                    while (!q.empty())
                    {
                        auto [r, c] = q.front();
                        q.pop();

                        // Normalize and record
                        shape.push_back({r - r0, c - c0});

                        for (int k = 0; k < 4; k++)
                        {
                            int nr = r + dr[k];
                            int nc = c + dc[k];
                            if (nr >= 0 && nr < n && nc >= 0 && nc < m &&
                                !vis[nr][nc] && grid[nr][nc] == 1)
                            {
                                vis[nr][nc] = 1;
                                q.push({nr, nc});
                            }
                        }
                    }
                    shapes.insert(shape);
                }
            }
        }
        return shapes.size();
    }
};

int main()
{
    Solution sol;

    // Test Case 1: Two identical square islands -> Should count as 1
    vector<vector<int>> grid1 = {
        {1, 1, 0, 0, 0},
        {1, 1, 0, 0, 0},
        {0, 0, 0, 1, 1},
        {0, 0, 0, 1, 1}};
    cout << "Test 1 (Identical Squares): " << sol.countDistinctIslandsDFS(grid1) << " (Expected: 1)" << endl;

    // Test Case 2: Two distinct L-shapes -> Should count as 2
    // Island A (top-left): Tall L-shape
    // Island B (bottom-right): T-shape
    vector<vector<int>> grid2 = {
        {1, 0, 0, 0, 0},
        {1, 0, 0, 0, 0},
        {1, 1, 0, 0, 0},
        {0, 0, 0, 1, 1},
        {0, 0, 0, 1, 0},
        {0, 0, 0, 1, 0}};
    cout << "Test 2 (Distinct Shapes): " << sol.countDistinctIslandsDFS(grid2) << " (Expected: 2)" << endl;

    // Test Case 3: One single complex island
    vector<vector<int>> grid3 = {
        {1, 1, 1, 0},
        {1, 0, 1, 0},
        {1, 1, 1, 0},
        {0, 0, 0, 0}};
    cout << "Test 3 (Single Complex Shape): " << sol.countDistinctIslandsDFS(grid3) << " (Expected: 1)" << endl;

    // Test Case 4: Island B is a reflection of Island A. Should still count as 2 distinct shapes
    // since the problem only accounts for translation, not rotation/reflection.
    vector<vector<int>> grid4 = {
        {1, 1, 0, 0, 0},
        {0, 1, 0, 0, 0},
        {0, 0, 0, 1, 1},
        {0, 0, 0, 1, 0}};
    cout << "Test 4 (Reflection, non-distinct): " << sol.countDistinctIslandsDFS(grid4) << " (Expected: 2)" << endl;

    return 0;
}
