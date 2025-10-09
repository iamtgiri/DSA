/*
File: Kth_Smallest_Element_in_a_BST.cpp
Date: 2025-10-09 10:22

Problem: Kth Smallest Element in a BST
Link: https://leetcode.com/problems/kth-smallest-element-in-a-bst/description/

Problem Statement:
Given the root of a Binary Search Tree (BST) and an integer k, return the k-th
smallest value (1-indexed) of all the values of the nodes in the tree.

-------------------------------------------------
❌ Brute Force
- Idea: Perform a full Inorder Traversal of the BST to get all elements in a sorted list.
  Then, return the element at index k-1.
- Time complexity: O(N). Requires traversing all N nodes regardless of k.
- Space complexity: O(N) to store the list of N elements and O(H) for the recursion stack.
- Limitations: Inefficient as it calculates all elements when only the k-th is needed.

❌ Brute Force (Rank-Based Without Augmentation)
- Idea: Recursively calculate the size (rank) of the left subtree at the current
  node. If size + 1 equals k, return root->val. If size + 1 > k, search left.
  If size + 1 < k, search right for k - (size + 1).
- Time complexity: O(N^2) in the worst case (skewed tree) because the full `rank()`
  function is called repeatedly, leading to redundant O(N) work at each level.
- Space complexity: O(H) for the recursive call stack.
- Limitations: Extremely inefficient due to recalculating subtree sizes (ranks)
  at every step.

✅ Optimized Approachs (Inorder Traversal)
- Idea: The **Inorder Traversal** of a BST visits nodes in ascending sorted order.
  We can perform this traversal and use a counter to stop immediately after
  visiting the k-th node.
- Approach: Recursive Inorder Traversal with Early Termination.
- Algorithm:
    1. Use a recursive DFS helper (`inorder`) that tracks the global `count` and `result` by reference.
    2. Traverse the left child.
    3. At the root, increment `count`. If `count == k`, store `root->val` in `result`
       and immediately return to stop further recursion.
    4. Traverse the right child only if the result has not yet been found (`result != -1`).
- Time complexity: O(H + k). We only visit the path down to the k-th node and up,
  which is proportional to the height H plus the count k.
- Space complexity: O(H) for the recursive function call stack.

💡 Key Pattern:
- **Inorder Traversal:** The canonical method for any problem involving ordered elements
  in a BST.
- **Early Termination:** Essential for achieving the best time complexity, O(H+k),
  by avoiding unnecessary traversal of the remaining tree.

ℹ️ Keywords:
- Binary Search Tree, BST, Inorder Traversal, Kth Smallest, Order Statistics, O(H+k)

🗒️ Notes
- (What did I learn? Similar problems? Mistakes I made?)
- An iterative solution using a stack can achieve the same time complexity O(H+k)
  but with slightly different space characteristics (O(H) stack space vs. O(H) recursion stack).
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
     * @brief Finds the k-th smallest element in a BST using the optimized Inorder Traversal.
     * @param root The root of the BST.
     * @param k The desired rank (1-indexed).
     * @return The value of the k-th smallest element. Returns -1 if k is out of range.
     */
    int kthSmallest(TreeNode *root, int k)
    {
        return kthSmallestOpt(root, k);
    }

    /**
     * @brief Inefficient rank-based approach (O(N^2)). Only included for comparison.
     */
    int kthSmallestBruteForce(TreeNode *root, int k)
    {
        if (!root)
            return -1;

        int curr_rank = rank(root->left) + 1;
        if (curr_rank == k)
            return root->val;
        else if (curr_rank > k)
            return kthSmallestBruteForce(root->left, k);
        else
            return kthSmallestBruteForce(root->right, k - curr_rank);
    }

    /**
     * @brief Optimized Inorder Traversal approach (O(H+k)).
     */
    int kthSmallestOpt(TreeNode *root, int k)
    {
        int count = 0;
        int result = -1;
        inorder(root, k, count, result);
        return result;
    }

private:
    /**
     * @brief Helper function for recursive Inorder Traversal with early termination.
     */
    void inorder(TreeNode *root, int k, int &count, int &result)
    {
        // Base case: If root is null or we have already found the result, return.
        if (!root || result != -1)
            return;

        // 1. Traverse Left (Smaller elements)
        inorder(root->left, k, count, result);

        // Check for early termination after left subtree
        if (result != -1)
            return;

        // 2. Process Root
        count++;
        if (count == k)
        {
            result = root->val; // Found the k-th smallest element
            return;             // Terminate this branch
        }

        // 3. Traverse Right (Larger elements)
        inorder(root->right, k, count, result);
    }

    /**
     * @brief Helper function to calculate the size (rank) of a subtree (O(N)).
     */
    int rank(TreeNode *root)
    {
        if (!root)
            return 0;

        int left = rank(root->left);
        int right = rank(root->right);
        return 1 + left + right;
    }
};

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
    // Inorder sequence: 0, 2, 3, 4, 5, 6, 7, 8, 9

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

    cout << "--- Kth Smallest Element in BST (Optimized O(H+k)) ---" << endl;

    // Test 1: k=1 (Smallest element). Expected: 0
    int k1 = 1;
    int res1 = sol.kthSmallest(root, k1);
    cout << "K=" << k1 << " Smallest: " << res1 << " (Expected: 0)" << endl;

    // Test 2: k=5 (Median/Middle element). Expected: 5
    int k2 = 5;
    int res2 = sol.kthSmallest(root, k2);
    cout << "K=" << k2 << " Smallest: " << res2 << " (Expected: 5)" << endl;

    // Test 3: k=9 (Largest element). Expected: 9
    int k3 = 9;
    int res3 = sol.kthSmallest(root, k3);
    cout << "K=" << k3 << " Smallest: " << res3 << " (Expected: 9)" << endl;

    // Test 4: k=10 (Out of bounds). Expected: -1
    int k5 = 10;
    int res5 = sol.kthSmallest(root, k5);
    cout << "K=" << k5 << " Smallest: " << res5 << " (Expected: -1)" << endl;

    // Note: Memory deallocation omitted for brevity in simple test harness.

    return 0;
}
