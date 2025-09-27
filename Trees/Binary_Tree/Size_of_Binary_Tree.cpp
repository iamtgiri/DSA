/*
File: Size_of_Binary_Tree.cpp
Date: 2025-09-27 10:30

Problem: Size of Binary Tree
Link: https://www.geeksforgeeks.org/problems/size-of-binary-tree/1

Problem Statement:
Given the root of a binary tree, find and return the total number of nodes.

-------------------------------------------------
❌ Brute Force
- Idea: The size of a tree is inherently a full traversal problem.
  The most intuitive solution (simple recursion) is already optimal.
- Time complexity: O(N), where N is the number of nodes.
- Space complexity: O(H), where H is the height of the tree (recursion stack).
- Limitations: None, but it is the baseline for efficiency.

✅ Optimized Approachs
- Idea: Count every node exactly once using tree traversal (DFS or BFS).
  The size is $1 + \text{size}(\text{left}) + \text{size}(\text{right})$.
- Approach: Depth-First Search (DFS) via recursion is simplest.
  Breadth-First Search (BFS) via iteration is also O(N).
- Algorithm:
    - Recursive (DFS): Base case returns 0 for null. Returns $1 + \text{recursive}$
      calls on left and right children.
    - Iterative (BFS): Use a queue; initialize count to 0. Enqueue root.
      While queue is not empty, dequeue node, increment count, and enqueue
      its non-null children.
- Time complexity: O(N) for both, as every node is visited exactly once.
- Space complexity:
    - Recursive: O(H) for recursion stack.
    - Iterative: O(W) for queue, where W is the max width (up to O(N)).

💡 Key Pattern:
- Tree Traversal (DFS/BFS)
- Divide and Conquer using recursion.

ℹ️ Keywords:
- Binary Tree, Size, Count Nodes, DFS, BFS, Traversal, Recursion

🗒️ Notes
- (What did I learn? Similar problems? Mistakes I made?)
- I used two different ways to implement recursion: one passing count
  by reference, and the other returning the count. The latter is cleaner.
- The concept is similar to finding max depth, but we use addition
  instead of the max function: $\text{Size} = 1 + \text{Size}_{\text{left}} + \text{Size}_{\text{right}}$.
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
     * @brief Calculates the size of the binary tree using standard recursion (DFS).
     * @details The size is 1 (for the current node) + size of left subtree
     * + size of right subtree. This is the cleanest recursive approach.
     * @param root The root node of the binary tree.
     * @return The total number of nodes in the tree.
     */
    int getSizeRec(TreeNode *root)
    {
        // Base case: If the node is null, the size is 0.
        if (root == nullptr)
        {
            return 0;
        }
        // Recursive step: 1 (for current) + size of left subtree + size of right.
        return 1 + getSizeRec(root->left) + getSizeRec(root->right);
    }

    /**
     * @brief Calculates the size of the binary tree using iteration (BFS).
     * @details Uses a queue to perform level-order traversal and count nodes.
     * @param root The root node of the binary tree.
     * @return The total number of nodes in the tree.
     */
    int getSizeItr(TreeNode *root)
    {
        // If the tree is empty, size is 0.
        if (root == nullptr)
        {
            return 0;
        }

        // Use a queue for BFS and an integer to store the size.
        queue<TreeNode *> q;
        q.push(root);
        int count = 0;

        // Process nodes level by level.
        while (!q.empty())
        {
            // Get the front node and remove it.
            TreeNode *node = q.front();
            q.pop();

            // Increment the count for the current node.
            count++;

            // Enqueue non-null children for the next level.
            if (node->left)
            {
                q.push(node->left);
            }
            if (node->right)
            {
                q.push(node->right);
            }
        }
        return count;
    }

    // The user's original implementation using pass-by-reference.
    int getSizeByRef(TreeNode *node)
    {
        // Initializes count to 0 and calls the helper function.
        int count = 0;
        countNodesByRef(node, count);
        return count;
    }

private:
    // Helper function for the getSizeByRef method.
    void countNodesByRef(TreeNode *node, int &count)
    {
        // Base case.
        if (!node)
            return;
        // Pre-order processing: increment count.
        count++;
        // Recurse on children.
        countNodesByRef(node->left, count);
        countNodesByRef(node->right, count);
    }
};

int main()
{
    // Create a solution object.
    Solution sol;

    // Example 1: A tree of size 5.
    // Tree: 1 -> 2, 3 -> 4, 5
    //        1
    //       / \
    //      2   3
    //         / \
    //        4   5
    TreeNode *root1 = new TreeNode(1);
    root1->left = new TreeNode(2);
    root1->right = new TreeNode(3);
    root1->right->left = new TreeNode(4);
    root1->right->right = new TreeNode(5);

    cout << "Example 1 (Size 5):" << endl;
    cout << "Recursive (Standard): " << sol.getSizeRec(root1) << endl;
    cout << "Iterative (BFS): " << sol.getSizeItr(root1) << endl;
    cout << "Recursive (By Ref): " << sol.getSizeByRef(root1) << endl;
    cout << endl;

    // Example 2: A skewed tree of size 3.
    // Tree: 1 -> 2 -> 3
    //      1
    //       \
    //        2
    //         \
    //          3
    TreeNode *root2 = new TreeNode(1);
    root2->right = new TreeNode(2);
    root2->right->right = new TreeNode(3);

    cout << "Example 2 (Size 3):" << endl;
    cout << "Recursive (Standard): " << sol.getSizeRec(root2) << endl;
    cout << "Iterative (BFS): " << sol.getSizeItr(root2) << endl;
    cout << "Recursive (By Ref): " << sol.getSizeByRef(root2) << endl;
    cout << endl;

    // Clean up memory.
    delete root1->right->left;
    delete root1->right->right;
    delete root1->left;
    delete root1->right;
    delete root1;

    delete root2->right->right;
    delete root2->right;
    delete root2;

    return 0;
}
