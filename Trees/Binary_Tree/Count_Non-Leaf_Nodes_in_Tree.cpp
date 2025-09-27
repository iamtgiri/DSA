/*
File: Count_Non-Leaf_Nodes_in_Tree.cpp
Date: 2025-09-27 10:50

Problem: Count Non-Leaf Nodes in Tree
Link: https://www.geeksforgeeks.org/problems/count-non-leaf-nodes-in-tree/1

Problem Statement:
Given the root of a binary tree, count all nodes that are NOT leaf nodes.
A non-leaf node has at least one child (left or right).

-------------------------------------------------
❌ Brute Force
- Idea: Traverse the entire tree (DFS/BFS) and check the non-leaf condition.
  This is already the most efficient method.
- Time complexity: O(N), where N is the number of nodes.
- Space complexity: O(H) (recursion stack).
- Limitations: None, serves as the baseline.

✅ Optimized Approachs
- Idea: Count nodes that have at least one child $(\text{node.left} \ne \text{nullptr} \text{ OR } \text{node.right} \ne \text{nullptr})$.
  Alternatively: $\text{Total Size} - \text{Leaf Count}$.
- Approach: Depth-First Search (DFS) via recursion is idiomatic.
- Algorithm:
    - Recursive (DFS): Base case returns 0 for null or a leaf. If not a leaf,
      return $1 + \text{recursive calls on children}$.
    - Iterative (BFS): Use a queue; check the non-leaf condition on dequeue.
- Time complexity: O(N) for both approaches.
- Space complexity:
    - DFS: O(H) for recursion stack.
    - BFS: O(W) for queue, where W is the max width (up to O(N)).

💡 Key Pattern:
- Tree Traversal (DFS/BFS)
- Conditional counting based on node properties.

ℹ️ Keywords:
- Binary Tree, Non-Leaf Node, Internal Node, Count, Traversal

🗒️ Notes
- (What did I learn? Similar problems? Mistakes I made?)
- A non-leaf node check is the inverse of the leaf node check.
- The root node is counted as a non-leaf node if the tree size $> 1$.
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
     * @brief Counts non-leaf nodes using recursion (DFS).
     * @details A non-leaf node must have at least one child.
     * @param root The root node of the binary tree.
     * @return The total number of non-leaf nodes.
     */
    int countNonLeafNodesRec(TreeNode *root)
    {
        // Base case 1: If the node is null, it cannot be a non-leaf node.
        if (!root)
            return 0;

        // Base case 2: If the node is a leaf (no children), return 0.
        // This is a leaf if $\text{root->left}$ is null AND $\text{root->right}$ is null.
        if (!root->left && !root->right)
            return 0;

        // Recursive step: If not a leaf, count 1 for this node, and add
        // the counts from the left and right subtrees.
        return 1 + countNonLeafNodesRec(root->left) + countNonLeafNodesRec(root->right);
    }

    /**
     * @brief Counts non-leaf nodes using iteration (BFS).
     * @details Uses a queue to traverse level-by-level, checking the
     * non-leaf condition on each node.
     * @param root The root node of the binary tree.
     * @return The total number of non-leaf nodes.
     */
    int countNonLeafNodesItr(TreeNode *root)
    {
        // Handle empty tree case.
        if (!root)
        {
            return 0;
        }

        // Use a queue for BFS and initialize the non-leaf counter.
        queue<TreeNode *> q;
        q.push(root);
        int nonLeafCount = 0;

        // Process nodes until the queue is empty.
        while (!q.empty())
        {
            TreeNode *node = q.front();
            q.pop();

            // Check if the current node is a non-leaf node (has at least one child).
            if (node->left || node->right)
            {
                nonLeafCount++;
            }

            // Enqueue non-null children.
            if (node->left)
            {
                q.push(node->left);
            }
            if (node->right)
            {
                q.push(node->right);
            }
        }
        return nonLeafCount;
    }
};

int main()
{
    // Create a solution object.
    Solution sol;

    // Example 1: Tree with 4 non-leaves (1, 2, 3, 6).
    //        1 (Non-Leaf)
    //       / \
    //      2 (Non-Leaf) 3 (Non-Leaf)
    //     / \   \
    //    4(Leaf) 5(Leaf) 6 (Non-Leaf)
    //                   /
    //                  7 (Leaf)
    TreeNode *root1 = new TreeNode(1);
    root1->left = new TreeNode(2);
    root1->right = new TreeNode(3);
    root1->left->left = new TreeNode(4);
    root1->left->right = new TreeNode(5);
    root1->right->right = new TreeNode(6);
    root1->right->right->left = new TreeNode(7);

    cout << "Example 1 (4 Non-Leaves):" << endl;
    cout << "Recursive Count: " << sol.countNonLeafNodesRec(root1) << endl;
    cout << "Iterative Count: " << sol.countNonLeafNodesItr(root1) << endl;
    cout << endl;

    // Example 2: Skewed Tree with 2 non-leaves (10, 20)
    //        10 (Non-Leaf)
    //          \
    //           20 (Non-Leaf)
    //             \
    //              30 (Leaf)
    TreeNode *root2 = new TreeNode(10);
    root2->right = new TreeNode(20);
    root2->right->right = new TreeNode(30);

    cout << "Example 2 (2 Non-Leaves):" << endl;
    cout << "Recursive Count: " << sol.countNonLeafNodesRec(root2) << endl;
    cout << "Iterative Count: " << sol.countNonLeafNodesItr(root2) << endl;
    cout << endl;

    // Example 3: Single node tree (0 non-leaves).
    TreeNode *root3 = new TreeNode(5);
    cout << "Example 3 (0 Non-Leaves):" << endl;
    cout << "Recursive Count: " << sol.countNonLeafNodesRec(root3) << endl;
    cout << "Iterative Count: " << sol.countNonLeafNodesItr(root3) << endl;
    cout << endl;

    // Clean up memory.
    delete root1->left->left;
    delete root1->left->right;
    delete root1->right->right->left;
    delete root1->right->right;
    delete root1->left;
    delete root1->right;
    delete root1;

    delete root2->right->right;
    delete root2->right;
    delete root2;

    delete root3;

    return 0;
}
