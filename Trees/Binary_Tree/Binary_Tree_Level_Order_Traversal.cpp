/*
 * File: Binary_Tree_Level_Order_Traversal.cpp
 * Date: 2025-09-25 18:52
 *
 * Problem: Binary Tree Level Order Traversal
 * Link: https://leetcode.com/problems/binary-tree-level-order-traversal/description/
 *
 * Problem Statement:
 * Given the root of a binary tree, return the level order traversal of its
 * nodes' values. (i.e., from left to right, level by level).
 *
 *
 * -----------------------------------------------------------------------------------
 * ❌ Brute Force
 * - Idea: The problem itself is a classic traversal. A recursive approach can be
 * devised, but it's more complex as you need to pass the level depth and
 * manage a list of lists. The iterative approach is the most natural for
 * level order traversal.
 * - Time complexity: N/A
 * - Space complexity: N/A
 * - Limitations: N/A
 *
 *
 * -----------------------------------------------------------------------------------
 * ✅ Optimized Approach: Breadth-First Search (BFS)
 * - Idea: Level order traversal, by definition, requires visiting all nodes at
 * a given depth before moving to the next depth. This is a perfect use case
 * for a Breadth-First Search (BFS) algorithm, which uses a queue to
 * explore nodes level by level.
 * - Approach: We'll use a queue to store the nodes to be visited. We'll process
 * one level at a time, adding all nodes from the current level to a temporary
 * list and then adding their children to the queue for the next level.
 * - Algorithm:
 * 1. Check for the edge case: If the `root` is `nullptr`, return an empty
 * vector of vectors.
 * 2. Create a queue `q` and push the `root` node into it.
 * 3. Create a vector of vectors `result` to store the final output.
 * 4. While the queue is not empty:
 * a. Get the current `size` of the queue. This size represents the number
 * of nodes at the current level.
 * b. Create a temporary vector `level` to store the values of the
 * current level's nodes.
 * c. Loop `size` times:
 * i. Dequeue the front node, let's call it `curr`.
 * ii. Add `curr->val` to the `level` vector.
 * iii. If `curr->left` is not `nullptr`, enqueue it.
 * iv. If `curr->right` is not `nullptr`, enqueue it.
 * d. After the loop, push the `level` vector into the `result` vector.
 * 5. Return the `result` vector.
 * - Time complexity: O(N) where N is the number of nodes in the tree. We visit
 * and process each node exactly once.
 * - Space complexity: O(W) where W is the maximum width of the tree. This is
 * the maximum number of nodes that can be in the queue at any given time.
 * In the worst case (a complete binary tree), W can be up to N/2,
 * so the space complexity is O(N).
 *
 *
 * -----------------------------------------------------------------------------------
 * 💡 Key Pattern: Breadth-First Search (BFS)
 * - When a problem involves processing a tree or graph level by level, a queue-
 * based BFS approach is the most suitable pattern. It guarantees that all
 * nodes at a specific depth are explored before moving to the next depth.
 *
 *
 * -----------------------------------------------------------------------------------
 * ℹ️ Keywords: Binary Tree, Level Order Traversal, BFS, Queue, Iterative
 *
 *
 * -----------------------------------------------------------------------------------
 * 🗒️ Notes
 * - (What did I learn?) The use of `q.size()` at the beginning of the `while`
 * loop is a critical trick to process nodes level by level. It ensures that
 * we only handle the nodes that were present in the queue at the start of
 * the current level's processing. Without this, the loop would process
 * nodes from multiple levels at once.
 * - (Similar problems?) Binary Tree Zigzag Level Order Traversal, Binary Tree
 * Right Side View. These are variations of BFS where the output format
 * or logic within each level changes.
 * - (Mistakes I made?) A common mistake is not using the `size` variable and
 * just looping while the queue is not empty. This would correctly traverse
 * the tree but would not separate the nodes into distinct levels.
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
     * @brief Performs a level order traversal of a binary tree.
     * @param root The root of the binary tree.
     * @return A vector of vectors containing the nodes' values, grouped
     * by level.
     */
    vector<vector<int>> levelOrder(TreeNode *root)
    {
        // Handle the edge case of an empty tree.
        if (root == nullptr)
        {
            return {};
        }

        // `result` will store the final output, with each inner vector
        // representing a level.
        vector<vector<int>> result;
        // `q` is the queue used for BFS to process nodes level by level.
        queue<TreeNode *> q;
        // Start the traversal by pushing the root node.
        q.push(root);

        // Continue the traversal as long as there are nodes in the queue.
        while (!q.empty())
        {
            // Get the number of nodes at the current level. This is crucial
            // for processing one level at a time.
            int size = q.size();
            // `level` will store the values of the nodes at the current level.
            vector<int> level;

            // Process all nodes at the current level.
            for (int i = 0; i < size; i++)
            {
                // Get the node at the front of the queue.
                TreeNode *curr = q.front();
                // Remove the node from the queue.
                q.pop();

                // Add the current node's value to the `level` vector.
                level.push_back(curr->val);

                // If the current node has a left child, add it to the queue
                // for the next level.
                if (curr->left)
                {
                    q.push(curr->left);
                }
                // If the current node has a right child, add it to the queue
                // for the next level.
                if (curr->right)
                {
                    q.push(curr->right);
                }
            }

            // After processing all nodes at the current level, add the `level`
            // vector to the final `result`.
            result.push_back(level);
        }

        // Return the complete level order traversal.
        return result;
    }
};

int main()
{
    // This is the main function for testing the solution.
    Solution sol;

    // Example 1:
    // Tree: 3 -> 9 (left) and 20 (right). 20 has 15 (left) and 7 (right).
    // Level Order: [[3], [9, 20], [15, 7]]
    TreeNode *root1 = new TreeNode(3);
    root1->left = new TreeNode(9);
    root1->right = new TreeNode(20);
    root1->right->left = new TreeNode(15);
    root1->right->right = new TreeNode(7);

    vector<vector<int>> result1 = sol.levelOrder(root1);
    cout << "Example 1 Level Order Traversal:" << endl;
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
    // [ 9 20 ]
    // [ 15 7 ]

    // Clean up memory
    delete root1->right->left;
    delete root1->right->right;
    delete root1->left;
    delete root1->right;
    delete root1;

    // Example 2: Empty tree
    TreeNode *root2 = nullptr;
    vector<vector<int>> result2 = sol.levelOrder(root2);
    cout << "\nExample 2 Level Order Traversal (empty tree):" << endl;
    if (result2.empty())
    {
        cout << "[]" << endl;
    }
    // Expected output: []

    return 0;
}