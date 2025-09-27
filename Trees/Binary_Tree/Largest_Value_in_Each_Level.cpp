/*
File: Largest_Value_in_Each_Level.cpp
Date: 2025-09-27 11:06

Problem: Largest Value in Each Tree Row
Link: https://leetcode.com/problems/find-largest-value-in-each-tree-row/description/

Problem Statement:
Given the root of a binary tree, return an array of the largest value in
each level (or row) of the tree.

-------------------------------------------------
❌ Brute Force
- Idea: The most straightforward approach is Level Order Traversal (BFS),
  which is already optimal since every node must be checked once.
- Time complexity: O(N), where N is the number of nodes.
- Space complexity: O(W), where W is the maximum width (up to O(N)).
- Limitations: None.

✅ Optimized Approachs
- Idea: Use BFS to group nodes by level, and track the maximum value
  within each group before moving to the next level.
- Approach: Level Order Traversal (BFS).
- Algorithm:
    - Use a queue for standard BFS.
    - Inside the main loop, fix the current level's size (number of nodes).
    - Iterate through the fixed size, finding the max value and enqueuing
      the next level's children.
    - Store the max value for that level in the result vector.
- Time complexity: O(N), as every node is processed and inserted/removed once.
- Space complexity: O(W), where W is the maximum number of nodes in a level.

💡 Key Pattern:
- Level Order Traversal (BFS) using queue size to delimit levels.
- Max/Min value tracking within a fixed loop.

ℹ️ Keywords:
- Binary Tree, BFS, Level Order Traversal, Maximum, Level, Row

🗒️ Notes
- (What did I learn? Similar problems? Mistakes I made?)
- Use INT_MIN to correctly initialize maxVal, handling negative node values.
- Must capture the queue size before the inner loop begins.
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
     * @brief Finds the largest value in each level of the binary tree.
     * @details Uses Level Order Traversal (BFS) to process one level at a time.
     * @param root The root node of the binary tree.
     * @return A vector of integers where each element is the max value of a level.
     */
    vector<int> largestValues(TreeNode *root)
    {
        // If the tree is empty, return an empty result vector.
        if (!root)
            return {};

        // Queue for Level Order Traversal (BFS).
        queue<TreeNode *> q;
        q.push(root);
        // Vector to store the maximum value found in each level.
        vector<int> ans;

        // Process levels until the queue is empty.
        while (!q.empty())
        {
            // Capture the number of nodes in the current level.
            int size = q.size();
            // Initialize max value for the current level to the smallest possible integer.
            int maxVal = INT_MIN;

            // Traverse all nodes in the current level.
            for (int i = 0; i < size; ++i)
            {
                // Get the front node and remove it from the queue.
                TreeNode *node = q.front();
                q.pop();

                // Update the maximum value for this level.
                // We don't need the 'if (node)' check here because we only push
                // non-null children into the queue, but it's safe to keep it.
                maxVal = max(maxVal, node->val);

                // Enqueue the left child if it exists.
                if (node->left)
                    q.push(node->left);
                // Enqueue the right child if it exists.
                if (node->right)
                    q.push(node->right);
            }
            // After processing the entire level, store its maximum value.
            ans.push_back(maxVal);
        }
        return ans;
    }
};

int main()
{
    // Create a solution object.
    Solution sol;

    // Example 1: Max values should be [1, 3, 9]
    //        1
    //       / \
    //      3   2
    //     / \   \
    //    5   3   9
    TreeNode *root1 = new TreeNode(1);
    root1->left = new TreeNode(3);
    root1->right = new TreeNode(2);
    root1->left->left = new TreeNode(5);
    root1->left->right = new TreeNode(7);  // Max of level 2 is 7
    root1->right->right = new TreeNode(9); // Max of level 3 is 9

    vector<int> result1 = sol.largestValues(root1);

    cout << "Example 1 (Expected: 1, 3, 9):" << endl;
    cout << "Result: ";
    for (int val : result1)
    {
        cout << val << " ";
    }
    cout << endl;

    // Example 2: Negative values. Max values should be [-1, -3]
    //        -1
    //       / \
    //     -3  -5
    TreeNode *root2 = new TreeNode(-1);
    root2->left = new TreeNode(-3);
    root2->right = new TreeNode(-5);

    vector<int> result2 = sol.largestValues(root2);

    cout << "Example 2 (Expected: -1, -3):" << endl;
    cout << "Result: ";
    for (int val : result2)
    {
        cout << val << " ";
    }
    cout << endl;

    // Clean up memory.
    delete root1->left->left;
    delete root1->left->right;
    delete root1->right->right;
    delete root1->left;
    delete root1->right;
    delete root1;

    delete root2->left;
    delete root2->right;
    delete root2;

    return 0;
}
