/*
File: Binary_Tree_Paths.cpp
Date: 2025-10-08 19:18

Problem: Binary Tree Paths
Link: https://leetcode.com/problems/binary-tree-paths/description/

Problem Statement:
Given the root of a binary tree, return all root-to-leaf paths in any order.
A leaf is a node with no children. Each path should be returned as a string
where nodes are separated by "->".

-------------------------------------------------
❌ Brute Force
- Idea: Iteratively traverse the tree using a stack (DFS) or queue (BFS),
  keeping track of the full path string built so far for each node in the queue.
  When a node has no children, its path is complete and added to the result.
- Time complexity: O(N * L), where N is the number of nodes and L is the average
  path length (due to string concatenation/copying at each step).
- Space complexity: O(N * L) to store all path strings, plus O(H) for the stack/queue.
- Limitations: Iterative path building can be slightly more complex to manage
  than the recursive approach, but is fundamentally the same efficiency.

✅ Optimized Approachs
- Idea: Use Depth First Search (DFS) recursion. This naturally allows the path
  to be built and torn down as the function returns up the call stack (although
  here we pass a value copy of the string, which simplifies rollback).
- Approach: Recursive DFS (Pre-Order Traversal) with Path String Tracking
- Algorithm:
    1. Define a recursive helper function, addpaths(node, current_path, results).
    2. In the helper:
       a. Append the current node's value to current_path, preceding it with "->"
          if the path is not empty.
       b. Check if the current node is a leaf (no left or right child).
       c. If it is a leaf, push the final current_path string into the results vector.
       d. Otherwise, recursively call addpaths on the left child and the right child.
- Time complexity: O(N * L), where N is the number of nodes and L is the average
  length of a path. String creation/copying dominates the complexity.
- Space complexity: O(H * L), where H is the height of the tree (recursion stack
  depth) and L is the maximum path length (to store all generated path strings).

💡 Key Pattern:
- **DFS Pathfinding:** Recursion is ideal for root-to-leaf path problems, as the
  path state can be easily managed and updated during the descent.

ℹ️ Keywords:
- Binary Tree, DFS, Recursion, Root-to-Leaf, Path Tracking, String Manipulation

🗒️ Notes
- (What did I learn? Similar problems? Mistakes I made?)
- The key is handling the "->" separator correctly, ensuring it's not placed
  before the root node's value. Using `to_string` is essential for C++ integer-to-string conversion.
-------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

/**
 * @class TreeNode
 * @brief Represents a single node in a binary tree.
 * @param val The data value stored in the node.
 * @param left Pointer to the left child node.
 * @param right Pointer to the right child node.
 */
class TreeNode
{
public:
    // The integer value stored in the node.
    int val;
    // Pointer to the left child node.
    TreeNode *left;
    // Pointer to the right child node.
    TreeNode *right;

    /**
     * @brief Default constructor.
     * @details Initializes a new node with a value of 0 and both child
     * pointers set to nullptr.
     */
    TreeNode() : val(0), left(nullptr), right(nullptr) {}

    /**
     * @brief Constructor with value.
     * @param x The integer value to be stored in the node.
     * @details Initializes a new node with the given value and both child
     * pointers set to nullptr.
     */
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}

    /**
     * @brief Full constructor.
     * @param x The integer value for the node.
     * @param left A pointer to the left child node.
     * @param right A pointer to the right child node.
     * @details Initializes a new node with a value and pointers to its
     * left and right children.
     */
    TreeNode(int x, TreeNode *left, TreeNode *right)
        : val(x), left(left), right(right) {}
};

class Solution
{
private:
    /**
     * @brief Recursive helper function to perform DFS and construct paths.
     * @details Builds the path string as it descends and stores it when a leaf is reached.
     * @param root The current node in the traversal.
     * @param curr The path string built so far from the tree root to the current node's parent.
     * @param paths The vector to store the final root-to-leaf paths.
     */
    void addpaths(TreeNode *root, string curr, vector<string> &paths)
    {
        // Base case: If the node is null, stop.
        if (!root)
            return;

        // Add the separator "->" if this is not the root node of the current path (i.e., curr is not empty).
        if (!curr.empty())
            curr += "->";

        // Append the current node's value to the path.
        curr += to_string(root->val);

        // Leaf Node check: If both children are null, this is a root-to-leaf path.
        if (!root->left && !root->right)
        {
            paths.push_back(curr);
            return;
        }

        // Recurse on children. The string 'curr' is passed by value (copied) in C++,
        // so changes made in this call do not affect parallel branches.
        addpaths(root->left, curr, paths);
        addpaths(root->right, curr, paths);
    }

public:
    /**
     * @brief Finds all root-to-leaf paths in a binary tree.
     * @param root The root of the binary tree.
     * @return A vector of strings, where each string is a path from root to leaf.
     */
    vector<string> binaryTreePaths(TreeNode *root)
    {
        vector<string> paths;
        if (!root)
            return paths;

        // Start the recursive process with an empty path string.
        addpaths(root, "", paths);
        return paths;
    }
};

// Helper function to create a test tree
TreeNode *createTestTree()
{
    // Tree structure:
    //      1
    //     / \
    //    2   3
    //     \
    //      5
    // Root-to-leaf paths: "1->2->5", "1->3"

    TreeNode *node5 = new TreeNode(5);
    TreeNode *node2 = new TreeNode(2, nullptr, node5);
    TreeNode *node3 = new TreeNode(3);
    TreeNode *root = new TreeNode(1, node2, node3);

    return root;
}

int main()
{
    Solution sol;

    TreeNode *root = createTestTree();

    cout << "Binary Tree Paths:" << endl;
    vector<string> paths = sol.binaryTreePaths(root);

    // Expected: ["1->2->5", "1->3"]
    for (const string &path : paths)
    {
        cout << path << endl;
    }

    // Note: Memory deallocation omitted for brevity in simple test harness.

    return 0;
}
