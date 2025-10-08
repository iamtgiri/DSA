/*
File: Tree_Boundary_Traversal.cpp
Date: 2025-10-08 18:53

Problem: Tree Boundary Traversal
Link: https://www.geeksforgeeks.org/problems/boundary-traversal-of-binary-tree/1

Problem Statement:
Given a binary tree, print its boundary nodes in an anti-clockwise direction
starting from the root. The boundary includes the root, left boundary (excluding
leaves), all leaf nodes (left to right), and the right boundary (excluding
leaves, printed bottom-up).

-------------------------------------------------
❌ Brute Force
- Idea: Traverse the entire tree three separate times using DFS or BFS: once
  to find the left boundary, once for all leaves, and once for the right boundary.
  Manually handle duplicates (e.g., the root and leaves that overlap).
- Time complexity: O(N) since we visit every node up to three times.
- Space complexity: O(N) to store the result and O(H) for recursion/stack depth.
- Limitations: Three separate traversals are less efficient than a single,
  modularized O(N) approach.

✅ Optimized Approachs
- Idea: Decompose the problem into three distinct, non-overlapping segments,
  and perform a single pass for each, ensuring the correct order.
- Approach: Modularized O(N) Traversal (Root + Left + Leaves + Right (Reversed))
- Algorithm:
    1. **Add Root:** If the root is not a leaf, add its value first.
    2. **Left Boundary:** Traverse down the left side, prioritizing the left
       child, and only adding non-leaf nodes (top-down order).
    3. **Leaves:** Perform a standard recursive (pre-order) DFS to collect all
       leaves in left-to-right order.
    4. **Right Boundary:** Traverse down the right side, prioritizing the right
       child, collecting non-leaf nodes in a temporary list, and then adding
       them to the result in reverse (bottom-up order).
- Time complexity: O(N). Every node is visited at most a constant number of times.
- Space complexity: O(H) for the recursion stack (for leaves/right boundary)
  and O(N) for the result vector.

💡 Key Pattern:
- **Modular Traversal:** The boundary traversal is a sequential combination of
  three simpler, standard tree traversals: Left Boundary, Leaves (DFS), and
  Right Boundary (Reversed).

ℹ️ Keywords:
- Binary Tree, Boundary, Traversal, Left Boundary, Leaves, Right Boundary, DFS

🗒️ Notes
- (What did I learn? Similar problems? Mistakes I made?)
- Crucially, the non-leaf nodes forming the left and right boundaries must NOT
  include the actual leaf nodes. The leaf nodes are collected separately to
  ensure they are in strict left-to-right order.
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
     * @brief Checks if a given node is a leaf node.
     * @param node Pointer to the tree node.
     * @return true if the node is a leaf, false otherwise.
     */
    bool isLeaf(TreeNode *node)
    {
        return !node->left && !node->right;
    }

    /**
     * @brief Traverses the left boundary in top-down order (excluding leaves).
     * @details Moves down the leftmost path, prioritizing the left child.
     * @param root The root of the subtree to start boundary traversal from.
     * @param ans The vector to store the boundary values.
     */
    void addLeftBoundary(TreeNode *root, vector<int> &ans)
    {
        // Start traversal from the left child of the given root.
        TreeNode *curr = root->left;
        while (curr)
        {
            // Only add the node's value if it is NOT a leaf.
            if (!isLeaf(curr))
                ans.push_back(curr->val);

            // Prioritize going left to maintain the leftmost path.
            if (curr->left)
                curr = curr->left;
            else
                curr = curr->right; // Move right if left child is missing.
        }
    }

    /**
     * @brief Traverses the right boundary in bottom-up order (excluding leaves).
     * @details Moves down the rightmost path, prioritizing the right child,
     * stores nodes in a temporary vector, and reverses it.
     * @param root The root of the subtree to start boundary traversal from.
     * @param ans The vector to store the boundary values.
     */
    void addRightBoundary(TreeNode *root, vector<int> &ans)
    {
        // Start traversal from the right child of the given root.
        TreeNode *curr = root->right;
        vector<int> temp; // Use temp vector for bottom-up order.
        while (curr)
        {
            // Only store the node's value if it is NOT a leaf.
            if (!isLeaf(curr))
                temp.push_back(curr->val);

            // Prioritize going right to maintain the rightmost path.
            if (curr->right)
                curr = curr->right;
            else
                curr = curr->left; // Move left if right child is missing.
        }

        // Add elements in reverse order to achieve bottom-up traversal.
        reverse(temp.begin(), temp.end());
        ans.insert(ans.end(), temp.begin(), temp.end());
    }

    /**
     * @brief Traverses the tree to collect all leaf nodes in left-to-right order.
     * @details Uses a recursive DFS (pre-order).
     * @param root The root of the subtree.
     * @param ans The vector to store the leaf values.
     */
    void addLeaves(TreeNode *root, vector<int> &ans)
    {
        if (!root)
            return;

        // Base case: If the current node is a leaf, add its value and return.
        if (isLeaf(root))
        {
            ans.push_back(root->val);
            return;
        }

        // Recurse left and then right to maintain left-to-right order.
        addLeaves(root->left, ans);
        addLeaves(root->right, ans);
    }

public:
    /**
     * @brief Performs the boundary traversal of the binary tree.
     * @param root The root of the binary tree.
     * @return A vector of integers representing the boundary nodes in anti-clockwise order.
     */
    vector<int> boundaryTraversal(TreeNode *root)
    {
        vector<int> ans;
        if (!root)
            return ans;

        // 1. Add Root (if not a leaf). If root is the only node, it's a leaf,
        // and it will be covered by addLeaves.
        if (!isLeaf(root))
            ans.push_back(root->val);

        // 2. Add Left Boundary (excluding leaves).
        addLeftBoundary(root, ans);

        // 3. Add Leaves (in left-to-right order).
        addLeaves(root, ans);

        // 4. Add Right Boundary (in bottom-up order, excluding leaves).
        addRightBoundary(root, ans);

        return ans;
    }
};

// Helper function to create a test tree
TreeNode *createTestTree()
{
    // Tree structure for testing boundary traversal:
    //         1
    //        / \
    //       2   3
    //      / \   \
    //     4   5   6
    //        / \   \
    //       7   8   9
    //                / \
    //               10 11
    // Expected boundary: [1, 2, 4, 7, 8, 10, 11, 9, 6, 3] (Root, Left Non-Leaves, Leaves, Right Non-Leaves Reversed)

    TreeNode *node11 = new TreeNode(11);
    TreeNode *node10 = new TreeNode(10);
    TreeNode *node9 = new TreeNode(9, node10, node11);
    TreeNode *node8 = new TreeNode(8);
    TreeNode *node7 = new TreeNode(7);
    TreeNode *node6 = new TreeNode(6, nullptr, node9);
    TreeNode *node5 = new TreeNode(5, node7, node8);
    TreeNode *node4 = new TreeNode(4);
    TreeNode *node3 = new TreeNode(3, nullptr, node6);
    TreeNode *node2 = new TreeNode(2, node4, node5);
    TreeNode *root = new TreeNode(1, node2, node3);

    return root;
}

int main()
{
    Solution sol;

    TreeNode *root = createTestTree();

    cout << "Tree Boundary Traversal (Anti-Clockwise):" << endl;
    vector<int> boundary = sol.boundaryTraversal(root);

    cout << "Boundary Nodes: [";
    for (size_t i = 0; i < boundary.size(); ++i)
    {
        cout << boundary[i];
        if (i < boundary.size() - 1)
        {
            cout << ", ";
        }
    }
    cout << "]" << endl;

    // Expected Output: [1, 2, 4, 7, 8, 10, 11, 9, 6, 3]

    // Note: Memory deallocation omitted for brevity in simple test harness.

    return 0;
}
