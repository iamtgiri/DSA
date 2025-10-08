/*
File: Bottom_View_of_Binary_Tree.cpp
Date: 2025-10-02 21:01

Problem: Bottom View of Binary Tree
Link: https://www.geeksforgeeks.org/problems/bottom-view-of-binary-tree/1

Problem Statement:
Given a binary tree, print the bottom view of the tree. The bottom view is
the set of nodes visible when the tree is viewed from the bottom. If two nodes
lie in the same vertical line, the node that is at the lowest level (maximum depth)
should be included in the view.

-------------------------------------------------
❌ Brute Force
- Idea: Perform DFS to calculate the (Horizontal Distance, Level) for every node.
  Store all nodes in a map where the key is HD. For each HD, iterate through all
  associated nodes and select the one with the maximum Level (depth).
- Time complexity: O(N log N) - N for traversal, log N for map lookups/sorting.
- Space complexity: O(N) to store all node coordinates and values.
- Limitations: Inefficient, requires explicit max-depth tracking and grouping
  of all nodes, which is complex compared to the BFS approach.

✅ Optimized Approachs
- Idea: Use **Level Order Traversal (BFS)** to ensure nodes are processed from
  top to bottom. The last node processed for any given Horizontal Distance (HD)
  will be the bottom-most node.
- Approach: BFS with a Horizontal Distance Map
- Algorithm:
    1. Define storage: map<HD, Value> records. The map automatically sorts by HD.
    2. Use a queue for BFS storing {Node*, HD}.
    3. Traverse the tree using BFS. For every node, **always update** the map:
       records[HD] = node->data.
    4. Since BFS guarantees we visit deeper nodes later, the map entry for a
       specific HD will always be overwritten by the bottom-most node at that HD.
    5. Extract the values from the map into the final result vector.
- Time complexity: O(N log K), where N is the number of nodes and K is the
  maximum width of the tree (due to map insertion/lookup).
- Space complexity: O(N) for the queue and the map.

💡 Key Pattern:
- **Level Order Priority:** Use BFS to process nodes by depth. This naturally
  ensures that the last node seen at a vertical column is the correct "bottom" node.

ℹ️ Keywords:
- Binary Tree, Bottom View, BFS, Horizontal Distance, Map, Overwriting

🗒️ Notes
- (What did I learn? Similar problems? Mistakes I made?)
- This problem is an easier variation of Vertical Order Traversal because we
  only need to care about the deepest node, not the level-by-level ordering.
  The map's overwrite behavior is the key optimization.
-------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

/**
 * @class Node
 * @brief Represents a single node in a binary tree (using 'data' field).
 */
class Node
{
public:
    int data;
    Node *left;
    Node *right;

    /**
     * @brief Constructor with value.
     * @param val The integer value to be stored in the node.
     */
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

class Solution
{
public:
    /**
     * @brief Finds the bottom view of a binary tree using BFS.
     * @param root The root of the binary tree.
     * @return A vector of integers representing the bottom view, sorted by HD.
     */
    vector<int> bottomView(Node *root)
    {
        if (!root)
            return {};

        // map<Horizontal Distance, Node Value>
        // The map automatically sorts by HD (column).
        // BFS ensures the value stored is the bottom-most one due to overwriting.
        map<int, int> records;

        // Queue for BFS: {Node*, Horizontal Distance}
        queue<pair<Node *, int>> q;
        q.push({root, 0}); // Start root at HD=0

        while (!q.empty())
        {
            // The structured binding syntax auto [node, x] = q.front() is excellent.
            auto [node, x] = q.front();
            q.pop();

            // This is the core logic: The map is always updated.
            // Since this is BFS, a later update for the same 'x' means we found a deeper node.
            records[x] = node->data;

            if (node->left)
                q.push({node->left, x - 1});
            if (node->right)
                q.push({node->right, x + 1});
        }

        // Final collection: Extract values in sorted HD order (thanks to the map).
        vector<int> ans;
        for (const auto &[x, val] : records)
        {
            ans.push_back(val);
        }

        return ans;
    }
};

// Helper function to build a tree for testing
Node *buildTree(vector<int> nodes, int index)
{
    if (index >= nodes.size() || nodes[index] == -1)
    {
        return nullptr;
    }
    Node *root = new Node(nodes[index]);
    root->left = buildTree(nodes, 2 * index + 1);
    root->right = buildTree(nodes, 2 * index + 2);
    return root;
}

int main()
{
    Solution sol;

    // Example 1: Standard bottom view
    //        20 (0)
    //       /  \
    //      8 (-1) 22 (1)
    //     / \   / \
    //    5(-2) 3(0) 4(2) 25(3)
    //         / \
    //       10(-1) 14(1)
    //
    // HD: -2: 5 | -1: 10 | 0: 3 | 1: 14 | 2: 4 | 3: 25
    // Expected Output: [5, 10, 3, 14, 4, 25]
    vector<int> nodes1 = {20, 8, 22, 5, 3, 4, 25, -1, -1, 10, 14, -1, -1, -1, -1};
    Node *root1 = buildTree(nodes1, 0);

    cout << "Bottom View 1 (Expected [5, 10, 3, 14, 4, 25]): " << endl;
    vector<int> result1 = sol.bottomView(root1);
    for (int val : result1)
    {
        cout << val << " ";
    }
    cout << endl;

    // Example 2: Simple overlap
    //        1 (0)
    //       / \
    //      2 (-1) 3 (1)
    //       \ /
    //        4 (0)
    //
    // HD: -1: 2 | 0: 4 (overwrites 1) | 1: 3
    // Expected Output: [2, 4, 3]
    Node *root2 = new Node(1);
    root2->left = new Node(2);
    root2->right = new Node(3);
    root2->left->right = new Node(4);
    root2->right->left = root2->left->right; // Node 4 is both right of 2 and left of 3

    cout << "Bottom View 2 (Expected [2, 4, 3]): " << endl;
    vector<int> result2 = sol.bottomView(root2);
    for (int val : result2)
    {
        cout << val << " ";
    }
    cout << endl;

    // Note: Memory deallocation omitted for brevity in simple test harness.

    return 0;
}
