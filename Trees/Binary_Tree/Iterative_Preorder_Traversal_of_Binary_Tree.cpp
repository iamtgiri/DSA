/*
 * File: Iterative_Preorder_Traversal_of_Binary_Tree.cpp
 * Date: 2025-09-25 19:14
 *
 * Problem: Iterative Preorder Traversal of Binary Tree
 * Link: https://leetcode.com/problems/binary-tree-preorder-traversal/
 *
 * Problem Statement:
 * Given the root of a binary tree, return the preorder traversal of its
 * nodes' values. Implement this iteratively.
 *
 *
 * -----------------------------------------------------------------------------------
 * ❌ Brute Force
 * - Idea: The problem itself is a classic traversal. A recursive solution is
 * often considered the standard "brute force" for these problems due to
 * its simplicity, but it may lead to stack overflow on very deep trees.
 * - Time complexity: N/A
 * - Space complexity: N/A
 * - Limitations: Recursive solutions can have a large call stack for deep
 * trees, which can lead to a stack overflow error.
 *
 *
 * -----------------------------------------------------------------------------------
 * ✅ Optimized Approach: Iterative Traversal with a Stack
 * - Idea: The core idea of preorder traversal is "Root -> Left -> Right." We
 * can simulate the recursion using an explicit stack. The stack will help us
 * keep track of the nodes we need to visit.
 * - Approach: We'll use a single stack. We'll start by pushing the root. Then,
 * we'll loop as long as the stack isn't empty. In each iteration, we'll pop
 * a node, process it, and then push its children onto the stack. To ensure
 * the "Left -> Right" order, we must push the right child first, then the
 * left child. This is because a stack is LIFO (Last-In, First-Out), and we
 * want the left child to be processed before the right.
 * - Algorithm:
 * 1. Create an empty vector `result` to store the traversal.
 * 2. Handle the edge case: if `root` is `nullptr`, return an empty `result`.
 * 3. Create a stack `st` and push the `root` onto it.
 * 4. While `st` is not empty:
 * a. Pop the top node, `curr`, from the stack.
 * b. Add `curr->val` to the `result` vector.
 * c. If `curr->right` exists, push it onto the stack.
 * d. If `curr->left` exists, push it onto the stack.
 * 5. Return the `result` vector.
 * - Time complexity: O(N) where N is the number of nodes in the tree. We visit
 * and process each node exactly once.
 * - Space complexity: O(H) where H is the height of the tree. This is for the
 * stack. In the worst case (a skewed tree), H can be N, so the space
 * complexity is O(N). In the best case (a balanced tree), H is log(N),
 * so the space complexity is O(logN).
 *
 *
 * -----------------------------------------------------------------------------------
 * 💡 Key Pattern: Iterative DFS using a Stack
 * - This is a fundamental pattern for converting any recursive Depth-First
 * Search (DFS) algorithm on a tree or graph into an iterative one. A stack
 * explicitly manages the nodes to be visited, mirroring the function call
 * stack of a recursive solution.
 *
 *
 * -----------------------------------------------------------------------------------
 * ℹ️ Keywords: Binary Tree, Iterative Traversal, Preorder, Stack, DFS
 *
 *
 * -----------------------------------------------------------------------------------
 * 🗒️ Notes
 * - (What did I learn?) The order of pushing children onto the stack is
 * counter-intuitive but crucial. To process Left before Right (as per
 * preorder definition), we must push Right onto the stack before Left.
 * This is because the last element pushed (Left) will be the first one
 * popped and processed.
 * - (Similar problems?) Iterative Inorder Traversal, Iterative Postorder
 * Traversal. The logic for these problems is similar, but the core stack
 * operations and visit order change slightly.
 * - (Mistakes I made?) A common mistake is to push the left child before the
 * right, which would result in a "Root -> Right -> Left" traversal.
 *
 *
 * -----------------------------------------------------------------------------------
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
     * @brief Performs an iterative preorder traversal of a binary tree.
     * @param root The root of the binary tree.
     * @return A vector containing the nodes' values in preorder.
     */
    vector<int> preorderTraversal(TreeNode *root)
    {
        // This vector will store the final result.
        vector<int> result;
        // Handle the edge case of an empty tree.
        if (root == nullptr)
            return result;

        // The stack will be used to simulate the recursion.
        stack<TreeNode *> st;
        // Start by pushing the root node.
        st.push(root);

        // Continue as long as there are nodes to process.
        while (!st.empty())
        {
            // Get the node at the top of the stack.
            TreeNode *curr = st.top();
            // Pop the node from the stack.
            st.pop();
            // Add the current node's value to the result vector.
            result.push_back(curr->val);

            // Push children onto the stack in reverse order of processing.
            // Push the right child first, so the left child is on top and
            // processed next.
            if (curr->right)
                st.push(curr->right);
            // Push the left child. It will be the next node processed.
            if (curr->left)
                st.push(curr->left);
        }
        // Return the final result.
        return result;
    }
};

int main()
{
    // This is the main function for testing the solution.
    Solution sol;

    // Example 1:
    // Tree: 1 -> 2 (left) and 3 (right). 2 has 4 (left) and 5 (right).
    // Preorder: 1 -> 2 -> 4 -> 5 -> 3
    TreeNode *root1 = new TreeNode(1);
    root1->left = new TreeNode(2);
    root1->right = new TreeNode(3);
    root1->left->left = new TreeNode(4);
    root1->left->right = new TreeNode(5);

    vector<int> result1 = sol.preorderTraversal(root1);
    cout << "Example 1 Iterative Preorder Traversal: ";
    for (int val : result1)
    {
        cout << val << " ";
    }
    cout << endl; // Expected output: 1 2 4 5 3

    // Clean up memory
    delete root1->left->left;
    delete root1->left->right;
    delete root1->left;
    delete root1->right;
    delete root1;

    // Example 2: Empty tree
    TreeNode *root2 = nullptr;
    vector<int> result2 = sol.preorderTraversal(root2);
    cout << "Example 2 Iterative Preorder Traversal (empty tree): ";
    if (result2.empty())
    {
        cout << "[]";
    }
    cout << endl; // Expected output: []

    return 0;
}