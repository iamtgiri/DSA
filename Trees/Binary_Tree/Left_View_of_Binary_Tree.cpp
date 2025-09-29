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

// Standard structure for GFG problems using 'data' field.
struct Node
{
    int data;
    Node *left;
    Node *right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
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
    void leftViewRecursive(Node *node, vector<int> &ans, int level, int &maxLevel)
    {
        if (!node)
            return;

        // Condition check: If the current level is greater than the max
        // level reached, it is the first node we encounter at this level.
        if (level > maxLevel)
        {
            ans.push_back(node->data);
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
    vector<int> leftViewBFS(Node *root)
    {
        if (!root)
            return {};

        vector<int> ans;
        queue<Node *> q;
        q.push(root);

        while (!q.empty())
        {
            int size = q.size();

            // The first node in the queue is the leftmost node of the current level.
            ans.push_back(q.front()->data);

            for (int i = 0; i < size; ++i)
            {
                Node *node = q.front();
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
    vector<int> leftViewDFS(Node *root)
    {
        if (!root)
            return {};
        vector<int> ans;
        int maxLevel = 0; // Represents the number of elements in ans / max depth recorded
        leftViewRecursive(root, ans, 1, maxLevel);
        return ans;
    }

    // Public function defaulting to the generally accepted BFS approach.
    vector<int> leftView(Node *root)
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
    Node *root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);
    root->right->right = new Node(7);
    root->left->left->left = new Node(8);

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
