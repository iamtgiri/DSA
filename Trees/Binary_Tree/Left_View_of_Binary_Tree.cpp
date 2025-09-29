/*
File: Left_View_of_Binary_Tree.cpp
Date: 2025-09-30 00:13

Problem: Left View of Binary Tree
Link: https://www.geeksforgeeks.org/problems/left-view-of-binary-tree/1

Problem Statement:
Given a Binary Tree, return the Left View of it. The Left View of a Binary Tree
is a set of nodes visible when the tree is viewed from the left side.

-------------------------------------------------
❌ Brute Force
- Idea: Not applicable. Any correct approach requires visiting all nodes.
- Time complexity: $\text{O}(N)$
- Space complexity: $\text{O}(N)$
- Limitations: None.

✅ Optimized Approachs
- Idea: Identify the first node encountered at each level from the left.
- Approach 1: Level Order Traversal (BFS)
- Algorithm 1:
    1. Use a queue for BFS.
    2. Iterate through the nodes level by level.
    3. For each level, the first node dequeued is the leftmost node.
    4. Add this node's value to the result list.
- Time complexity: $\text{O}(N)$, where $N$ is the number of nodes.
- Space complexity: $\text{O}(W)$, where $W$ is the maximum width of the tree.
  (Worst case $W \approx N/2$, so $\text{O}(N)$).

- Approach 2: Recursive Traversal (DFS)
- Algorithm 2:
    1. Traverse using Pre-order (Root -> Left -> Right).
    2. Maintain the current $\text{level}$ (depth) and the $\text{maxLevel}$ reached
       so far (the size of the result vector).
    3. If $\text{level} > \text{maxLevel}$, it means we are seeing a node at a
       new depth for the first time. Since we visit the left child first,
       this node must be the leftmost node of this level.
    4. Add it to the result and update $\text{maxLevel}$.
- Time complexity: $\text{O}(N)$, as every node is visited exactly once.
- Space complexity: $\text{O}(H)$, where $H$ is the height of the tree (for
  the recursion stack).

💡 Key Pattern:
- **Level Tracking:** Solving "view" problems often requires tracking the
  current depth to ensure only one node per level is recorded.

ℹ️ Keywords:
- Binary Tree, Left View, BFS, DFS, Level Order, Pre-order, Depth

🗒️ Notes
- (What did I learn? Similar problems? Mistakes I made?)
- The DFS approach is typically preferred for its better space complexity
  in balanced trees ($\text{O}(\log N)$ vs $\text{O}(N)$ for BFS).
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
     * @brief Recursive helper function for the DFS (Pre-order) approach.
     * @param node The current node being visited.
     * @param ans Reference to the result vector.
     * @param level The depth of the current node (starting at 1).
     * @param maxLevel Reference to the maximum level recorded in 'ans'.
     */
    void leftViewRecursive(TreeNode *node, vector<int> &ans, int level, int &maxLevel)
    {
        if (!node)
            return;

        // Condition check: If the current level is greater than the max
        // level reached, it is the first node we encounter at this level.
        if (level > maxLevel)
        {
            ans.push_back(node->val);
            maxLevel = level;
        }

        // Prioritize the left child to ensure we always hit the leftmost
        // node first at any given level.
        leftViewRecursive(node->left, ans, level + 1, maxLevel);
        leftViewRecursive(node->right, ans, level + 1, maxLevel);
    }

public:
    /**
     * @brief Finds the left view of the binary tree using Level Order (BFS).
     * @param root The root node of the binary tree.
     * @return A vector containing the nodes in the left view.
     */
    vector<int> leftViewBFS(TreeNode *root)
    {
        if (!root)
            return {};

        vector<int> ans;
        queue<TreeNode *> q;
        q.push(root);

        while (!q.empty())
        {
            int size = q.size();

            // The first node in the queue is the leftmost node of the current level.
            ans.push_back(q.front()->val);

            for (int i = 0; i < size; ++i)
            {
                TreeNode *node = q.front();
                q.pop();

                // Process children for the next level
                if (node->left)
                    q.push(node->left);
                if (node->right)
                    q.push(node->right);
            }
        }
        return ans;
    }

    /**
     * @brief Finds the left view of the binary tree using Recursion (DFS).
     * @param root The root node of the binary tree.
     * @return A vector containing the nodes in the left view.
     */
    vector<int> leftViewDFS(TreeNode *root)
    {
        if (!root)
            return {};
        vector<int> ans;
        int maxLevel = 0; // Represents the number of elements in ans / max depth recorded
        leftViewRecursive(root, ans, 1, maxLevel);
        return ans;
    }

    // Public function defaulting to the generally accepted BFS approach.
    vector<int> leftView(TreeNode *root)
    {
        return leftViewBFS(root);
    }
};

int main()
{
    Solution sol;

    // Test Tree: (Expected Left View: 1, 2, 4, 8)
    //        1
    //       / \
    //      2   3
    //     / \   \
    //    4   5   7
    //   /
    //  8
    TreeNode *root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    root->right->right = new TreeNode(7);
    root->left->left->left = new TreeNode(8);

    // Example test cases
    vector<int> view_bfs = sol.leftViewBFS(root);
    cout << "Left View (BFS): ";
    for (int val : view_bfs)
    {
        cout << val << " ";
    }
    cout << " (Expected: 1 2 4 8)" << endl;

    vector<int> view_dfs = sol.leftViewDFS(root);
    cout << "Left View (DFS): ";
    for (int val : view_dfs)
    {
        cout << val << " ";
    }
    cout << " (Expected: 1 2 4 8)" << endl;

    // Note: Memory deallocation omitted for brevity in simple test harness.

    return 0;
}
