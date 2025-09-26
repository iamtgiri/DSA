/*
File: Balanced_Binary_Tree.cpp
Date: 2025-09-26 11:25

Problem: Balanced Binary Tree
Link: https://leetcode.com/problems/balanced-binary-tree/description/

Problem Statement:
Given a binary tree, determine if it is height-balanced.
A height-balanced binary tree is a tree in which the depth of the two
subtrees of every node never differs by more than one.

-------------------------------------------------
❌ Brute Force
- Idea: For each node, recursively calculate the height of its left
  and right subtrees. If the absolute difference of their heights
  is greater than 1, the tree is not balanced. This is done for
  every node from the root down.
- Time complexity: O(N^2) in the worst case (e.g., a skewed tree),
  as the 'height' function is called repeatedly for the same nodes.
- Space complexity: O(H) for the recursion stack, where H is the
  height of the tree.
- Limitations: Inefficient due to redundant calculations.

✅ Optimized Approachs
- Idea: Use a single recursive traversal (post-order) to check for
  balance and calculate the height simultaneously.
- Approach: A recursive function can return the height of the subtree
  it's currently processing. If at any point an imbalance is found,
  it returns a special value (e.g., -2) to indicate the imbalance
  and short-circuit the entire process.
- Algorithm:
    1. Define a helper function `checkBalanceAndHeight(node)`.
    2. Base case: If the node is null, return -1 (height of empty tree).
    3. Recursively call `checkBalanceAndHeight` on the left and right
       children.
    4. If the left or right call returns -2, an imbalance was already
       found, so return -2 immediately to propagate the failure.
    5. Calculate the absolute difference of the left and right heights.
    6. If the difference is > 1, the tree is unbalanced, so return -2.
    7. Otherwise, the current subtree is balanced. Return its height:
       `1 + max(left_height, right_height)`.
- Time complexity: O(N), as each node is visited only once.
- Space complexity: O(H) for the recursion stack.

💡 Key Pattern:
- Tree Traversal (post-order DFS)
- Recursion
- Combining multiple checks (height and balance) into a single pass

ℹ️ Keywords:
- Binary Tree, Height, Balance, Recursion, DFS, LeetCode

🗒️ Notes
- (What did I learn? Similar problems? Mistakes I made?)
- I learned how a recursive function can return a special value to
  propagate an error or condition up the call stack, avoiding
  unnecessary computations.
- The brute-force approach, while intuitive, is a classic example of
  a sub-optimal recursive solution due to repeated work.
- The optimized solution is more elegant and efficient.
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
     * @brief Calculates the height of a binary tree.
     * @param root The root node of the binary tree.
     * @return The height of the tree.
     */
    int height(TreeNode *root)
    {
        // Base case: An empty tree has a height of -1.
        if (!root)
            return -1;
        // The height is 1 plus the maximum height of its children.
        return 1 + max(height(root->left), height(root->right));
    }

    /**
     * @brief Determines if a binary tree is balanced using a brute-force
     * recursive approach (O(N^2)).
     * @param root The root node of the binary tree.
     * @return True if the tree is balanced, false otherwise.
     */
    bool isBalancedBrute(TreeNode *root)
    {
        // Base case: An empty tree is considered balanced.
        if (!root)
            return true;

        // Calculate heights of left and right subtrees. This is an
        // expensive operation as it's done for every node.
        int lh = height(root->left);
        int rh = height(root->right);

        // Check if the current node's subtrees are balanced.
        if (abs(lh - rh) > 1)
            return false;

        // Recursively check if the left and right subtrees are also
        // balanced. This leads to redundant height calculations.
        return isBalancedBrute(root->left) && isBalancedBrute(root->right);
    }

    /**
     * @brief Determines if a binary tree is balanced using an optimized
     * recursive approach (O(N)).
     * @param root The root node of the binary tree.
     * @return True if the tree is balanced, false otherwise.
     */
    bool isBalancedOptimized(TreeNode *root)
    {
        // Call the helper function and check for the sentinel value.
        return checkBalanceAndHeight(root) != -2;
    }

private:
    /**
     * @brief A single-pass recursive helper that checks for balance and
     * returns the height of the subtree.
     * @param root The current node.
     * @return The height of the subtree, or -2 if an imbalance is found.
     */
    int checkBalanceAndHeight(TreeNode *root)
    {
        // Base case: An empty subtree is balanced with a height of -1.
        if (!root)
            return -1;

        // Recursively get the height/balance status of the left subtree.
        int lh = checkBalanceAndHeight(root->left);
        // If the left subtree is already unbalanced, propagate the failure.
        if (lh == -2)
            return -2;

        // Recursively get the height/balance status of the right subtree.
        int rh = checkBalanceAndHeight(root->right);
        // If the right subtree is already unbalanced, propagate the failure.
        if (rh == -2)
            return -2;

        // Check if the current node's subtrees are balanced.
        if (abs(lh - rh) > 1)
            return -2;

        // If balanced, return the height of the current subtree.
        return 1 + max(lh, rh);
    }
};

int main()
{
    // Create a solution object.
    Solution sol;

    // Example 1: A balanced binary tree.
    // Tree: 3 -> 9, 20 -> 15, 7
    //      3
    //     / \
    //    9  20
    //       / \
    //      15  7
    TreeNode *root1 = new TreeNode(3);
    root1->left = new TreeNode(9);
    root1->right = new TreeNode(20);
    root1->right->left = new TreeNode(15);
    root1->right->right = new TreeNode(7);

    // Test the balanced tree with both approaches.
    cout << "Tree 1 (Balanced):" << endl;
    cout << "Brute-force approach: " << (sol.isBalancedBrute(root1) ? "true" : "false") << endl;
    cout << "Optimized approach: " << (sol.isBalancedOptimized(root1) ? "true" : "false") << endl;
    cout << endl;

    // Example 2: An unbalanced binary tree.
    // Tree: 1 -> 2 -> 3
    //      1
    //       \
    //        2
    //         \
    //          3
    TreeNode *root2 = new TreeNode(1);
    root2->right = new TreeNode(2);
    root2->right->right = new TreeNode(3);

    // Test the unbalanced tree with both approaches.
    cout << "Tree 2 (Unbalanced):" << endl;
    cout << "Brute-force approach: " << (sol.isBalancedBrute(root2) ? "true" : "false") << endl;
    cout << "Optimized approach: " << (sol.isBalancedOptimized(root2) ? "true" : "false") << endl;
    cout << endl;

    // Example 3: A balanced but complex tree.
    // Tree: 1 -> 2, 2 -> 3, 3 -> 4, 3 -> 5
    //        1
    //       /
    //      2
    //     / \
    //    3   3
    //   / \
    //  4   5
    TreeNode *root3 = new TreeNode(1);
    root3->left = new TreeNode(2);
    root3->left->left = new TreeNode(3);
    root3->left->right = new TreeNode(3);
    root3->left->left->left = new TreeNode(4);
    root3->left->left->right = new TreeNode(5);

    // Test the unbalanced tree with both approaches.
    cout << "Tree 3 (Balanced):" << endl;
    cout << "Brute-force approach: " << (sol.isBalancedBrute(root3) ? "true" : "false") << endl;
    cout << "Optimized approach: " << (sol.isBalancedOptimized(root3) ? "true" : "false") << endl;
    cout << endl;

    // Clean up memory to avoid leaks.
    delete root1->right->left;
    delete root1->right->right;
    delete root1->left;
    delete root1->right;
    delete root1;

    delete root2->right->right;
    delete root2->right;
    delete root2;

    delete root3->left->left->left;
    delete root3->left->left->right;
    delete root3->left->left;
    delete root3->left->right;
    delete root3->left;
    delete root3;

    return 0;
}
