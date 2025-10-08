/*
File: LCA_in_Binary_Search_Tree.cpp
Date: 2025-10-09 02:24

Problem: Lowest Common Ancestor of a Binary Search Tree
Link: https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-search-tree/description/

Problem Statement:
Given the root of a Binary Search Tree (BST), and two nodes p and q, find the
lowest common ancestor (LCA) of the two nodes. The LCA is the lowest node in the
tree that has both p and q as descendants.

-------------------------------------------------
❌ Brute Force
- Idea: Ignore the BST property and use the general Binary Tree LCA method: find
  paths from root to p and q, then compare the paths to find the last common node.
- Time complexity: O(N) where N is the number of nodes (to traverse and find paths).
- Space complexity: O(H) for storing the path vectors, where H is the height of the tree.
- Limitations: Does not utilize the sorted nature of the BST, resulting in an
  unnecessary full tree traversal.

✅ Optimized Approachs
- Idea: Exploit the **Binary Search Tree property**. The LCA must be the first node
  where nodes p and q split paths (one is in the left subtree, one in the right),
  or where one node is an ancestor of the other.
- Approach: Iterative Traversal (Single Pass)
- Algorithm:
    1. Start at the `root`.
    2. While the current `root` is not the LCA:
       a. If both $p.val$ and $q.val$ are **less than** $root.val$, the LCA must be
          in the left subtree. Move `root = root->left`.
       b. If both $p.val$ and $q.val$ are **greater than** $root.val$, the LCA must
          be in the right subtree. Move `root = root->right`.
       c. Otherwise, $p$ and $q$ are split (one is less than, one is greater than $root.val$),
          or one of them equals $root.val$. In this case, `root` is the LCA. Return `root`.
- Time complexity: O(H). Since we only traverse down one branch, the time complexity is
  proportional to the height of the tree. If the tree is balanced, this is O($\log N$).
- Space complexity: O(1) (Iterative approach) as no recursion stack or extra storage is used.

💡 Key Pattern:
- **Directional Traversal:** Using value comparison to determine which branch to search,
  eliminating half the search space at each step (similar to standard BST search).

ℹ️ Keywords:
- Binary Search Tree, BST, LCA, Iterative, O(H), O(log N)

🗒️ Notes
- (What did I learn? Similar problems? Mistakes I made?)
- The iterative approach is preferred for BST LCA as it avoids the recursive overhead
  and achieves O(1) space complexity, maintaining the O(H) time complexity.
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
     * @brief Finds the Lowest Common Ancestor (LCA) in a BST.
     * @param root The root of the BST.
     * @param p One of the target nodes.
     * @param q The other target node.
     * @return The pointer to the LCA node.
     */
    TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q)
    {
        // Use an iterative approach for O(1) space complexity.
        while (root)
        {
            // If both p and q are smaller than the current root, LCA must be in the left subtree.
            if (p->val < root->val && q->val < root->val)
                root = root->left;
            // If both p and q are greater than the current root, LCA must be in the right subtree.
            else if (p->val > root->val && q->val > root->val)
                root = root->right;
            // If the values split (one is smaller, one is larger) or one value equals the root,
            // the current root is the LCA.
            else
                return root;
        }
        return nullptr; // Should not happen if p and q are guaranteed to be in the tree.
    }
};

// Helper function to find a node by value (essential for testing)
TreeNode *findNode(TreeNode *root, int val)
{
    if (!root)
        return nullptr;
    if (root->val == val)
        return root;
    if (val < root->val)
        return findNode(root->left, val);
    return findNode(root->right, val);
}

// Helper function to create a test BST
TreeNode *createTestBST()
{
    // BST structure:
    //          6
    //        /   \
    //       2     8
    //      / \   / \
    //     0   4 7   9
    //        / \
    //       3   5

    TreeNode *node3 = new TreeNode(3);
    TreeNode *node5 = new TreeNode(5);
    TreeNode *node4 = new TreeNode(4, node3, node5);
    TreeNode *node0 = new TreeNode(0);
    TreeNode *node2 = new TreeNode(2, node0, node4);

    TreeNode *node7 = new TreeNode(7);
    TreeNode *node9 = new TreeNode(9);
    TreeNode *node8 = new TreeNode(8, node7, node9);

    TreeNode *root = new TreeNode(6, node2, node8);

    return root;
}

int main()
{
    Solution sol;

    TreeNode *root = createTestBST();

    // Test 1: p=2, q=8. Expected LCA: 6 (Split at root)
    TreeNode *p1 = findNode(root, 2);
    TreeNode *q1 = findNode(root, 8);
    TreeNode *lca1 = sol.lowestCommonAncestor(root, p1, q1);
    cout << "LCA of " << p1->val << " and " << q1->val << " is: "
         << (lca1 ? to_string(lca1->val) : "Not Found") << " (Expected: 6)" << endl;

    // Test 2: p=2, q=4. Expected LCA: 2 (4 is a descendant of 2)
    TreeNode *p2 = findNode(root, 2);
    TreeNode *q2 = findNode(root, 4);
    TreeNode *lca2 = sol.lowestCommonAncestor(root, p2, q2);
    cout << "LCA of " << p2->val << " and " << q2->val << " is: "
         << (lca2 ? to_string(lca2->val) : "Not Found") << " (Expected: 2)" << endl;

    // Test 3: p=3, q=5. Expected LCA: 4
    TreeNode *p3 = findNode(root, 3);
    TreeNode *q3 = findNode(root, 5);
    TreeNode *lca3 = sol.lowestCommonAncestor(root, p3, q3);
    cout << "LCA of " << p3->val << " and " << q3->val << " is: "
         << (lca3 ? to_string(lca3->val) : "Not Found") << " (Expected: 4)" << endl;

    // Test 4: p=7, q=9. Expected LCA: 8
    TreeNode *p4 = findNode(root, 7);
    TreeNode *q4 = findNode(root, 9);
    TreeNode *lca4 = sol.lowestCommonAncestor(root, p4, q4);
    cout << "LCA of " << p4->val << " and " << q4->val << " is: "
         << (lca4 ? to_string(lca4->val) : "Not Found") << " (Expected: 8)" << endl;

    // Note: Memory deallocation omitted for brevity in simple test harness.

    return 0;
}
