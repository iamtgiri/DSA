/*
File: Binary_Tree_Right_Side_View.cpp
Date: 2025-09-30 00:21

Problem: Binary Tree Right Side View
Link: https://leetcode.com/problems/binary-tree-right-side-view/description/

Problem Statement:
Given the root of a binary tree, imagine yourself standing on the right side
of it. Return the values of the nodes you can see ordered from top to bottom.

-------------------------------------------------
❌ Brute Force
- Idea: Not applicable. Any correct approach requires visiting all nodes.
- Time complexity: $\text{O}(N)$
- Space complexity: $\text{O}(N)$
- Limitations: None.

✅ Optimized Approachs
- Idea: Identify the last node encountered at each level, or the first node
  encountered when prioritizing the right side of the tree.
- Approach 1: Level Order Traversal (BFS)
- Algorithm 1:
    1. Use a queue for BFS.
    2. Iterate through the nodes level by level (size of the queue).
    3. The **last** node processed in the current loop iteration (which
       corresponds to the $\text{back()}$ of the queue *before* the loop
       starts, or the last $\text{node}$ processed *inside* the loop) is the
       rightmost node.
    4. Add this node's value to the result list.
- Time complexity: $\text{O}(N)$, where $N$ is the number of nodes.
- Space complexity: $\text{O}(W)$, where $W$ is the maximum width of the tree ($\text{O}(N)$ worst case).

- Approach 2: Recursive Traversal (DFS)
- Algorithm 2:
    1. Traverse using a modified Pre-order: **Root -> Right -> Left**.
    2. Maintain the current $\text{level}$ (depth) and $\text{maxLevel}$ reached.
    3. If $\text{level}$ is greater than the current size of the result vector
       (meaning it's the first time we've hit this depth), add the node's
       value to the result.
    4. Since we prioritize the right child, the first node seen at any new
       level will be the rightmost one.
- Time complexity: $\text{O}(N)$, as every node is visited exactly once.
- Space complexity: $\text{O}(H)$, where $H$ is the height of the tree (for
  the recursion stack).

💡 Key Pattern:
- **Level Tracking & Priority:** Use level/depth tracking (either implicitly in
  BFS or explicitly in DFS) and prioritize the **right** child over the left.

ℹ️ Keywords:
- Binary Tree, Right View, BFS, DFS, Level Order, Pre-order, Depth

🗒️ Notes
- (What did I learn? Similar problems? Mistakes I made?)
- The DFS approach is the most efficient in terms of space complexity for
  balanced trees, but the BFS approach is very clear: the last element of
  every level is the answer.
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
private:
    /**
     * @brief Recursive helper function for the DFS (Right-prioritized Pre-order).
     * @param node The current node being visited.
     * @param ans Reference to the result vector.
     * @param level The current depth of the node (starting at 0 or 1).
     */
    void rightSideViewRecursive(TreeNode *node, vector<int> &ans, int level)
    {
        if (!node)
            return;

        // Condition check: If the current level is equal to the size of the
        // answer vector, it means this is the first node we encounter at
        // this new level.
        if (level == ans.size())
        {
            ans.push_back(node->val);
        }

        // Prioritize the right child to ensure the rightmost node is hit first.
        rightSideViewRecursive(node->right, ans, level + 1);
        // Then check the left child.
        rightSideViewRecursive(node->left, ans, level + 1);
    }

public:
    /**
     * @brief Finds the right side view of the binary tree using Level Order (BFS).
     * @details This method iterates level-by-level, recording the last node seen.
     * @param root The root node of the binary tree.
     * @return A vector containing the nodes in the right view.
     */
    vector<int> rightSideViewBFS(TreeNode *root)
    {
        if (!root)
            return {};

        // Using queue<TreeNode*> is standard, but list for pop_front/back is
        // also possible. Switching to standard queue for clarity.
        queue<TreeNode *> q;
        vector<int> ans;
        q.push(root);

        while (!q.empty())
        {
            int size = q.size();

            // The value of the node is retrieved when i == size - 1, meaning
            // it is the last node processed on this level (the rightmost one).
            for (int i = 0; i < size; ++i)
            {
                TreeNode *node = q.front();
                q.pop();

                // If it's the last node of the current level, add it to the result.
                if (i == size - 1)
                {
                    ans.push_back(node->val);
                }

                // Enqueue children for the next level
                if (node->left)
                    q.push(node->left);
                if (node->right)
                    q.push(node->right);
            }
        }
        return ans;
    }

    /**
     * @brief Finds the right side view of the binary tree using Recursion (DFS).
     * @details This method prioritizes the right child to see the rightmost
     * node first at every level.
     * @param root The root node of the binary tree.
     * @return A vector containing the nodes in the right view.
     */
    vector<int> rightSideViewDFS(TreeNode *root)
    {
        vector<int> ans;
        rightSideViewRecursive(root, ans, 0); // Start level at 0
        return ans;
    }

    // Public function defaulting to the DFS approach due to potentially better
    // space complexity $\text{O(H)}$ in balanced trees.
    vector<int> rightSideView(TreeNode *root)
    {
        return rightSideViewDFS(root);
    }
};

int main()
{
    Solution sol;

    // Test Tree: (Expected Right View: 1, 3, 4)
    //        1
    //       / \
    //      2   3
    //     / \   \
    //    4   5   6
    //   /
    //  7
    TreeNode *root = new TreeNode(1,
                                  new TreeNode(2, new TreeNode(4, new TreeNode(7), nullptr), new TreeNode(5)),
                                  new TreeNode(3, nullptr, new TreeNode(6)));

    // Expected Output: 1 3 6 7 (Incorrect expectation above. Let's trace it: 1, 3, 6, 7 is the path.)
    // Correction: Rightmost nodes are 1, 3, 6, 7

    // Example test cases
    vector<int> view_bfs = sol.rightSideViewBFS(root);
    cout << "Right View (BFS): ";
    for (int val : view_bfs)
    {
        cout << val << " ";
    }
    cout << " (Expected: 1 3 6 7)" << endl;

    vector<int> view_dfs = sol.rightSideViewDFS(root);
    cout << "Right View (DFS): ";
    for (int val : view_dfs)
    {
        cout << val << " ";
    }
    cout << " (Expected: 1 3 6 7)" << endl;

    // Note: Memory deallocation omitted for brevity in simple test harness.

    return 0;
}
