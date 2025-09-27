/*
File: Sum_of_Binary_Tree.cpp
Date: 2025-09-27 10:36

Problem: Sum of Binary Tree
Link: https://www.geeksforgeeks.org/problems/sum-of-binary-tree/1

Problem Statement:
Given the root of a binary tree, find the sum of all node values.

-------------------------------------------------
❌ Brute Force
- Idea: The problem requires visiting every node, so standard traversal
  (DFS or BFS) is already optimal. No less efficient brute-force exists.
- Time complexity: O(N)
- Space complexity: O(H) to O(N)
- Limitations: None.

✅ Optimized Approachs
- Idea: Traverse the tree and accumulate the value of each node.
  The sum of a tree is: $ \text{root.val} + \text{sum}(\text{left}) + \text{sum}(\text{right}) $.
- Approach: Depth-First Search (DFS) via recursion is the most concise.
- Algorithm:
    - Recursive (DFS): Base case returns 0 for a null node. Recursively
      sums the current node's value with the sums from its subtrees.
    - Iterative (BFS): Use a queue to visit nodes level-by-level,
      adding each node's value to a running total.
- Time complexity: O(N) for both approaches, as every node is visited once.
- Space complexity:
    - DFS: O(H) for recursion stack.
    - BFS: O(W) for queue, where W is the maximum width (up to O(N)).

💡 Key Pattern:
- Tree Traversal (DFS/BFS)
- Divide and Conquer / Reduction

ℹ️ Keywords:
- Binary Tree, Sum, DFS, BFS, Traversal, Recursion, long long

🗒️ Notes
- (What did I learn? Similar problems? Mistakes I made?)
- Used 'long long' for the return type to safely handle large sums.
- The structure is similar to size or max depth calculation.
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
     * @brief Calculates the sum of all node values using recursion (DFS).
     * @details Sum is $ \text{root.val} + \text{sum}(\text{left}) + \text{sum}(\text{right}) $.
     * @param root The root node of the binary tree.
     * @return The total sum of node values (using long long for safety).
     */
    long long sumBT(TreeNode *root)
    {
        // Base case: If the node is null, its contribution to the sum is 0.
        if (!root)
            return 0;

        // Recursive step: Sum current value with results from subtrees.
        return (long long)root->val + sumBT(root->left) + sumBT(root->right);
    }

    /**
     * @brief Calculates the sum of all node values using iteration (BFS).
     * @details Uses a queue to process nodes level-by-level and accumulate sum.
     * @param root The root node of the binary tree.
     * @return The total sum of node values (using long long for safety).
     */
    long long sumBT_Itr(TreeNode *root)
    {
        // If the tree is empty, the sum is 0.
        if (!root)
            return 0;

        // Use a queue for BFS and a variable to store the total sum.
        queue<TreeNode *> q;
        q.push(root);
        long long totalSum = 0;

        // Process nodes until the queue is empty.
        while (!q.empty())
        {
            // Get the front node and remove it.
            TreeNode *node = q.front();
            q.pop();

            // Add the current node's value to the total sum.
            totalSum += node->val;

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
        return totalSum;
    }
};

int main()
{
    // Create a solution object.
    Solution sol;

    // Example Tree: Sum = 1 + 2 + 3 + 4 + 5 = 15
    //        1
    //       / \
    //      2   3
    //         / \
    //        4   5
    TreeNode *root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->right->left = new TreeNode(4);
    root->right->right = new TreeNode(5);

    // Calculate and print the sums.
    cout << "Tree Sum (Recursive): " << sol.sumBT(root) << endl;     // Expected: 15
    cout << "Tree Sum (Iterative): " << sol.sumBT_Itr(root) << endl; // Expected: 15

    // Example Skewed Tree: Sum = 10 + 20 + 30 = 60
    //        10
    //          \
    //           20
    //             \
    //              30
    TreeNode *root2 = new TreeNode(10);
    root2->right = new TreeNode(20);
    root2->right->right = new TreeNode(30);

    // Calculate and print the sums.
    cout << "Skewed Tree Sum (Recursive): " << sol.sumBT(root2) << endl;     // Expected: 60
    cout << "Skewed Tree Sum (Iterative): " << sol.sumBT_Itr(root2) << endl; // Expected: 60

    // Clean up memory.
    delete root->right->left;
    delete root->right->right;
    delete root->left;
    delete root->right;
    delete root;

    delete root2->right->right;
    delete root2->right;
    delete root2;

    return 0;
}
