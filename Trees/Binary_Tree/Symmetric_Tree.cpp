/*
File: Symmetric_Tree.cpp
Date: 2025-09-27 15:41

Problem: Symmetric Tree
Link: https://leetcode.com/problems/symmetric-tree/description/

Problem Statement:
Given the root of a binary tree, check whether it is a mirror of itself
(i.e., symmetric around its center).

-------------------------------------------------
❌ Brute Force
- Idea: The only way to verify symmetry is to check every pair of mirror
  nodes. This is inherently optimal.
- Time complexity: O(N), where N is the number of nodes.
- Space complexity: O(H) (recursion stack).
- Limitations: None, serves as the optimal approach baseline.

✅ Optimized Approachs
- Idea: Compare the root's left and right subtrees in a mirrored fashion.
- Approach: Depth-First Search (DFS) or Breadth-First Search (BFS).
- Algorithm:
    - DFS (Recursive): Create a helper $\text{isMirror(t1, t2)}$. Check values,
      then call $\text{isMirror(t1->left, t2->right)}$ AND $\text{isMirror(t1->right, t2->left)}$.
    - BFS (Iterative): Use a queue to store mirror pairs. Dequeue $\text{t1}$ and
      $\text{t2}$, compare, and then enqueue $\text{t1->left}$ with $\text{t2->right}$, and
      $\text{t1->right}$ with $\text{t2->left}$.
- Time complexity: O(N), as every node is visited exactly once.
- Space complexity: O(H) for recursion or O(W) for BFS queue (up to O(N)).

💡 Key Pattern:
- **Simultaneous Mirrored Traversal:** The traversal of one side is the
  mirror image of the other side.
- **Comparison Function:** A dedicated function to compare two nodes
  and their mirrored subtrees.

ℹ️ Keywords:
- Binary Tree, Symmetric, Mirror, DFS, BFS, Structure

🗒️ Notes
- (What did I learn? Similar problems? Mistakes I made?)
- This problem is closely related to "Identical Trees." The only difference
  is the order of recursive calls / enqueue operations.
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
     * @brief Helper function to recursively check if two nodes are mirrors.
     * @param t1 The node from the left side.
     * @param t2 The node from the right side.
     * @return True if the subtrees rooted at t1 and t2 are mirrors.
     */
    bool isMirror(TreeNode *t1, TreeNode *t2)
    {
        // Case 1: Both are null, they are symmetric at this point.
        if (!t1 && !t2)
            return true;

        // Case 2: One is null or values differ, non-symmetric.
        if (!t1 || !t2 || t1->val != t2->val)
            return false;

        // Case 3: Recursively check the outer and inner children in mirror order.
        return isMirror(t1->left, t2->right) &&
               isMirror(t1->right, t2->left);
    }

public:
    /**
     * @brief Checks if a tree is symmetric using iteration (BFS).
     * @param root The root of the binary tree.
     * @return True if the tree is symmetric, false otherwise.
     */
    bool isSymmetricItr(TreeNode *root)
    {
        if (!root)
            return true;

        // Queue to store mirror pairs of nodes to check.
        queue<TreeNode *> q;
        q.push(root->left);
        q.push(root->right);

        while (!q.empty())
        {
            TreeNode *t1 = q.front();
            q.pop();
            TreeNode *t2 = q.front();
            q.pop();

            // Case 1: Both are null, continue to the next pair.
            if (!t1 && !t2)
                continue;

            // Case 2: One is null or values differ, non-symmetric.
            if (!t1 || !t2 || t1->val != t2->val)
                return false;

            // Enqueue mirror pairs for the next level:
            // 1. Outer pair: t1's left and t2's right.
            q.push(t1->left);
            q.push(t2->right);
            // 2. Inner pair: t1's right and t2's left.
            q.push(t1->right);
            q.push(t2->left);
        }
        return true;
    }

    /**
     * @brief Checks if a tree is symmetric using recursion (DFS).
     * @param root The root of the binary tree.
     * @return True if the tree is symmetric, false otherwise.
     */
    bool isSymmetricRec(TreeNode *root)
    {
        // The tree is symmetric if the two subtrees are mirrors of each other.
        if (!root)
            return true;
        return isMirror(root->left, root->right);
    }

    // Main public function defaulting to the recursive approach.
    bool isSymmetric(TreeNode *root)
    {
        return isSymmetricRec(root);
    }
};

int main()
{
    Solution sol;

    // Test Case 1: Symmetric Tree (Expected: True)
    //        1
    //       / \
    //      2   2
    //     / \ / \
    //    3  4 4  3
    TreeNode *root1 = new TreeNode(1,
                                   new TreeNode(2, new TreeNode(3), new TreeNode(4)),
                                   new TreeNode(2, new TreeNode(4), new TreeNode(3)));

    // Test Case 2: Asymmetric Tree (Expected: False)
    //        1
    //       / \
    //      2   2
    //       \   \
    //        3   3
    TreeNode *root2 = new TreeNode(1,
                                   new TreeNode(2, nullptr, new TreeNode(3)),
                                   new TreeNode(2, nullptr, new TreeNode(3)));

    // Test Case 3: Empty Tree (Expected: True)
    TreeNode *root3 = nullptr;

    cout << "Test Case 1 (Symmetric):" << endl;
    cout << "  DFS Result: " << (sol.isSymmetric(root1) ? "True" : "False") << endl;
    cout << "  BFS Result: " << (sol.isSymmetricItr(root1) ? "True" : "False") << endl;

    cout << "\nTest Case 2 (Asymmetric):" << endl;
    cout << "  DFS Result: " << (sol.isSymmetric(root2) ? "True" : "False") << endl;
    cout << "  BFS Result: " << (sol.isSymmetricItr(root2) ? "True" : "False") << endl;

    cout << "\nTest Case 3 (Empty):" << endl;
    cout << "  DFS Result: " << (sol.isSymmetric(root3) ? "True" : "False") << endl;
    cout << "  BFS Result: " << (sol.isSymmetricItr(root3) ? "True" : "False") << endl;

    // Note: Proper memory deallocation for complex tests is omitted for brevity.

    return 0;
}
