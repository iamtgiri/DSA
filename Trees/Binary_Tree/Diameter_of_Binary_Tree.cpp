/*
File: Diameter_of_Binary_Tree.cpp
Date: 2025-09-29 00:43

Problem: Diameter of Binary Tree
Link: https://leetcode.com/problems/diameter-of-binary-tree/description/

Problem Statement:
Given the root of a binary tree, return the length of the diameter of the tree.
The diameter is the length of the longest path between any two nodes in a tree.
This path may or may not pass through the root. The length of a path between
two nodes is represented by the number of edges between them.

-------------------------------------------------
❌ Brute Force
- Idea: For every single node in the tree, calculate the maximum depth of
  its left subtree and its right subtree. The diameter passing through that
  node is $\text{LeftDepth} + \text{RightDepth}$. Track the maximum across all nodes.
- Time complexity: $\text{O}(N^2)$, as for each of the $N$ nodes, we traverse
  down to calculate depth, taking $\text{O}(N)$ time.
- Space complexity: $\text{O}(H)$ for the recursion stack.
- Limitations: Inefficient due to redundant calculations of height/depth.

✅ Optimized Approachs
- Idea: Calculate the **diameter** and the **height** simultaneously in a
  single bottom-up traversal.
- Approach: Depth-First Search (Post-order Traversal).
- Algorithm:
    1. Define a helper function $\text{height(node, diameter)}$ that returns the height
       of the current $\text{node}$.
    2. In the post-order step (after recursive calls):
        a. Calculate $\text{leftHeight}$ and $\text{rightHeight}$ from children.
        b. Update the global $\text{diameter}$: $\text{diameter} = \text{max(diameter, leftHeight + rightHeight)}$.
           (The path length passing through the current $\text{node}$ is $\text{leftHeight} + \text{rightHeight}$).
        c. Return the height of the current subtree: $1 + \text{max(leftHeight, rightHeight)}$.
- Time complexity: $\text{O}(N)$, as every node is visited exactly once.
- Space complexity: $\text{O}(H)$, where $H$ is the height of the tree (for recursion stack).

💡 Key Pattern:
- **Single Pass Optimization:** Combining two related calculations (height and
  diameter) into one post-order traversal to avoid $\text{O}(N^2)$ complexity.
- **Passing by Reference:** Using a reference variable ($\text{int \&diameter}$)
  to update the global maximum value across all recursive calls.

ℹ️ Keywords:
- Binary Tree, Diameter, Longest Path, Height, Depth, DFS, Post-order, Reference

🗒️ Notes
- (What did I learn? Similar problems? Mistakes I made?)
- The diameter does not necessarily pass through the root. It's the longest
  path passing through *any* node.
- The path length is the number of edges, so it is simply the sum of the
  heights of the left and right subtrees (not $1 + \text{left} + \text{right}$).
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
public:
    /**
     * @brief Public function to find the diameter of the binary tree.
     * @param root The root of the binary tree.
     * @return The length of the longest path (diameter) in the tree.
     */
    int diameterOfBinaryTree(TreeNode *root)
    {
        // Global variable to store the maximum diameter found so far.
        int diameter = 0;

        // The helper function is called primarily for its side effect of
        // updating 'diameter', though it also returns the tree height.
        height(root, diameter);

        return diameter;
    }

private:
    /**
     * @brief Recursively calculates the height of the subtree rooted at 'node'
     * while simultaneously updating the maximum 'diameter' found.
     * @param node The current node in the traversal.
     * @param diameter Reference to the global max diameter variable.
     * @return The height of the subtree rooted at 'node'.
     */
    int height(TreeNode *node, int &diameter)
    {
        // Base case: Height of an empty subtree is 0.
        if (!node)
            return 0;

        // Recursively calculate the height of the left and right subtrees.
        // This is the Post-order step.
        int leftHeight = height(node->left, diameter);
        int rightHeight = height(node->right, diameter);

        // Update the max diameter found. The diameter passing through the
        // current node is $\text{leftHeight} + \text{rightHeight}$.
        diameter = max(diameter, leftHeight + rightHeight);

        // Return the height of the current node's subtree.
        return 1 + max(leftHeight, rightHeight);
    }
};

int main()
{
    Solution sol;

    // Test Case 1: Diameter = 3
    //      1
    //     / \
    //    2   3
    //   / \
    //  4   5
    TreeNode *root1 = new TreeNode(1,
                                   new TreeNode(2, new TreeNode(4), new TreeNode(5)),
                                   new TreeNode(3));

    cout << "Diameter of Tree 1 (Expected 3): "
         << sol.diameterOfBinaryTree(root1) << endl;

    // Test Case 2: Diameter = 4
    //      1
    //       \
    //        2
    //       / \
    //      3   4
    //     /    \
    //    5     11
    TreeNode *root2 = new TreeNode(1, nullptr,
                                   new TreeNode(2, new TreeNode(3, new TreeNode(5), nullptr), new TreeNode(4, nullptr, new TreeNode(11))));

    cout << "Diameter of Tree 2 (Expected 4): "
         << sol.diameterOfBinaryTree(root2) << endl;

    return 0;
}
