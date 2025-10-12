/*
File: Maximum_Sum_BST_in_Binary_Tree.cpp
Date: 2025-10-12 22:04

Problem: Maximum Sum BST in Binary Tree
Link: https://leetcode.com/problems/maximum-sum-bst-in-binary-tree/description/

Problem Statement:
Given a binary tree, find the maximum sum of all nodes in any sub-tree that is also
a Binary Search Tree (BST).

-------------------------------------------------
❌ Brute Force
- Idea: For every node in the given tree, treat it as the root of a potential BST.
  For each such node:
    1. Check if the subtree rooted at this node is a valid BST.
    2. If it is valid, calculate the sum of all nodes in that subtree.
    3. Update the global maximum sum.
- Time complexity: O(N^2). We check N nodes, and validating/summing a subtree takes O(size of subtree), resulting in an aggregate O(N^2).
- Space complexity: O(H). For the recursive call stack.
- Limitations: Highly inefficient due to redundant checks on overlapping subtrees.

✅ Optimized Approachs
- Idea: Use a single **Post-order Traversal (DFS)** to simultaneously validate the BST property and calculate the sum and required boundaries (min/max values) for the parent node. This is a form of Dynamic Programming on trees.
- Approach: Recursive Post-order DFS returning Node Information.
- Algorithm:
    1. Define a helper structure (or tuple) `Info` to return four key pieces of data from a subtree:
        - `isBST`: boolean, is the current subtree a valid BST?
        - `sum`: int, the sum of the subtree if it is a BST (0 otherwise).
        - `minVal`: int, the minimum value in the subtree (required for parent's right child check).
        - `maxVal`: int, the maximum value in the subtree (required for parent's left child check).
    2. In the `dfs` function, recursively call children first (Post-order).
    3. Check the three BST conditions for the current `root`:
        a. `left.isBST` must be true.
        b. `right.isBST` must be true.
        c. `root->val` must be greater than `left.maxVal` AND less than `right.minVal`.
    4. If all conditions pass, the current subtree is a BST. Calculate the total sum, update the global `maxSum`, and return `isBST=true` with the new min/max bounds.
    5. If any condition fails, return `isBST=false`.
- Time complexity: O(N). Every node is visited and processed exactly once.
- Space complexity: O(H). For the recursive function call stack.

💡 Key Pattern:
- **Post-order/Bottom-Up Traversal:** When a node's property (like being a BST) depends entirely on the properties of its children, a bottom-up approach is necessary.
- **Passing Multiple Results:** Returning a struct/object that encapsulates all necessary information (validity, sum, and bounds) allows the single pass to work efficiently.

ℹ️ Keywords:
- Binary Search Tree, BST, DFS, Post-order, Dynamic Programming, Subtree Sum, Min/Max

🗒️ Notes
- Using `INT_MAX` for the min bound of an empty tree and `INT_MIN` for the max bound of an empty tree is crucial for the base case to satisfy the parent's BST check correctly.
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
     * @brief Finds the maximum sum of all nodes in any sub-tree that is also a BST.
     * @param root The root of the binary tree.
     * @return The maximum sum found.
     */
    int maxSum = 0;

    /**
     * @brief Struct to hold the required information from a subtree.
     */
    struct Info
    {
        bool isBST;
        int sum;
        int minVal; // Minimum value in the subtree
        int maxVal; // Maximum value in the subtree
    };

    /**
     * @brief Recursive DFS (Post-order) to validate BST and calculate sums.
     */
    Info dfs(TreeNode *root)
    {
        // Base Case: Empty node is considered a valid BST with 0 sum.
        // INT_MAX and INT_MIN ensure the parent node's BST checks pass correctly.
        if (!root)
            return {true, 0, INT_MAX, INT_MIN};

        // Post-order traversal: Recurse on children first
        Info left = dfs(root->left);
        Info right = dfs(root->right);

        // Check if the current subtree is a valid BST
        if (left.isBST && right.isBST && // 1. Children must be BSTs
            root->val > left.maxVal &&   // 2. Root must be > Max of left subtree
            root->val < right.minVal)
        { // 3. Root must be < Min of right subtree

            // If valid: Calculate sum and update global max
            int currSum = root->val + left.sum + right.sum;
            maxSum = max(maxSum, currSum);

            // Return valid Info: New min/max are determined by the current root or children's min/max
            return {true, currSum, min(root->val, left.minVal),
                    max(root->val, right.maxVal)};
        }

        // If invalid: Set isBST to false and return sentinel values.
        // Min/Max are set to values that will guarantee the parent check fails (e.g., INT_MIN/INT_MAX).
        return {false, 0, INT_MIN, INT_MAX};
    }

    int maxSumBST(TreeNode *root)
    {
        maxSum = 0; // Reset for potential multiple calls or testing
        dfs(root);
        return maxSum;
    }
};

// --- Test Helper Functions ---

// Creates a sample binary tree for testing
TreeNode *createTestTree()
{
    // Tree Structure (Max Sum BST is 18, rooted at 8)
    //         5
    //       /   \
    //      4     8  <- Valid BST (sum 18)
    //     / \   / \
    //    3   6 7   9
    //        ^ Fails BST property for root 5 (6 is not < 5)

    TreeNode *n3 = new TreeNode(3);
    TreeNode *n6 = new TreeNode(6);
    TreeNode *n4 = new TreeNode(4, n3, n6); // Subtree at 4 is NOT a BST (4 < 6 fails)

    TreeNode *n7 = new TreeNode(7);
    TreeNode *n9 = new TreeNode(9);
    TreeNode *n8 = new TreeNode(8, n7, n9); // Subtree at 8 IS a BST (sum 24)

    TreeNode *root = new TreeNode(5, n4, n8);

    // Corrected structure to match the LeetCode example for clarity:
    // Max Sum BST should be the right subtree rooted at 8 (sum 24).
    // The current max sum BST is 7+8+9 = 24

    // Test Case A (Corrected to show max sum is a subtree):
    //        1
    //       / \
    //      4  10
    //     / \
    //    6   3
    // Subtree at 4 (6, 4, 3) is NOT a BST.
    // Subtree at 10 is BST (sum 10).
    // Subtree at 6 is BST (sum 6).
    // Max sum should be 10 or 6. Let's use the provided structure for max sum in a subtree:
    //          -4
    //         / \
    //        1   8
    //       / \ / \
    //      6  -1 7  9

    TreeNode *n6_ = new TreeNode(6);
    TreeNode *n_1 = new TreeNode(-1);
    TreeNode *n1 = new TreeNode(1, n6_, n_1); // Fails BST: 1 < 6, 1 > -1. OK

    TreeNode *n7 = new TreeNode(7);
    TreeNode *n9 = new TreeNode(9);
    TreeNode *n8 = new TreeNode(8, n7, n9); // Valid BST (sum 24)

    TreeNode *root2 = new TreeNode(-4, n1, n8); // Fails BST: -4 < 8, -4 < -1 (max of left is -1). Fails.

    return root2; // Max sum BST is the subtree at 8 (7+8+9 = 24)
}

int main()
{
    Solution sol;

    cout << "--- Maximum Sum BST in Binary Tree Test Cases ---" << endl;

    // Test Case 1: Max Sum is in a proper subtree
    TreeNode *root1 = createTestTree();
    // Tree:
    //          -4
    //         / \
    //        1   8  (BST sum 24)
    //       / \ / \
    //      6  -1 7  9
    // Expected Max Sum: 24 (from subtree rooted at 8: 7, 8, 9)
    int res1 = sol.maxSumBST(root1);
    cout << "Test 1 (Subtree Max): Result = " << res1 << " (Expected: 24)" << endl;

    // Test Case 2: Max Sum is the whole tree (if valid)
    // Structure: 2, 4, 6, 8, 10
    //          6
    //        /   \
    //       4     8
    //      / \   / \
    //     2   5 7   10
    TreeNode *t2_2 = new TreeNode(2);
    TreeNode *t2_5 = new TreeNode(5);
    TreeNode *t2_4 = new TreeNode(4, t2_2, t2_5);
    TreeNode *t2_7 = new TreeNode(7);
    TreeNode *t2_10 = new TreeNode(10);
    TreeNode *t2_8 = new TreeNode(8, t2_7, t2_10);
    TreeNode *root2 = new TreeNode(6, t2_4, t2_8);
    // Expected Sum: 6 + (4+2+5) + (8+7+10) = 6 + 11 + 25 = 42
    int res2 = sol.maxSumBST(root2);
    cout << "Test 2 (Full Tree Max): Result = " << res2 << " (Expected: 42)" << endl;

    // Test Case 3: Max Sum is 0 (only negative numbers, but valid BST is found)
    // If the largest valid BST has only negative numbers, the max sum is still that negative sum.
    //          -10
    //         /   \
    //        -5   -15
    //       /
    //      -6
    TreeNode *t3_n6 = new TreeNode(-6);
    TreeNode *t3_n5 = new TreeNode(-5, t3_n6, nullptr);
    TreeNode *t3_n15 = new TreeNode(-15);
    TreeNode *root3 = new TreeNode(-10, t3_n5, t3_n15);
    // Expected Sum: -10 + (-5 + -6) + (-15) = -36
    int res3 = sol.maxSumBST(root3);
    cout << "Test 3 (Negative Sum): Result = " << res3 << " (Expected: -36)" << endl;

    // Note: Memory deallocation omitted for brevity in simple test harness.

    return 0;
}
