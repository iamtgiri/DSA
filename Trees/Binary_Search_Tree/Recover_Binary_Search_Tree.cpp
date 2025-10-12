/*
File: Recover_Binary_Search_Tree.cpp
Date: 2025-10-12 10:51

Problem: Recover Binary Search Tree
Link: https://leetcode.com/problems/recover-binary-search-tree/description/

Problem Statement:
You are given the roots of a Binary Search Tree (BST) where exactly two nodes
of the tree were swapped by mistake. Recover the tree without changing its structure.
You do not need to return anything, just modify the tree in-place.

-------------------------------------------------
❌ Brute Force
- Idea: Flatten the BST into a sorted array (Inorder traversal) along with a list of node pointers.
  Sort a copy of the values array. Compare the sorted values with the current node values
  to identify the two nodes whose values must be swapped.
- Time complexity: O(N log N). Dominated by the sorting step.
- Space complexity: O(N). To store the list of N node pointers and N values.
- Limitations: Inefficient due to $O(N \log N)$ time and high auxiliary space.

✅ Optimized Approachs
- Idea: Exploit the property that an **Inorder Traversal** of a correct BST must yield
  elements in strictly ascending order. The two swapped nodes will cause one or two
  violations of the property (`prev->val > node->val`).
- Approach: Inorder Traversal with Pointers to track Inversions.
- Algorithm:
    1. Perform a recursive Inorder Traversal, tracking the `prev` visited node.
    2. Initialize three pointers: `first`, `second`, and `prev` (all to `nullptr`).
    3. During the traversal, if `prev` is not null and `prev->val > node->val`:
        a. This is a violation (an inversion).
        b. If `first` is still `nullptr`, this is the *first* violation. Set `first = prev` (the larger of the two misplaced nodes).
        c. Always set `second = node` (the smaller of the two misplaced nodes).
    4. After the traversal, `first` holds the larger misplaced node, and `second` holds
       the smaller misplaced node (regardless of whether the swap was adjacent or not).
    5. Swap `first->val` and `second->val`.
- Time complexity: O(N). Requires a single pass over all N nodes.
- Space complexity: O(H). Due to the recursive function call stack, where H is the height of the tree.

💡 Key Pattern:
- **Inorder Property Violation:** The single swap creates one or two places where the
  Inorder sequence is locally decreasing. By capturing the first node of the first
  violation and the second node of the last violation, we isolate the two swapped nodes.

ℹ️ Keywords:
- Binary Search Tree, BST, Inorder Traversal, In-place, Constant Space (if using Morris), Violation

🗒️ Notes
- The $O(H)$ space complexity is usually considered sufficient. If $O(1)$ auxiliary space
  is required (as per the follow-up note on LeetCode), **Morris Traversal** must be used
  to implement the Inorder traversal without using a stack.
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
     * @brief Recovers the BST by swapping the values of the two misplaced nodes.
     * Time: O(N), Space: O(H) (recursion stack).
     * @param root The root of the incorrectly formed BST.
     */
    void recoverTree(TreeNode *root)
    {
        // Pointers to the two swapped nodes
        TreeNode *first = nullptr;  // The first (larger) node of the swap
        TreeNode *second = nullptr; // The second (smaller) node of the swap
        TreeNode *prev = nullptr;   // Tracks the previously visited node in Inorder

        inorder(root, prev, first, second);

        // Final recovery: Swap the values of the identified nodes
        if (first && second)
            swap(first->val, second->val);
    }

private:
    /**
     * @brief Recursive Inorder Traversal to find the two misplaced nodes.
     */
    void inorder(TreeNode *node, TreeNode *&prev, TreeNode *&first,
                 TreeNode *&second)
    {
        if (!node)
            return;

        // 1. Traverse Left (L)
        inorder(node->left, prev, first, second);

        // 2. Process Root (N) - Check for inversion
        if (prev && prev->val > node->val)
        {
            // First violation found: The first misplaced node is always the previous node (larger value)
            if (!first)
                first = prev;

            // The second misplaced node is always updated to the current node (smaller value)
            // This handles both adjacent (one inversion) and non-adjacent (two inversions) swaps.
            second = node;
        }

        // Update previous node for the next comparison
        prev = node;

        // 3. Traverse Right (R)
        inorder(node->right, prev, first, second);
    }
};

// --- Test Helper Functions ---

// Creates a sample BST and intentionally swaps two nodes
TreeNode *createSwappedBST(bool adjacentSwap)
{
    // Correct BST structure: 1, 2, 3, 4, 5, 6
    //          4
    //        /   \
    //       2     6
    //      / \   /
    //     1   3 5
    TreeNode *n1 = new TreeNode(1);
    TreeNode *n3 = new TreeNode(3);
    TreeNode *n5 = new TreeNode(5);
    TreeNode *n2 = new TreeNode(2, n1, n3);
    TreeNode *n6 = new TreeNode(6, n5, nullptr);
    TreeNode *root = new TreeNode(4, n2, n6);

    if (adjacentSwap)
    {
        // Adjacent swap example: Swap 3 and 4
        // Correct Inorder: 1, 2, 3, 4, 5, 6
        // Swapped Inorder: 1, 2, 4, 3, 5, 6 (Inversion: 4 > 3)
        root->val = 3;
        n3->val = 4;
    }
    else
    {
        // Non-adjacent swap example: Swap 1 and 6
        // Correct Inorder: 1, 2, 3, 4, 5, 6
        // Swapped Inorder: 6, 2, 3, 4, 5, 1 (Inversions: 6 > 2, 5 > 1)
        n1->val = 6;
        n6->val = 1;
    }
    return root;
}

/**
 * @brief Print inorder traversal of the tree.   
 */
void printInorder(TreeNode *root)
{
    if (!root)
        return;
    printInorder(root->left);
    cout << root->val << " ";
    printInorder(root->right);
}

int main()
{
    Solution sol;

    // --- Test Case 1: Adjacent Swap ---
    // Swapped nodes: 3 and 4
    TreeNode *root_adj = createSwappedBST(true);
    cout << "--- Test Case 1: Adjacent Swap (3 and 4 swapped) ---" << endl;
    cout << "Initial Inorder: ";
    printInorder(root_adj); // Expected: 1 2 4 3 5 6
    cout << endl;

    sol.recoverTree(root_adj);

    cout << "Recovered Inorder: ";
    printInorder(root_adj); // Expected: 1 2 3 4 5 6 (Correct BST)
    cout << endl
         << endl;

    // --- Test Case 2: Non-Adjacent Swap ---
    // Swapped nodes: 1 and 6
    TreeNode *root_non_adj = createSwappedBST(false);
    cout << "--- Test Case 2: Non-Adjacent Swap (1 and 6 swapped) ---" << endl;
    cout << "Initial Inorder: ";
    printInorder(root_non_adj); // Expected: 6 2 3 4 5 1
    cout << endl;

    sol.recoverTree(root_non_adj);

    cout << "Recovered Inorder: ";
    printInorder(root_non_adj); // Expected: 1 2 3 4 5 6 (Correct BST)
    cout << endl;

    // Note: Memory deallocation omitted for brevity in simple test harness.

    return 0;
}
