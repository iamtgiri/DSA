/*
File: Construct_a_BST_from_a_preorder_traversal.cpp
Date: 2025-10-09 10:55

Problem: Construct Binary Search Tree from Preorder Traversal
Link: https://leetcode.com/problems/construct-binary-search-tree-from-preorder-traversal/description/

Problem Statement:
Given an array of integers `preorder` which represents the preorder traversal of a
Binary Search Tree (BST), construct and return the BST.

-------------------------------------------------
❌ Brute Force
- Idea: First, sort the given `preorder` array to obtain the `inorder` traversal
  (since Inorder traversal of a BST is sorted). Then, use the standard method
  to build a tree from both Preorder and Inorder traversals.
- Time complexity: O(N log N). Dominated by the initial sorting step.
- Space complexity: O(N) to store the auxiliary `inorder` array and map (for fast lookups).
- Limitations: Sorting is an unnecessary step and adds complexity beyond O(N).

✅ Optimized Approachs
- Idea: Exploit the property that in a BST, for any node X, all values in its
  left subtree must be less than X, and all values in its right subtree must be
  greater than X. We can use this to establish upper and lower bounds for
  each recursive call.
- Approach: Recursive Construction with Range Bounds (Single Pass).
- Algorithm:
    1. Use a recursive helper function that takes the `preorder` array, a mutable
       index `i` (to track the current element), and inclusive `low` and exclusive `high`
       bounds (the valid range for the current subtree's root).
    2. Base Case: If the index `i` is out of bounds, or if the current element
       `preorder[i]` falls outside the `[low, high)` range, return `nullptr`.
    3. Create the `root` node from `preorder[i]` and advance `i`.
    4. Recursively build the **left subtree**: The new upper bound is `root->val`.
       The new range is `[low, root->val)`.
    5. Recursively build the **right subtree**: The new lower bound is `root->val`.
       The new range is `[root->val, high)`.
- Time complexity: O(N). Every element in the `preorder` array is visited and processed
  exactly once.
- Space complexity: O(H). For the recursive call stack, where H is the height of the tree.

💡 Key Pattern:
- **Preorder + Bounding:** When reconstructing a BST from Preorder (or Postorder),
  defining a valid range (`[low, high]`) for node values is the key to an efficient,
  single-pass solution.

ℹ️ Keywords:
- Binary Search Tree, BST, Preorder Traversal, Recursion, Upper Bound, Lower Bound

🗒️ Notes
- (What did I learn? Similar problems? Mistakes I made?)
- The time complexity for this approach is optimal, as we must read all N elements.
- The use of the mutable index `i` is crucial to ensure both recursive calls continue
  the traversal from the correct point in the *single* preorder sequence.
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
     * @brief Constructs a BST from its preorder traversal using recursive bounding.
     * @param preorder The preorder traversal of the BST.
     * @return The root of the constructed BST.
     */
    TreeNode *bstFromPreorder(vector<int> &preorder)
    {
        // Initialize the preorder index to 0.
        int i = 0;
        // Start the recursive build with the largest possible bounds.
        return build(preorder, i, INT_MIN, INT_MAX);
    }

private:
    /**
     * @brief Recursive helper to build the BST.
     * @param pre The preorder array.
     * @param i The current index in the preorder array (passed by reference).
     * @param low The minimum valid value for the current root (inclusive).
     * @param high The maximum valid value for the current root (exclusive).
     * @return The root of the constructed subtree.
     */
    TreeNode *build(const vector<int> &pre, int &i, int low, int high)
    {
        // Base Case 1: All nodes processed.
        // Base Case 2: Current value is outside the valid range set by ancestors.
        if (i == pre.size() || pre[i] < low || pre[i] > high)
            return nullptr;

        // The current element in the preorder sequence must be the root.
        TreeNode *root = new TreeNode(pre[i++]);

        // Build Left Subtree: New upper bound is the current root's value.
        root->left = build(pre, i, low, root->val);

        // Build Right Subtree: New lower bound is the current root's value.
        root->right = build(pre, i, root->val, high);

        return root;
    }
};

// Helper function for Preorder Traversal (for verification)
void preorderTraversal(TreeNode *root)
{
    if (!root)
        return;
    cout << root->val << " ";
    preorderTraversal(root->left);
    preorderTraversal(root->right);
}

int main()
{
    Solution sol;

    // Test Case 1: Example from LeetCode
    // Preorder: [8, 5, 1, 7, 10, 12]
    // Expected BST:
    //          8
    //        /   \
    //       5     10
    //      / \     \
    //     1   7     12
    vector<int> preorder1 = {8, 5, 1, 7, 10, 12};
    TreeNode *root1 = sol.bstFromPreorder(preorder1);

    cout << "--- Construct BST from Preorder Traversal ---" << endl;
    cout << "Input Preorder 1: 8 5 1 7 10 12" << endl;
    cout << "Output Preorder 1: ";
    preorderTraversal(root1);
    cout << endl;

    // Test Case 2: Skewed Tree (Ascending order)
    // Preorder: [1, 2, 3, 4]
    // Expected BST (Right skewed): 1 -> 2 -> 3 -> 4
    vector<int> preorder2 = {1, 2, 3, 4};
    TreeNode *root2 = sol.bstFromPreorder(preorder2);

    cout << "Input Preorder 2: 1 2 3 4" << endl;
    cout << "Output Preorder 2: ";
    preorderTraversal(root2);
    cout << endl;

    // Test Case 3: Empty
    vector<int> preorder3 = {};
    TreeNode *root3 = sol.bstFromPreorder(preorder3);

    cout << "Input Preorder 3: (empty)" << endl;
    cout << "Output Preorder 3: ";
    if (!root3)
        cout << "nullptr";
    preorderTraversal(root3);
    cout << endl;

    return 0;
}
