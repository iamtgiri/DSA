/*
File: Simplify_Path.cpp
Date: 2025-11-19 01:16

Problem: Simplify Path
Link: https://leetcode.com/problems/simplify-path/description/

Problem Statement:
Given a string path, which is an absolute path (starting with a slash '/') to a file or directory in a Unix-style file system, convert it to the simplified canonical path.

The canonical path should meet the following requirements:
1. It starts with a single slash '/'.
2. Any two directories are separated by a single slash '/'.
3. It does not end with a trailing '/'.
4. It only contains the names of the directories in the path (i.e., no '.', '..', or multiple consecutive slashes).

-------------------------------------------------
Brute Force (if any, ignore if not applicable)
- Idea: Repeatedly use string searching/replacement (e.g., regex) to clean up `//`, then `/.`, and finally resolve `../` by looking backward in the string.
- Time complexity: Highly dependent on string manipulation functions, likely O(L^2) or worse in some scenarios, where L is the path length.
- Space complexity: O(L)
- Limitations: Inefficient due to repeated string modifications and difficult to correctly handle the backtracking nature of `..`.

Current/Optimized Approachs
- Idea: A **Stack** naturally handles the forward movement (pushing a directory) and the backtracking/parent movement (popping for `..`).
- Approach: **Tokenization and Stack Processing**
- Algorithm:
  1. Use `stringstream` and `getline` to **tokenize** the input path by the '/' delimiter.
  2. Iterate through each token (`part`):
     a. **Ignore** `""` (empty string from multiple slashes) and `.` (current directory).
     b. If `part` is `..` (parent directory) and the stack is not empty, pop the last directory from the stack.
     c. Otherwise (if it's a valid directory name), push `part` onto the stack.
  3. **Reconstruct** the path by joining the elements in the stack with single slashes, prefixed by the root '/'. If the stack is empty, return "/".
- Time complexity: **O(L)**, where L is the length of the path string. We tokenize the string once and iterate through the tokens once.
- Space complexity: **O(D)**, where D is the number of valid directory names in the canonical path (at most O(L)).

💡 Key Pattern:
- **Stack for Backtracking/Resolution**: Use a stack whenever an operation involves forward progress that can be undone (e.g., function calls, path navigation, parenthesis matching).

ℹ️ Keywords:
- Stack, Canonical Path, Tokenization, Stringstream, Unix File System.

🗒️ Notes
- Using `std::stringstream` with `std::getline` is a clean way to split a string by a delimiter in C++.
- The implementation correctly handles edge cases like an empty path, multiple slashes, and paths consisting only of `..` (which resolves to `/`).
-------------------------------------------------
*/

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

class Solution
{
public:
    /**
     * @brief Converts an absolute Unix path to its simplified canonical form.
     * @param path The input absolute path string.
     * @return The simplified canonical path string.
     */
    string simplifyPath(string path)
    {
        // Use a vector as a stack to store the canonical directory names
        vector<string> stack;
        string part;
        // Use stringstream to easily split the path by '/'
        stringstream ss(path);

        while (getline(ss, part, '/'))
        {
            // Case 1: Ignore empty parts (from multiple slashes like //) or current directory (.)
            if (part == "" || part == ".")
            {
                continue;
            }
            // Case 2: Move up to the parent directory (..)
            if (part == "..")
            {
                if (!stack.empty())
                {
                    stack.pop_back(); // Go up one level
                }
            }
            // Case 3: Valid directory name
            else
            {
                stack.push_back(part); // Move down into a directory
            }
        }

        // Reconstruct the result path
        string result = "";
        for (const string &dir : stack)
        {
            result += "/" + dir;
        }

        // If the stack is empty (e.g., path was "/", "/.", "/.."), return just "/"
        return result.empty() ? "/" : result;
    }
};

int main()
{
    Solution sol;

    // Test Case 1: Simple path with redundant slashes
    string path1 = "/home//foo/";
    string result1 = sol.simplifyPath(path1);
    cout << "Path: " << path1 << "\nResult: " << result1 << " (Expected: /home/foo)\n"
         << endl; // Expected: /home/foo

    // Test Case 2: Path with parent directory (..)
    string path2 = "/a/./b/../../c/";
    string result2 = sol.simplifyPath(path2);
    cout << "Path: " << path2 << "\nResult: " << result2 << " (Expected: /c)\n"
         << endl; // Expected: /c

    // Test Case 3: Path starting with multiple parents (resolves to root)
    string path3 = "/../";
    string result3 = sol.simplifyPath(path3);
    cout << "Path: " << path3 << "\nResult: " << result3 << " (Expected: /)\n"
         << endl; // Expected: /

    // Test Case 4: Complex path
    string path4 = "/home/user/documents/../files/./data//";
    string result4 = sol.simplifyPath(path4);
    cout << "Path: " << path4 << "\nResult: " << result4 << " (Expected: /home/user/files/data)\n"
         << endl; // Expected: /home/user/files/data

    return 0;
}