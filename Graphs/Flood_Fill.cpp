/*
File: Flood_Fill.cpp
Date: 2025-10-13 18:48

Problem: Flood Fill
Link: https://leetcode.com/problems/flood-fill/description/

Problem Statement:
An image is represented by an m x n integer grid `image` where `image[i][j]`
represents the pixel value of the image.

You are also given three integers sr, sc, and color. You should perform a
flood fill on the image starting from the pixel `image[sr][sc]`.

To perform a flood fill, consider the starting pixel, plus any pixels
connected 4-directionally to the starting pixel of the same color as the
starting pixel, plus any pixels connected 4-directionally to those pixels
(also with the same color), and so on. Replace the color of all the
aforementioned pixels with `color`.

Return the modified image after performing the flood fill.
-------------------------------------------------
❌ Brute Force
- Similar to the Number of Provinces problem, a standard graph traversal
  is the optimal way to solve this. There isn't a significantly less
  efficient, yet still correct, "brute force" method.

✅ Optimized Approach (BFS)
- Idea: Treat the image grid as a graph where each pixel is a node. An edge
  exists between two pixels if they are adjacent (4-directionally) and have
  the same color.
- Approach: Start a Breadth-First Search (BFS) from the starting pixel
  `(sr, sc)`. Find all connected pixels that have the same initial color and
  change their color to the new `color`.
- Algorithm:
  1. Get the initial color of the starting pixel `(sr, sc)`.
  2. If the initial color is already the target color, do nothing.
  3. Create a queue and add the starting pixel `(sr, sc)`.
  4. Change the color of the starting pixel to the new `color`.
  5. While the queue is not empty:
     a. Dequeue a pixel.
     b. For each of its 4-directional neighbors:
     c. If a neighbor is within bounds and has the same original color,
        change its color and enqueue it.
  6. Return the modified image.
- Time complexity: O(m * n), where m and n are the dimensions of the image.
  In the worst case, we visit every pixel once.
- Space complexity: O(m * n). In the worst case, the queue could hold all
  pixels (e.g., a checkerboard pattern).

💡 Key Pattern:
- Using graph traversal (BFS or DFS) on a grid to find a connected region.
- This is a common pattern for problems like "number of islands" or mazes.

ℹ️ Keywords:
- Grid, Matrix, Graph, BFS, DFS, Flood Fill, Connected Components

🗒️ Notes
- This is a classic algorithm with applications in image processing.
- The base case check `if (tcolor == color)` is crucial to prevent an
  infinite loop if the starting pixel already has the new color.
-------------------------------------------------
*/

#include <iostream>
#include <vector>
#include <queue>
#include <utility>

using namespace std;

class Solution
{
public:
    /**
     * @brief Performs a flood fill on an image starting from a given pixel.
     * @param image The m x n image grid.
     * @param sr The starting row.
     * @param sc The starting column.
     * @param color The new color to fill with.
     * @return The modified image.
     */
    vector<vector<int>> floodFill(vector<vector<int>> &image, int sr, int sc, int color)
    {
        int originalColor = image[sr][sc];
        // If the start color is the same as the new color, no work is needed.
        if (originalColor == color)
        {
            return image;
        }

        int m = image.size();
        int n = image[0].size();
        queue<pair<int, int>> q;

        q.push({sr, sc});
        image[sr][sc] = color;

        // Define the 4 directions for neighbors (up, down, left, right).
        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};

        while (!q.empty())
        {
            pair<int, int> current = q.front();
            q.pop();

            // Explore the 4 neighbors.
            for (int i = 0; i < 4; ++i)
            {
                int newRow = current.first + dr[i];
                int newCol = current.second + dc[i];

                // Check if the neighbor is valid and has the original color.
                if (newRow >= 0 && newRow < m && newCol >= 0 && newCol < n &&
                    image[newRow][newCol] == originalColor)
                {
                    image[newRow][newCol] = color;
                    q.push({newRow, newCol});
                }
            }
        }
        return image;
    }
};

void printImage(const vector<vector<int>> &image)
{
    for (const auto &row : image)
    {
        for (int pixel : row)
        {
            cout << pixel << " ";
        }
        cout << endl;
    }
}

int main()
{
    Solution sol;

    // Example test case 1
    cout << "Test Case 1:" << endl;
    vector<vector<int>> image1 = {{1, 1, 1}, {1, 1, 0}, {1, 0, 1}};
    int sr1 = 1, sc1 = 1, color1 = 2;
    cout << "Original Image:" << endl;
    printImage(image1);
    vector<vector<int>> result1 = sol.floodFill(image1, sr1, sc1, color1);
    cout << "Modified Image:" << endl;
    printImage(result1);
    cout << "--------------------" << endl;

    // Example test case 2
    cout << "Test Case 2:" << endl;
    vector<vector<int>> image2 = {{0, 0, 0}, {0, 0, 0}};
    int sr2 = 0, sc2 = 0, color2 = 0;
    cout << "Original Image:" << endl;
    printImage(image2);
    vector<vector<int>> result2 = sol.floodFill(image2, sr2, sc2, color2);
    cout << "Modified Image (should be unchanged):" << endl;
    printImage(result2);
    cout << "--------------------" << endl;

    return 0;
}
