/*
File: Valid_Sudoku.cpp
Date: 2025-10-16 12:28

Problem: Valid Sudoku
Link: https://leetcode.com/problems/valid-sudoku/description/

Problem Statement:
Determine if a 9x9 Sudoku board is valid. Only the filled cells need to be
validated according to the following rules:
1. Each row must contain the digits 1-9 without repetition.
2. Each column must contain the digits 1-9 without repetition.
3. Each of the nine 3x3 sub-boxes must contain the digits 1-9 without repetition.
Note: The board may contain partially filled cells, represented by the '.'
character. A valid Sudoku board (not necessarily solvable) is returned.

----------------------------------------------------------------------------------
❌ Brute Force
- Idea: Iterate through the board three times: once to check all 9 rows, once to
  check all 9 columns, and a third time to check all 9 3x3 sub-boxes. Each check
  requires a separate loop and a local hash set or boolean array.
- Time complexity: O(N^3) or O(9*3 * N^2) which simplifies to O(1) in terms of
  big-O notation since N=9 (board size is fixed). More precisely, O(3 * N^2).
- Space complexity: O(N) or O(1) for the local hash sets used within each check.
- Limitations: Inefficient due to three separate full board passes.

✅ Optimized Approachs
- Idea: Check all three constraints (row, column, and 3x3 box) simultaneously
  in a single pass over the board. This is achieved by generating a unique string
  identifier for each constraint violation.
- Approach: Single-Pass Iteration with Unique String Hashing (Set).
- Algorithm:
  1. Initialize a global `unordered_set<string>` called `seen`.
  2. Iterate through the board from i=0 to 8 (rows) and j=0 to 8 (columns).
  3. For every non-empty cell `c = board[i][j]`, generate three unique strings:
     - Row: `c in row i`
     - Col: `c in col j`
     - Box: `c in box i/3-j/3` (i/3 and j/3 define the 3x3 box index).
  4. If any of these three strings is already in `seen`, the board is invalid.
  5. Otherwise, insert all three strings into `seen`.
  6. If the loop completes, the board is valid.
- Time complexity: O(N^2). Since N=9 is fixed, the time complexity is O(1) or
  exactly 81 operations (plus set operations), which is highly efficient.
- Space complexity: O(N^2). In the worst case, we store 3 * 81 unique strings
  in the hash set, which is constant O(1).

💡 Key Pattern:
- **Constraint Hashing:** Use unique, descriptive strings (or tuples) as keys
  in a hash set to simultaneously track multiple independent constraints (like
  row, column, and block) in a single pass, making the solution very clean.

ℹ️ Keywords:
- Hash Set, Array, Matrix, Single Pass, Constraint Checking, Constant Time O(1)

🗒️ Notes
- The use of integer division `i/3` and `j/3` correctly calculates the 0-8 index
  of the 3x3 sub-box (e.g., box (0,0), (0,1), ..., (2,2)).
- The space used is proportional to the number of cells, but since the board
  size is fixed at 9x9, both time and space are technically O(1).
----------------------------------------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    /**
     * @brief Determines if the partially filled 9x9 Sudoku board is valid
     * based on rows, columns, and 3x3 sub-boxes.
     * @param board The 9x9 vector of characters representing the Sudoku board.
     * @return True if the board is valid, false otherwise.
     */
    bool isValidSudoku(vector<vector<char>> &board)
    {
        // Hash set to store unique constraints seen so far.
        // Format: "digit in row i", "digit in col j", "digit in box i/3-j/3"
        unordered_set<string> seen;

        for (int i = 0; i < 9; ++i)
        {
            for (int j = 0; j < 9; ++j)
            {
                char c = board[i][j];

                // Skip empty cells
                if (c == '.')
                    continue;

                // 1. Row Constraint
                string row = string(1, c) + " in row " + to_string(i);

                // 2. Column Constraint
                string col = string(1, c) + " in col " + to_string(j);

                // 3. 3x3 Box Constraint (i/3 and j/3 calculate the box index)
                string box = string(1, c) + " in box " + to_string(i / 3) + "-" + to_string(j / 3);

                // Check for duplicates in any of the three constraints
                if (seen.count(row) || seen.count(col) || seen.count(box))
                    return false;

                // If unique, store all three constraints
                seen.insert(row);
                seen.insert(col);
                seen.insert(box);
            }
        }
        return true;
    }
};

int main()
{
    Solution sol;

    // --- Test Case 1: Valid Sudoku Board (Example from LeetCode)
    vector<vector<char>> board1 = {
        {'5', '3', '.', '.', '7', '.', '.', '.', '.'},
        {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
        {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
        {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
        {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
        {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
        {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
        {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
        {'.', '.', '.', '.', '8', '.', '.', '7', '9'}};
    cout << "Board 1 (Expected: True): " << (sol.isValidSudoku(board1) ? "Valid" : "Invalid") << endl;

    // --- Test Case 2: Invalid Row (Repetitive '8' in row 0)
    vector<vector<char>> board2 = {
        {'8', '8', '.', '.', '7', '.', '.', '.', '.'}, // Repetitive '8'
        {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
        {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
        {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
        {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
        {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
        {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
        {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
        {'.', '.', '.', '.', '8', '.', '.', '7', '9'}};
    cout << "Board 2 (Expected: False): " << (sol.isValidSudoku(board2) ? "Valid" : "Invalid") << endl;

    // --- Test Case 3: Invalid 3x3 Box (Repetitive '9' in top-left box)
    vector<vector<char>> board3 = {
        {'5', '3', '.', '.', '7', '.', '.', '.', '.'},
        {'6', '9', '.', '1', '9', '5', '.', '.', '.'}, // Repetitive '9' (row 1, col 1) vs '9' (row 1, col 3) - but only in the top-left box is the error
        {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
        {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
        {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
        {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
        {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
        {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
        {'.', '.', '.', '.', '8', '.', '.', '7', '9'}};
    cout << "Board 3 (Expected: False): " << (sol.isValidSudoku(board3) ? "Valid" : "Invalid") << endl;

    return 0;
}
