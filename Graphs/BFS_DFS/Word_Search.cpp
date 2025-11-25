/*
File: Word_Search.cpp
Date: 2025-11-25 08:48

Problem: Word Search
Link: https://www.geeksforgeeks.org/problems/word-search/1  

Problem Statement:
Given a 2D array (board) of characters and a word, determine if the word exists in the grid. The word can be constructed from letters of sequentially adjacent cells (horizontally or vertically). The same letter cell may not be used more than once.

-------------------------------------------------
Brute Force (if any, ignore if not applicable)
- Idea: While there isn't a simple O(N^3) brute force for graph/grid traversal, a naive recursive approach that fails to track visited cells would lead to infinite loops or highly redundant calculations, making it unusable.
- Limitations: Pathfinding problems require state tracking to avoid cycles.

Current/Optimized Approachs
- Idea: Treat the grid as a graph where each cell is a node and adjacent cells (up, down, left, right) are edges. Use Depth First Search (DFS) starting from every cell that matches the first letter of the word, and use backtracking to explore all valid paths.
- Approach: **Depth First Search (DFS) with Backtracking**
- Algorithm:
  1. Iterate through every cell (x, y) of the grid as a potential starting point.
  2. If the cell mat[x][y] matches the first character of the 'word', initiate DFS.
  3. **DFS Function:**
     a. **Base Case:** If the current index `idx` equals the length of 'word', the word has been found, return true.
     b. **Boundary/Mismatch Check:** Return false if (x, y) is out of bounds or mat[x][y] does not match word[idx].
     c. **Mark Visited:** Temporarily replace mat[x][y] with a unique character (e.g., '#') to prevent re-use in the current path.
     d. **Recursive Step:** Recursively call DFS for the four neighbors (up, down, left, right) for the next character (idx + 1).
     e. **Backtrack:** Before returning, restore mat[x][y] to its original value.
- Time complexity: **O(N * M * 4^L)** where N is rows, M is columns, and L is the length of the word. In the worst case, every cell (N*M) can start a search, and at each step, there are up to 4 choices for L steps.
- Space complexity: O(L) for the recursion stack depth (L is the length of the word).

💡 Key Pattern:
- **Backtracking on a Grid:** Used for combinatorial search problems on 2D arrays (like pathfinding, knight's tour, N-Queens) where choices must be undone to explore alternative paths.

ℹ️ Keywords:
- DFS, Backtracking, Grid Traversal, Pathfinding, Graph Search.

🗒️ Notes
- Using the board itself to mark visited cells (by changing the character to '#') is an efficient way to avoid using an extra O(N*M) boolean `visited` array. This is a common pattern in competitive programming for problems that modify the input grid temporarily.
- Remember to always restore the cell's original value during backtracking!
-------------------------------------------------
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Solution
{
private:
    /**
     * @brief Recursive DFS function to search for the remaining part of the word.
     * @param mat The character board (passed by reference to allow modification for visited marking).
     * @param word The target word string.
     * @param idx The index of the character in 'word' currently being sought.
     * @param x The current row index.
     * @param y The current column index.
     * @return True if the word is found starting from this cell, false otherwise.
     */
    bool dfs(vector<vector<char>> &mat, const string &word, int idx,
             int x, int y)
    {

        // Base Case 1: Word found
        if (idx == word.size())
            return true;

        int n = mat.size(), m = mat[0].size();

        // Base Case 2: Out of bounds
        if (x < 0 || x >= n || y < 0 || y >= m)
            return false;

        // Base Case 3: Character mismatch
        if (mat[x][y] != word[idx])
            return false;

        // Current cell matches word[idx]. Proceed with search.

        // 1. Mark as visited (Backtracking step: save and modify)
        char saved = mat[x][y];
        mat[x][y] = '#'; // Use '#' or any character not in the alphabet

        // 2. Define neighbors (up, down, left, right)
        static const int dx[] = {-1, 1, 0, 0};
        static const int dy[] = {0, 0, -1, 1};

        // 3. Explore neighbors
        for (int k = 0; k < 4; k++)
        {
            if (dfs(mat, word, idx + 1, x + dx[k], y + dy[k]))
            {
                // If any neighbor path returns true, we found the word.
                // Restore and return true.
                mat[x][y] = saved;
                return true;
            }
        }

        // 4. Backtrack: Restore the cell's original character
        mat[x][y] = saved;
        return false;
    }

public:
    /**
     * @brief Checks if the given word exists in the character matrix.
     * @param mat The character matrix (board).
     * @param word The word to search for.
     * @return True if the word exists, false otherwise.
     */
    bool isWordExist(vector<vector<char>> &mat, string &word)
    {
        if (word.empty())
            return true;
        if (mat.empty() || mat[0].empty())
            return false;

        // The DFS helper function expects the word as a const reference
        // but the input is a non-const reference, so we'll convert it for safety.
        const string &const_word = word;

        int n = mat.size();
        int m = mat[0].size();

        // Iterate through all possible starting cells
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < m; ++j)
            {
                // Only start DFS if the cell matches the first letter
                if (mat[i][j] == const_word[0])
                {
                    if (dfs(mat, const_word, 0, i, j))
                        return true;
                }
            }
        }

        return false;
    }
};

int main()
{
    Solution sol;

    // Test Case 1: Word exists (Path: A -> B -> C -> E -> S)
    vector<vector<char>> mat1 = {
        {'A', 'B', 'C', 'E'},
        {'S', 'F', 'C', 'S'},
        {'A', 'D', 'E', 'E'}};
    string word1 = "ABCCED";
    bool res1 = sol.isWordExist(mat1, word1);
    cout << "Board: 4x4, Word: " << word1 << endl;
    cout << "Result: " << (res1 ? "True" : "False") << " (Expected: True)" << endl;
    cout << "---" << endl;

    // Test Case 2: Word does not exist
    vector<vector<char>> mat2 = {
        {'A', 'B', 'C', 'E'},
        {'S', 'F', 'C', 'S'},
        {'A', 'D', 'E', 'E'}};
    string word2 = "SEE";
    bool res2 = sol.isWordExist(mat2, word2); // Should find S -> E (row 1, col 3 to row 2, col 3)
    cout << "Board: 4x4, Word: " << word2 << endl;
    cout << "Result: " << (res2 ? "True" : "False") << " (Expected: True)" << endl;
    cout << "---" << endl;

    // Test Case 3: Word does not exist (not enough contiguous path)
    vector<vector<char>> mat3 = {
        {'A', 'B', 'C', 'E'},
        {'S', 'F', 'C', 'S'},
        {'A', 'D', 'E', 'E'}};
    string word3 = "ABCB";
    bool res3 = sol.isWordExist(mat3, word3);
    cout << "Board: 4x4, Word: " << word3 << endl;
    cout << "Result: " << (res3 ? "True" : "False") << " (Expected: False)" << endl;

    return 0;
}