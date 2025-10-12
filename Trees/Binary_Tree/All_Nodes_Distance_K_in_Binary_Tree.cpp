/*
File: All_Nodes_Distance_K_in_Binary_Tree.cpp
Date: 2025-10-12 23:07

Problem: All Nodes Distance K in Binary Tree
Link: https://leetcode.com/problems/all-nodes-distance-k-in-binary-tree/description/

Problem Statement:
Given the root of a binary tree, a target node in the tree, and an integer k,
return an array of the values of all nodes that have a distance k from the target node.
The distance between two nodes is the length of the shortest path between them.

-------------------------------------------------
❌ Brute Force
- Idea: For every node in the tree, calculate its distance to the target node using
  a complex two-part traversal (one part to find the target's path up to the root,
  and another part to find the distance down from the common ancestor).
- Time complexity: O(N^2). Finding the distance between N nodes and the target in a
  naive way can take O(N) each.
- Space complexity: O(H).
- Limitations: Extremely complex logic for tracking distances in both upward and
  downward directions without a graph structure.

✅ Optimized Approachs
- Idea: Since distance must be measured in all directions (up to parent, down to children),
  the tree must be modeled as an **undirected graph**. Once the graph is built,
  a simple Breadth-First Search (BFS) starting from the target node easily finds all
  nodes at exactly distance k.
- Approach: Graph Conversion + Breadth-First Search (BFS).
- Algorithm:
    1. **Graph Conversion (buildGraph):** Traverse the tree (using BFS or DFS) to build
       an adjacency list (`unordered_map`) representing the undirected connections
       between all nodes (parent <-> child).
    2. **BFS from Target (distanceK):** a. Initialize a queue with `{target_node_value, 0}` (distance).
       b. Use a `visited` set to avoid revisiting nodes and infinite loops.
       c. Perform BFS, incrementing the distance with each level.
       d. When `distance == k`, add the node to the result list.
       e. Stop the traversal when `distance > k`.
- Time complexity: O(N). O(N) to build the graph and O(N) for the BFS, summing to O(N).
- Space complexity: O(N). To store the graph (adjacency list) and the visited set.

💡 Key Pattern:
- **Tree-to-Graph Transformation:** Use this pattern whenever a problem requires
  traversing the tree in a direction not permitted by the native data structure
  (e.g., needing parent pointers or unrestricted movement).
- **BFS for Shortest Distance:** BFS is the ideal algorithm for finding nodes at an
  exact distance $K$ in an unweighted graph.

ℹ️ Keywords:
- BFS, Graph Traversal, Adjacency List, Undirected Graph, Distance, Shortest Path

🗒️ Notes
- The target node itself might be part of the general tree structure, which is
  represented by its value in the graph. The BFS automatically handles paths
  that go up from the target and then down into other subtrees.
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
     * @brief Finds all nodes at distance k from the target node.
     * @param root The root of the binary tree.
     * @param target The starting node.
     * @param k The required distance.
     * @return A vector of node values at distance k.
     */
    vector<int> distanceK(TreeNode *root, TreeNode *target, int k)
    {
        if (!root)
            return {};

        // 1. Build the undirected graph
        unordered_map<int, vector<int>> graph;
        buildGraph(root, graph);

        // 2. Perform BFS from the target node
        unordered_set<int> visited;
        queue<pair<int, int>> q; // {node_value, distance}

        q.push({target->val, 0});
        visited.insert(target->val);

        vector<int> result;

        while (!q.empty())
        {
            auto [node, dist] = q.front();
            q.pop();

            if (dist == k)
                result.push_back(node);

            // Optimization: Stop the search once we exceed k distance
            if (dist >= k)
                continue;

            // Explore neighbors
            for (int nei : graph[node])
            {
                if (!visited.count(nei))
                {
                    visited.insert(nei);
                    q.push({nei, dist + 1});
                }
            }
        }

        return result;
    }

private:
    /**
     * @brief Converts the binary tree into an undirected graph (adjacency list).
     * @param root Current node in the tree.
     * @param g The adjacency list to populate.
     */
    void buildGraph(TreeNode *root, unordered_map<int, vector<int>> &g)
    {
        queue<TreeNode *> q;
        q.push(root);

        while (!q.empty())
        {
            TreeNode *node = q.front();
            q.pop();

            // Link parent <-> left child
            if (node->left)
            {
                g[node->val].push_back(node->left->val);
                g[node->left->val].push_back(node->val);
                q.push(node->left);
            }

            // Link parent <-> right child
            if (node->right)
            {
                g[node->val].push_back(node->right->val);
                g[node->right->val].push_back(node->val);
                q.push(node->right);
            }
        }
    }
};

// --- Test Helper Functions ---

// Helper function to find a node by its value for testing
TreeNode *findNode(TreeNode *root, int val)
{
    if (!root)
        return nullptr;
    if (root->val == val)
        return root;

    TreeNode *found = findNode(root->left, val);
    if (found)
        return found;

    return findNode(root->right, val);
}

// Helper function to create the test tree
TreeNode *createTestTree()
{
    // Tree Structure (Example from LeetCode 863):
    //        3
    //       / \
    //      5   1
    //     / \ / \
    //    6  2 0  8
    //      / \
    //     7   4

    TreeNode *n7 = new TreeNode(7);
    TreeNode *n4 = new TreeNode(4);
    TreeNode *n6 = new TreeNode(6);
    TreeNode *n0 = new TreeNode(0);
    TreeNode *n8 = new TreeNode(8);

    TreeNode *n2 = new TreeNode(2, n7, n4);
    TreeNode *n5 = new TreeNode(5, n6, n2);
    TreeNode *n1 = new TreeNode(1, n0, n8);

    TreeNode *root = new TreeNode(3, n5, n1);

    return root;
}

int main()
{
    Solution sol;
    TreeNode *root = createTestTree();

    cout << "--- All Nodes Distance K in Binary Tree Test Cases ---" << endl;

    // Target Node: 5, K = 2
    // Expected Nodes: 7 (down), 4 (down), 1 (up then down)
    TreeNode *target1 = findNode(root, 5);
    int k1 = 2;
    vector<int> res1 = sol.distanceK(root, target1, k1);
    sort(res1.begin(), res1.end());
    cout << "Target: 5, K=" << k1 << " | Result: ";
    for (int val : res1)
        cout << val << " ";
    cout << " (Expected: 1 4 7)" << endl;

    // Target Node: 5, K = 3
    // Expected Nodes: 0 (up-down-down), 8 (up-down-down)
    TreeNode *target2 = findNode(root, 5);
    int k2 = 3;
    vector<int> res2 = sol.distanceK(root, target2, k2);
    sort(res2.begin(), res2.end());
    cout << "Target: 5, K=" << k2 << " | Result: ";
    for (int val : res2)
        cout << val << " ";
    cout << " (Expected: 0 8)" << endl;

    // Target Node: 1, K = 3
    // Expected Nodes: 6, 7, 4 (up-down-down)
    TreeNode *target3 = findNode(root, 1);
    int k3 = 3;
    vector<int> res3 = sol.distanceK(root, target3, k3);
    sort(res3.begin(), res3.end());
    cout << "Target: 1, K=" << k3 << " | Result: ";
    for (int val : res3)
        cout << val << " ";
    cout << " (Expected: 4 6 7)" << endl;

    // Target Node: 3, K = 1
    // Expected Nodes: 5, 1
    TreeNode *target4 = findNode(root, 3);
    int k4 = 1;
    vector<int> res4 = sol.distanceK(root, target4, k4);
    sort(res4.begin(), res4.end());
    cout << "Target: 3, K=" << k4 << " | Result: ";
    for (int val : res4)
        cout << val << " ";
    cout << " (Expected: 1 5)" << endl;

    // Note: Memory deallocation omitted for brevity in simple test harness.

    return 0;
}
