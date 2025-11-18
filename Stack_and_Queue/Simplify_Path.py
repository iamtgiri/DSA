"""
File: Simplify_Path.py
Date: 2025-11-19 01:17

Problem: Simplify Path
Link: https://leetcode.com/problems/simplify-path/description/

Problem Statement:
Given a string path, which is an absolute path (starting with a slash '/') to a file or directory in a Unix-style file system, convert it to the simplified canonical path.

-------------------------------------------------
Brute Force (if any, ignore if not applicable)
- Idea: Repeatedly use string searching and replacement functions (or regular expressions) to clean up multiple slashes, resolve '.' directories, and then iteratively resolve '../' segments by removing the preceding directory.
- Time complexity: O(L^2) (due to costly, repeated string modifications and searching).
- Space complexity: O(L)
- Limitations: Inefficient and complex to handle the backtracking logic of '..' correctly with only string manipulation.

Current/Optimized Approach
- Idea: The problem inherently involves forward movement (entering a directory) and backward movement (leaving a directory via '..'). A **Stack** is the perfect data structure to model this behavior.
- Approach: **Tokenization and Stack Processing**
- Algorithm:
  1. Split the input `path` string into tokens using the '/' delimiter.
  2. Initialize an empty `stack` (list in Python) to store valid directory names.
  3. Iterate through each `part` (token):
     a. If the part is `.` or empty (`''` from consecutive slashes), ignore it (`continue`).
     b. If the part is `..`, check if the stack is not empty. If it's not, pop the top element (simulating moving up to the parent directory).
     c. Otherwise (the part is a valid directory name), push it onto the stack.
  4. Reconstruct the canonical path by joining the elements in the final stack with '/' and prefixing the result with the root '/'.
- Time complexity: **O(L)**, where L is the length of the input path. Splitting and iterating through the tokens is a linear time operation.
- Space complexity: **O(L)**, as the stack size is proportional to the number of valid directories in the path.

💡 Key Pattern:
- **Stack for Path Resolution/Backtracking**: Use a stack whenever an operation requires forward progression and potential 'undo' or 'backtracking' (like resolving `..` in a path, or matching parentheses).

ℹ️ Keywords:
- Stack, Canonical Path, Tokenization, Unix File System, Absolute Path.

🗒️ Notes
- Python's `path.split('/')` is very effective here, automatically handling multiple adjacent slashes by producing empty strings.
- The final path construction `'/'.join(stack)` handles the separation correctly, and the prefixing with `/` ensures the path is absolute, resolving the requirement that if the stack is empty (e.g., path was `/` or `/../`), it returns `/`.
-------------------------------------------------
"""

from typing import List, Optional, Any

class Solution:
    def simplifyPath(self, path: str) -> str:
        # 1. Tokenize the path by splitting on '/'
        parts = path.split('/')
        stack = []

        # 2. Process each token
        for p in parts:
            if p == '' or p == '.':
                # Ignore empty strings (from multiple slashes) and current directory '.'
                continue
            if p == '..':
                # Move up to the parent directory if possible
                if stack:
                    stack.pop()
            else:
                # Valid directory name
                stack.append(p)

        # 3. Reconstruct the path: join elements with '/' and prefix with '/'
        return '/' + '/'.join(stack)


if __name__ == "__main__":
    sol = Solution()
    
    # Test Case 1: Simple path with redundant slashes
    path1 = "/home//foo/"
    print(f"Path: {path1}\nResult: {sol.simplifyPath(path1)} (Expected: /home/foo)\n")

    # Test Case 2: Path with parent directory (..)
    path2 = "/a/./b/../../c/"
    print(f"Path: {path2}\nResult: {sol.simplifyPath(path2)} (Expected: /c)\n")

    # Test Case 3: Path starting with multiple parents (resolves to root)
    path3 = "/../"
    print(f"Path: {path3}\nResult: {sol.simplifyPath(path3)} (Expected: /)\n")

    # Test Case 4: Complex path
    path4 = "/home/user/documents/../files/./data//"
    print(f"Path: {path4}\nResult: {sol.simplifyPath(path4)} (Expected: /home/user/files/data)\n")
    
    # Test Case 5: Path with only '.' and '..'
    path5 = "/."
    print(f"Path: {path5}\nResult: {sol.simplifyPath(path5)} (Expected: /)\n")