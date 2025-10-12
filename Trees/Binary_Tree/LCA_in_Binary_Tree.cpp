/*
File: LCA_in_Binary_Tree.cpp
Date: 2025-10-09 00:03

Problem: Lowest Common Ancestor of a Binary Tree
Link: https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree/description/

Problem Statement:
Given the root of a binary tree, find the lowest common ancestor (LCA) of two
given nodes, p and q. The LCA is defined as the lowest node in the tree that has
both p and q as descendants (where a node can be a descendant of itself).

-------------------------------------------------
❌ Brute Force
- Idea: For every node starting from the root, check if both target nodes (p and q)
  exist in its subtree using a separate DFS/traversal (`find` function). The last
  node for which this is true is the LCA. This checks containment multiple times.
- Time complexity: O(N * N) in the worst case (skewed tree), where N is the number of nodes.
  More accurately, it's O(N^2) as each of the O(N) calls to `lca` performs O(N) work via `find`.
- Space complexity: O(H) for the recursion stack depth.
- Limitations: Highly inefficient due to redundant checks for p and q existence
  at every ancestor level.

✅ Optimized Approachs
- Idea: Use a single recursive DFS post-order traversal that returns one of
  three states: null (neither p nor q found), p (p found), or q (q found). This
  allows the LCA decision to be made bottom-up.
- Approach: Single-Pass Recursive DFS
- Algorithm:
    1. Base Case: If the current `root` is null, p, or q, return `root`.
    2. Recurse: Call `lowestCommonAncestorOpt` on left and right children.
    3. Process Results (Post-Order Logic):
       a. If both left and right calls return non-null nodes, the current `root`
          is the LCA. Return `root`.
       b. If only one call returns a non-null node, return that non-null result
          up the call stack.
       c. If both return null, return null.
- Time complexity: O(N). We visit every node exactly once.
- Space complexity: O(H) for the recursion stack depth, where H is the height of the tree.

💡 Key Pattern:
- **Bottom-Up Recursion (Post-Order):** The LCA for p and q must be determined
  after recursively processing the left and right subtrees.

ℹ️ Keywords:
- Binary Tree, LCA, Lowest Common Ancestor, DFS, Recursion, Post-Order, Divide and Conquer

🗒️ Notes
- (What did I learn? Similar problems? Mistakes I made?)
- The Brute Force approach demonstrates the conceptual definition of LCA, while
  the Optimized approach provides the efficient implementation required in interviews.
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
     */
    TreeNode() : val(0), left(nullptr), right(nullptr) {}

    /**
     * @brief Constructor with value.
     */
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}

    /**
     * @brief Full constructor.
     */
    TreeNode(int x, TreeNode *left, TreeNode *right)
        : val(x), left(left), right(right) {}
};

class Solution
{
public:
    /**
     * @brief Finds the LCA using the brute-force O(N^2) recursive approach.
     * @details This function iterates and re-checks for p and q containment
     * at every node, making it inefficient.
     */
    TreeNode *lowestCommonAncestorBruteForce(TreeNode *root, TreeNode *p, TreeNode *q)
    {
        TreeNode *anc = nullptr;
        // The helper lca function updates 'anc' to the lowest possible ancestor.
        lca(root, p, q, anc);
        return anc;
    }

    /**
     * @brief Finds the LCA using the efficient O(N) single-pass recursive approach.
     * @details This is the standard solution for LCA in a general Binary Tree.
     */
    TreeNode *lowestCommonAncestorOpt(TreeNode *root, TreeNode *p, TreeNode *q)
    {
        // 1. Base Case: If root is null, or if root is p or q, return root.
        if (!root || root == p || root == q)
            return root;

        // 2. Recurse: Find LCA in the left and right subtrees.
        TreeNode *left_lca = lowestCommonAncestorOpt(root->left, p, q);
        TreeNode *right_lca = lowestCommonAncestorOpt(root->right, p, q);

        // 3. Process Results (Post-Order Logic)

        // If both sides return non-null, the current root is the LCA.
        if (left_lca && right_lca)
            return root;

        // Otherwise, return the non-null result (or null if both were null)
        return left_lca ? left_lca : right_lca;
    }

private:
    /**
     * @brief Recursive helper for the brute-force approach.
     * @details Checks if both p and q exist in the current subtree and updates the LCA.
     */
    void lca(TreeNode *root, TreeNode *p, TreeNode *q, TreeNode *&anc)
    {
        if (!root)
            return;

        // Check: If both p and q exist in the current subtree rooted at 'root'
        if (find(root, p) && find(root, q))
        {
            // Update the ancestor to the current node (it's the lowest found so far)
            anc = root;
            // Recursively search deeper to find a potentially lower common ancestor
            lca(root->left, p, q, anc);
            lca(root->right, p, q, anc);
        }
    }

    /**
     * @brief Simple DFS to check if node p exists in the subtree rooted at 'root'.
     */
    bool find(TreeNode *root, TreeNode *p)
    {
        if (!root)
            return false;
        if (root == p)
            return true;
        return find(root->left, p) || find(root->right, p);
    }
};

// Helper function to find a node by value (useful for test setup)
TreeNode *findNode(TreeNode *root, int val)
{
    if (!root)
        return nullptr;
    if (root->val == val)
        return root;
    TreeNode *left = findNode(root->left, val);
    if (left)
        return left;
    return findNode(root->right, val);
}

// Helper function to create a test tree
TreeNode *createTestTree()
{
    // Tree structure:
    //         3
    //        / \
    //       5   1
    //      / \ / \
    //     6  2 0  8
    //       / \
    //      7   4

    TreeNode *node7 = new TreeNode(7);
    TreeNode *node4 = new TreeNode(4);
    TreeNode *node6 = new TreeNode(6);
    TreeNode *node2 = new TreeNode(2);
    node2->left = node7;
    node2->right = node4;

    TreeNode *node0 = new TreeNode(0);
    TreeNode *node8 = new TreeNode(8);

    TreeNode *node5 = new TreeNode(5);
    node5->left = node6;
    node5->right = node2;

    TreeNode *node1 = new TreeNode(1);
    node1->left = node0;
    node1->right = node8;

    TreeNode *root = new TreeNode(3);
    root->left = node5;
    root->right = node1;

    return root;
}

int main()
{
    Solution sol;

    TreeNode *root = createTestTree();

    cout << "--- Testing Lowest Common Ancestor (Optimized O(N)) ---" << endl;

    // Test 1: p=5, q=4. Expected LCA: 5 (since 5 is an ancestor of 4)
    TreeNode *node_p1 = findNode(root, 5);
    TreeNode *node_q1 = findNode(root, 4);
    if (node_p1 && node_q1)
    {
        TreeNode *lca_result = sol.lowestCommonAncestorOpt(root, node_p1, node_q1);
        cout << "LCA of " << node_p1->val << " and " << node_q1->val << " is: "
             << (lca_result ? to_string(lca_result->val) : "Not Found") << " (Expected: 5)" << endl;
    }

    // Test 2: p=5, q=1. Expected LCA: 3
    TreeNode *node_p2 = findNode(root, 5);
    TreeNode *node_q2 = findNode(root, 1);
    if (node_p2 && node_q2)
    {
        TreeNode *lca_result = sol.lowestCommonAncestorOpt(root, node_p2, node_q2);
        cout << "LCA of " << node_p2->val << " and " << node_q2->val << " is: "
             << (lca_result ? to_string(lca_result->val) : "Not Found") << " (Expected: 3)" << endl;
    }

    // Test 3: p=7, q=4. Expected LCA: 2
    TreeNode *node_p3 = findNode(root, 7);
    TreeNode *node_q3 = findNode(root, 4);
    if (node_p3 && node_q3)
    {
        TreeNode *lca_result = sol.lowestCommonAncestorOpt(root, node_p3, node_q3);
        cout << "LCA of " << node_p3->val << " and " << node_q3->val << " is: "
             << (lca_result ? to_string(lca_result->val) : "Not Found") << " (Expected: 2)" << endl;
    }

    cout << "--- Testing Lowest Common Ancestor (Brute Force O(N^2)) ---" << endl;

    // Test 4: p=7, q=4. Expected LCA: 2
    if (node_p3 && node_q3)
    {
        TreeNode *lca_result = sol.lowestCommonAncestorBruteForce(root, node_p3, node_q3);
        cout << "LCA of " << node_p3->val << " and " << node_q3->val << " is: "
             << (lca_result ? to_string(lca_result->val) : "Not Found") << " (Expected: 2)" << endl;
    }

    // Note: Memory deallocation omitted for brevity in simple test harness.

    return 0;
}
