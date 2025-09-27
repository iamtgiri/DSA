/*
File: Height_of_Binary_Tree.cpp
Date: 2025-09-26 11:03

Problem: Maximum Depth of Binary Tree
Link: https://leetcode.com/problems/maximum-depth-of-binary-tree/description/

Problem Statement:
Given the root of a binary tree, return its maximum depth.
A binary tree's maximum depth is the number of nodes along the
longest path from the root node down to the farthest leaf node.

-------------------------------------------------
❌ Brute Force
- Idea: The problem is inherently a traversal problem, so there is
  no "brute-force" approach that is less efficient than a standard
  traversal. The recursive and iterative solutions are the most
  common and optimal.
- Time complexity: O(N)
- Space complexity: O(H) to O(N) depending on the tree structure.
- Limitations: None.

✅ Optimized Approachs
- Idea: Two main approaches can be used:
    1. Depth-First Search (DFS) using recursion.
    2. Breadth-First Search (BFS) using a queue.
- Approach:
    - Recursive (DFS): The depth of the tree is 1 plus the maximum
      depth of its left and right subtrees. This can be solved
      recursively.
    - Iterative (BFS): Traverse the tree level by level. The number
      of levels is the maximum depth.
- Algorithm:
    - Recursive:
        1. Base case: If the root is null, return 0.
        2. Recursive step: Return 1 + max(maxDepth(root->left),
           maxDepth(root->right)).
    - Iterative:
        1. Initialize a queue with the root node.
        2. Initialize a depth counter to 0.
        3. While the queue is not empty:
            a. Increment the depth counter.
            b. Process all nodes at the current level.
            c. Add the children of the current level's nodes to the queue.
        4. Return the final depth counter.
- Time complexity: O(N) for both approaches, as every node is visited once.
- Space complexity:
    - DFS: O(H), where H is the height of the tree, for the recursion
      stack. In a skewed tree, this can be O(N).
    - BFS: O(W), where W is the maximum width of the tree, for the
      queue. In a balanced tree, this can be O(N).

💡 Key Pattern:
- Tree Traversal (DFS and BFS)
- Recursion
- Breadth-First Search (Level-Order Traversal)

ℹ️ Keywords:
- Binary Tree, Depth, LeetCode, DFS, BFS, Traversal, Recursion

🗒️ Notes
- (What did I learn? Similar problems? Mistakes I made?)
- The iterative solution using BFS is good for finding the depth.
  I need to be careful with the loop for processing each level.
- Mistakes: I initially returned the depth inside the while loop in
  the iterative approach, causing an incorrect result. It must be
  returned after the loop completes.
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
     * @brief Calculates the maximum depth of a binary tree using recursion (DFS).
     * @param root The root node of the binary tree.
     * @return The maximum depth of the tree.
     */
    int maxDepthRec(TreeNode *root)
    {
        // Base case: if the current node is null, the depth is 0.
        if (root == nullptr)
            return 0;
        // The depth is 1 (for the current node) plus the maximum
        // depth of its left or right subtree.
        return 1 + max(maxDepthRec(root->left), maxDepthRec(root->right));
    }

    /**
     * @brief Calculates the maximum depth of a binary tree using iteration (BFS).
     * @param root The root node of the binary tree.
     * @return The maximum depth of the tree.
     */
    int maxDepthItr(TreeNode *root)
    {
        // If the tree is empty, the depth is 0.
        if (root == nullptr)
            return 0;

        // Use a queue for level-order traversal (BFS).
        queue<TreeNode *> q;
        // Push the root node into the queue.
        q.push(root);
        // Initialize the depth counter.
        int h = 0;

        // Continue the traversal as long as there are nodes in the queue.
        while (!q.empty())
        {
            // Increment the depth for each level.
            ++h;
            // Get the number of nodes at the current level.
            int size = q.size();
            // Process all nodes at the current level.
            for (int i = 0; i < size; i++)
            {
                // Get the node at the front of the queue.
                TreeNode *node = q.front();
                // Pop the node from the queue.
                q.pop();
                // If the left child exists, push it to the queue.
                if (node->left)
                    q.push(node->left);
                // If the right child exists, push it to the queue.
                if (node->right)
                    q.push(node->right);
            }
        }
        // Return the final depth after traversing all levels.
        return h;
    }
};

int main()
{
    // Create a solution object to access the methods.
    Solution sol;

    // Example 1:
    // Tree: 3 -> 9, 20 -> 15, 7
    TreeNode *root1 = new TreeNode(3);
    root1->left = new TreeNode(9);
    root1->right = new TreeNode(20);
    root1->right->left = new TreeNode(15);
    root1->right->right = new TreeNode(7);

    // Call the recursive and iterative methods.
    int depthRec1 = sol.maxDepthRec(root1);
    int depthItr1 = sol.maxDepthItr(root1);

    // Print the results.
    cout << "Example 1:" << endl;
    cout << "Maximum Depth (Recursive): " << depthRec1 << endl; // Expected: 3
    cout << "Maximum Depth (Iterative): " << depthItr1 << endl; // Expected: 3
    cout << endl;

    // Example 2:
    // Tree: 1 -> null, 2
    TreeNode *root2 = new TreeNode(1);
    root2->right = new TreeNode(2);

    // Call the recursive and iterative methods.
    int depthRec2 = sol.maxDepthRec(root2);
    int depthItr2 = sol.maxDepthItr(root2);

    // Print the results.
    cout << "Example 2:" << endl;
    cout << "Maximum Depth (Recursive): " << depthRec2 << endl; // Expected: 2
    cout << "Maximum Depth (Iterative): " << depthItr2 << endl; // Expected: 2
    cout << endl;

    // Clean up memory.
    delete root1->right->left;
    delete root1->right->right;
    delete root1->left;
    delete root1->right;
    delete root1;
    delete root2->right;
    delete root2;

    return 0;
}
