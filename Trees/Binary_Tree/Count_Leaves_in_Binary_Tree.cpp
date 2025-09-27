/*
File: Count_Leaves_in_Binary_Tree.cpp
Date: 2025-09-27 10:43

Problem: Count Leaves in Binary Tree
Link: https://www.geeksforgeeks.org/problems/count-leaves-in-binary-tree/1

Problem Statement:
Given the root of a binary tree, find and return the total number of
leaf nodes. A leaf is a node with no left or right children.

-------------------------------------------------
❌ Brute Force
- Idea: The most straightforward way is to traverse every node.
  Since all nodes must be checked, this is already the optimal approach.
- Time complexity: O(N), where N is the number of nodes.
- Space complexity: O(H) (recursion stack).
- Limitations: None, serves as the baseline.

✅ Optimized Approachs
- Idea: Use tree traversal (DFS or BFS) and count nodes that satisfy
  the leaf condition: $\text{node.left} == \text{nullptr}$ AND $\text{node.right} == \text{nullptr}$.
- Approach: Depth-First Search (DFS) via recursion is the most idiomatic.
- Algorithm:
    - Recursive (DFS): Base case returns 0 for null. If $\text{node.left}$
      and $\text{node.right}$ are null, return 1. Else, return sum of
      recursive calls on children.
    - Iterative (BFS): Use a queue; check the leaf condition on dequeue.
- Time complexity: O(N) for both approaches.
- Space complexity:
    - DFS: O(H) for recursion stack.
    - BFS: O(W) for queue, where W is the maximum width (up to O(N)).

💡 Key Pattern:
- Tree Traversal (DFS/BFS)
- Base case check on leaf node condition.

ℹ️ Keywords:
- Binary Tree, Leaf Node, Count, Traversal, Recursion, BFS

🗒️ Notes
- (What did I learn? Similar problems? Mistakes I made?)
- This problem closely mirrors finding the size of a tree, but the base
  case logic is adjusted: $1 + \dots$ is only added for leaf nodes.
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
     * @brief Counts the number of leaf nodes using recursion (DFS).
     * @details The count is the sum of leaf counts from the left and
     * right subtrees, plus 1 if the current node is a leaf.
     * @param root The root node of the binary tree.
     * @return The total number of leaf nodes.
     */
    int countLeavesRec(TreeNode *root)
    {
        // Base case 1: If the node is null, there are no leaves here.
        if (!root)
            return 0;
        // Base case 2: If the node has no children, it is a leaf.
        else if (!root->left && !root->right)
            return 1;
        // Recursive step: Sum the leaf counts from both subtrees.
        else
            return countLeavesRec(root->left) + countLeavesRec(root->right);
    }

    /**
     * @brief Counts the number of leaf nodes using iteration (BFS).
     * @details Uses a queue to traverse level-by-level, checking the
     * leaf condition on each node.
     * @param root The root node of the binary tree.
     * @return The total number of leaf nodes.
     */
    int countLeavesItr(TreeNode *root)
    {
        // Handle empty tree case.
        if (!root)
        {
            return 0;
        }

        // Use a queue for BFS and initialize the leaf counter.
        queue<TreeNode *> q;
        q.push(root);
        int leafCount = 0;

        // Process nodes until the queue is empty.
        while (!q.empty())
        {
            TreeNode *node = q.front();
            q.pop();

            // Check if the current node is a leaf.
            if (!node->left && !node->right)
            {
                leafCount++;
            }

            // Enqueue non-null children.
            if (node->left)
            {
                q.push(node->left);
            }
            if (node->right)
            {
                q.push(node->right);
            }
        }
        return leafCount;
    }
};

int main()
{
    // Create a solution object.
    Solution sol;

    // Example 1: Tree with 3 leaves (4, 5, 7)
    //        1
    //       / \
    //      2   3
    //     / \   \
    //    4   5   6
    //           /
    //          7
    TreeNode *root1 = new TreeNode(1);
    root1->left = new TreeNode(2);
    root1->right = new TreeNode(3);
    root1->left->left = new TreeNode(4);  // Leaf
    root1->left->right = new TreeNode(5); // Leaf
    root1->right->right = new TreeNode(6);
    root1->right->right->left = new TreeNode(7); // Leaf

    cout << "Example 1 (3 leaves):" << endl;
    cout << "Recursive Count: " << sol.countLeavesRec(root1) << endl;
    cout << "Iterative Count: " << sol.countLeavesItr(root1) << endl;
    cout << endl;

    // Example 2: Skewed Tree with 1 leaf (30)
    //        10
    //          \
    //           20
    //             \
    //              30
    TreeNode *root2 = new TreeNode(10);
    root2->right = new TreeNode(20);
    root2->right->right = new TreeNode(30); // Leaf

    cout << "Example 2 (1 leaf):" << endl;
    cout << "Recursive Count: " << sol.countLeavesRec(root2) << endl;
    cout << "Iterative Count: " << sol.countLeavesItr(root2) << endl;
    cout << endl;

    // Clean up memory.
    delete root1->left->left;
    delete root1->left->right;
    delete root1->right->right->left;
    delete root1->right->right;
    delete root1->left;
    delete root1->right;
    delete root1;

    delete root2->right->right;
    delete root2->right;
    delete root2;

    return 0;
}
