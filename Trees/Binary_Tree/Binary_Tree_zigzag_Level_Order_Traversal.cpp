/*
 * File: Binary_Tree_Zigzag_Level_Order_Traversal.cpp
 * Date: 2025-09-25 19:08
 *
 * Problem: Binary Tree Zigzag Level Order Traversal
 * Link: https://leetcode.com/problems/binary-tree-zigzag-level-order-traversal/description/
 *
 * Problem Statement:
 * Given the root of a binary tree, return the zigzag level order traversal of
 * its nodes' values. (i.e., from left to right, then right to left for the
 * next level and so on).
 *
 *
 * -----------------------------------------------------------------------------------
 * ❌ Brute Force
 * - Idea: The simplest approach is a standard level-order traversal (BFS) and
 * then reverse the result for every other level. This works but involves an
 * extra step of reversing vectors, which can be inefficient.
 * - Time complexity: O(N * L) where N is the number of nodes and L is the
 * number of levels. The reversal takes O(K) where K is the number of
 * nodes at that level.
 * - Space complexity: O(W) where W is the maximum width of the tree, for the
 * queue and temporary vectors.
 * - Limitations: The reversal step adds overhead and is not the most optimal
 * solution.
 *
 *
 * -----------------------------------------------------------------------------------
 * ✅ Optimized Approach: Two-Stack Iterative Traversal
 * - Idea: Instead of a single queue, we can use two stacks to manage the
 * traversal direction. One stack handles left-to-right traversal, and the
 * other handles right-to-left.
 * - Approach: We'll use two stacks, `s1` and `s2`. We'll process nodes from
 * `s1` (left-to-right) and push their children into `s2`. Then we'll
 * process nodes from `s2` (right-to-left) and push their children into `s1`.
 * This automatically creates the zigzag pattern.
 * - Algorithm:
 * 1. Create a vector of vectors `result` and handle the edge case of a null
 * root.
 * 2. Initialize two stacks, `s1` and `s2`. Push the `root` onto `s1`.
 * 3. Loop while either `s1` or `s2` is not empty.
 * a. Process `s1` (left-to-right level):
 * i. Create a `level` vector.
 * ii. Pop nodes from `s1` until it's empty. For each node, add its value
 * to `level`.
 * iii. Critically, push the children of the current node onto `s2` in
 * the order: **left child, then right child**.
 * iv. If `level` is not empty, add it to `result`.
 * b. Process `s2` (right-to-left level):
 * i. Create a `level` vector.
 * ii. Pop nodes from `s2` until it's empty. For each node, add its value
 * to `level`.
 * iii. Critically, push the children of the current node onto `s1` in
 * the order: **right child, then left child**.
 * iv. If `level` is not empty, add it to `result`.
 * 4. Return `result`.
 * - Time complexity: O(N) where N is the number of nodes. We visit each node
 * and perform constant time operations (push, pop) on the stacks.
 * - Space complexity: O(W) where W is the maximum width of the tree. The two
 * stacks together will hold at most all nodes from the two widest levels.
 * In the worst case (a complete binary tree), this is O(N).
 *
 *
 * -----------------------------------------------------------------------------------
 * 💡 Key Pattern: Two-Stack Traversal
 * - This pattern is a clever variation of BFS that uses stacks instead of a
 * queue to reverse the order of processing for each level. It's a key
 * technique for problems requiring alternating direction traversal.
 *
 *
 * -----------------------------------------------------------------------------------
 * ℹ️ Keywords: Binary Tree, Zigzag Traversal, Level Order, Stack, Iterative, BFS
 *
 *
 * -----------------------------------------------------------------------------------
 * 🗒️ Notes
 * - (What did I learn?) The use of two stacks, with controlled push order,
 * naturally handles the zigzag pattern without the need for reversing. For
 * `s1` (L->R), we push children (L->R) to `s2`. For `s2` (R->L), we push
 * children (R->L) to `s1`. This ensures the correct order on the next level.
 * - (Similar problems?) Standard Level Order Traversal, Binary Tree Right Side
 * View, and other BFS-related tree problems.
 * - (Mistakes I made?) A common mistake is getting the push order for the
 * children wrong. For a left-to-right pass, you need to push children
 * right-to-left into the next stack so they are popped left-to-right. For a
 * right-to-left pass, you need to push children left-to-right into the next
 * stack so they are popped right-to-left. The provided code has the `if`
 * conditions correctly ordered to achieve this.
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
     * @brief Performs a zigzag level order traversal of a binary tree.
     * @param root The root of the binary tree.
     * @return A vector of vectors containing the nodes' values in zigzag order,
     * grouped by level.
     */
    vector<vector<int>> zigzagLevelOrder(TreeNode *root)
    {
        // This vector will store the final result.
        vector<vector<int>> result;
        // Handle the edge case of an empty tree.
        if (root == nullptr)
            return result;

        // s1: Processes nodes from left to right.
        // Its children will be pushed to s2.
        stack<TreeNode *> s1;

        // s2: Processes nodes from right to left.
        // Its children will be pushed to s1.
        stack<TreeNode *> s2;

        // Start the traversal by pushing the root node onto the first stack.
        s1.push(root);

        // Continue the traversal as long as at least one stack is not empty.
        while (!s1.empty() || !s2.empty())
        {
            // `level` will store the values of the nodes at the current level.
            vector<int> level;

            // Process the current level from left to right using stack s1.
            while (!s1.empty())
            {
                // Get the node at the top of the stack.
                TreeNode *curr = s1.top();
                // Remove the node from the stack.
                s1.pop();
                // Add the node's value to the current level vector.
                level.push_back(curr->val);

                // Push children for the next level (to be processed from right
                // to left), pushing the left child first.
                if (curr->left)
                    s2.push(curr->left);
                if (curr->right)
                    s2.push(curr->right);
            }
            // If the level is not empty, add it to the result.
            if (!level.empty())
                result.push_back(level);

            // Clear the level vector for the next level's processing.
            level.clear();

            // Process the current level from right to left using stack s2.
            while (!s2.empty())
            {
                // Get the node at the top of the stack.
                TreeNode *curr = s2.top();
                // Remove the node from the stack.
                s2.pop();
                // Add the node's value to the current level vector.
                level.push_back(curr->val);

                // Push children for the next level (to be processed from left
                // to right), pushing the right child first.
                if (curr->right)
                    s1.push(curr->right);
                if (curr->left)
                    s1.push(curr->left);
            }
            // If the level is not empty, add it to the result.
            if (!level.empty())
                result.push_back(level);
        }

        // Return the final zigzag traversal.
        return result;
    }
};

int main()
{
    // This is the main function for testing the solution.
    Solution sol;

    // Example 1:
    // Tree: 3 -> 9 (left) and 20 (right). 20 has 15 (left) and 7 (right).
    // Zigzag: [[3], [20, 9], [15, 7]]
    TreeNode *root1 = new TreeNode(3);
    root1->left = new TreeNode(9);
    root1->right = new TreeNode(20);
    root1->right->left = new TreeNode(15);
    root1->right->right = new TreeNode(7);

    vector<vector<int>> result1 = sol.zigzagLevelOrder(root1);
    cout << "Example 1 Zigzag Level Order Traversal:" << endl;
    for (const auto &level : result1)
    {
        cout << "[ ";
        for (int val : level)
        {
            cout << val << " ";
        }
        cout << "]" << endl;
    }
    // Expected output:
    // [ 3 ]
    // [ 20 9 ]
    // [ 15 7 ]

    // Clean up memory
    delete root1->right->left;
    delete root1->right->right;
    delete root1->left;
    delete root1->right;
    delete root1;

    // Example 2: Empty tree
    TreeNode *root2 = nullptr;
    vector<vector<int>> result2 = sol.zigzagLevelOrder(root2);
    cout << "\nExample 2 Zigzag Traversal (empty tree):" << endl;
    if (result2.empty())
    {
        cout << "[]" << endl;
    }
    // Expected output: []

    return 0;
}