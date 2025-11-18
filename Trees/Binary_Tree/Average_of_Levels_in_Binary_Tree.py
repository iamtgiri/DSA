"""
File: Average_of_Levels_in_Binary_Tree.py
Date: 2025-11-19 00:41

Problem: Average of Levels in Binary Tree
Link: https://leetcode.com/problems/average-of-levels-in-binary-tree/description/

Problem Statement:
Given the root of a binary tree, return the average value of the nodes on each level in the form of an array. Answers within 10^-5 of the actual answer will be accepted.

-------------------------------------------------
Brute Force (if any, ignore if not applicable)
- Idea: Depth-First Search (DFS) / Recursive Pre-order. Collect node values into lists indexed by level, and then iterate through the lists to calculate the average.
- Time complexity: O(N) (Visit every node once).
- Space complexity: O(N) for recursion stack and storing all node values.
- Limitations: Requires extra logic (a map or list of lists) to group nodes by level, making it less direct than BFS.

Current/Optimized Approach
- Idea: Use **Level Order Traversal (BFS)** to process the tree layer by layer, which naturally groups all nodes belonging to the same level together.
- Approach: **Breadth-First Search (BFS) with Queue**
- Algorithm:
  1. Initialize a result list and a queue (using `deque`) containing only the `root`.
  2. While the queue is not empty:
     a. Get the `level_count` (the current size of the queue). This isolates the nodes of the current level.
     b. Initialize `level_sum = 0`.
     c. Iterate `level_count` times:
        i. Dequeue a `node`.
        ii. Add `node.val` to `level_sum`.
        iii. Enqueue the node's children (`node.left` and `node.right`) if they exist.
     d. Calculate the average (`level_sum / level_count`) and append it to the result list.
- Time complexity: **O(N)**. Every node is enqueued and dequeued exactly once.
- Space complexity: **O(W)**, where W is the maximum width of the tree (which can be up to O(N) in the worst case, e.g., a complete tree).

💡 Key Pattern:
- **Level Order Traversal:** This pattern is essential for any problem requiring processing or calculations based on the **depth or level** of a binary tree.

ℹ️ Keywords:
- BFS, Queue, Level Order, Traversal, Binary Tree, Average.

🗒️ Notes
- Python automatically handles large number sums and division with floats, ensuring the required precision is met.
- Using `collections.deque` is preferred over a standard list for queue operations (pop/append from opposite ends) as it provides O(1) time complexity.
-------------------------------------------------
"""

from typing import List, Optional, Any
from collections import deque

# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class Solution:
    def averageOfLevels(self, root: Optional[TreeNode]) -> List[float]:
        if not root:
            return []
        
        result = []
        # Use deque for O(1) append and pop operations
        queue = deque([root])
        
        while queue:
            level_sum = 0
            # Get the number of nodes in the current level
            level_count = len(queue)
            
            # Process all nodes in the current level
            for _ in range(level_count):
                node = queue.popleft()
                level_sum += node.val
                
                # Add children to the queue for the next level
                if node.left:
                    queue.append(node.left)
                if node.right:
                    queue.append(node.right)
                    
            # Calculate the average and append it to the result
            result.append(level_sum / level_count)
        
        return result

# Helper function to build a tree from a list (similar to LeetCode's format)
def build_tree(nodes: List[Optional[int]]) -> Optional[TreeNode]:
    if not nodes:
        return None
    
    root = TreeNode(nodes[0])
    queue = deque([root])
    i = 1
    
    while queue and i < len(nodes):
        parent = queue.popleft()
        
        # Left child
        if i < len(nodes) and nodes[i] is not None:
            parent.left = TreeNode(nodes[i])
            queue.append(parent.left)
        i += 1
        
        # Right child
        if i < len(nodes) and nodes[i] is not None:
            parent.right = TreeNode(nodes[i])
            queue.append(parent.right)
        i += 1
        
    return root


if __name__ == "__main__":
    sol = Solution()
    
    # Example 1: [3, 9, 20, None, None, 15, 7]
    # Level 0: 3 / 1 = 3.0
    # Level 1: (9 + 20) / 2 = 14.5
    # Level 2: (15 + 7) / 2 = 11.0
    nodes1 = [3, 9, 20, None, None, 15, 7]
    root1 = build_tree(nodes1)
    result1 = sol.averageOfLevels(root1)
    print(f"Input: {nodes1}")
    print(f"Output: {result1}")
    print(f"Expected: [3.0, 14.5, 11.0]")
    
    print("-" * 20)
    
    # Example 2: [2147483647, 2147483647, 2147483647] (Testing large numbers)
    # Level 0: 2147483647.0
    # Level 1: 2147483647.0
    MAX_INT = 2147483647
    nodes2 = [MAX_INT, MAX_INT, MAX_INT]
    root2 = build_tree(nodes2)
    result2 = sol.averageOfLevels(root2)
    print(f"Input: {nodes2}")
    print(f"Output: {result2}")
    # Python will use standard float representation for the large number
    print(f"Expected: [{float(MAX_INT)}, {float(MAX_INT)}]")