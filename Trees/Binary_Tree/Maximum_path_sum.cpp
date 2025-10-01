/*
File: Maximum_path_sum.cpp
Date: 2025-10-01 14:50

Problem: Maximum path sum
Link: https://leetcode.com/problems/binary-tree-maximum-path-sum/description/

Problem Statement:
Given the root of a binary tree, find the maximum path sum. A path is defined
as any sequence of nodes from some starting node to any node, which may or may
not include the root. The path must contain at least one node.

-------------------------------------------------
❌ Brute Force
- Idea: For every node, calculate the path sum for all possible paths that
  pass through it. Requires multiple depth traversals for each node.
- Time complexity: O(N^2), as calculating all path sums through a node
  can take O(N) time, repeated for $N$ nodes.
- Space complexity: O(H) for the recursion stack.
- Limitations: Highly inefficient due to redundant subtree sum calculations.

✅ Optimized Approachs
- Idea: Use a single Post-order DFS pass to simultaneously track the **global
  maximum path** (V-shape) and the **maximum path extending upwards**
  (single branch).
- Approach: Depth-First Search (Post-order Traversal with reference variable).
- Algorithm:
    1. A helper function dfs(node, maxSum) returns the maximum path
       sum that *can be extended* from node to its parent.
    2. Inside $\text{dfs}$: Recursively find max paths from left/right,
       discarding negative contributions using max(0, sum).
    3. Calculate the potential **global maximum path** through the current
       node: node.val + leftMax + rightMax.
    4. Update the global maxSum with this new potential maximum.
    5. Return the **maximum path to extend upward**: node.val + max(leftMax, rightMax).
- Time complexity: O(N)$, as every node is visited exactly once.
- Space complexity: O(H), where H is the height of the tree (for the
  recursion stack).

💡 Key Pattern:
- **Two Metrics in One DFS:** Simultaneously calculate a local metric
  (extendable path) and update a global metric (total max path).
- **Handling Negatives:** Use max(0, subtree sum) to ensure
  subtrees with negative sums are ignored, maximizing the path.

ℹ️ Keywords:
- Binary Tree, Path Sum, DFS, Post-order, Recursion, Global Maximum

🗒️ Notes
- (What did I learn? Similar problems? Mistakes I made?)
- Crucial distinction: The value returned (node.val + max(left, right))
  is different from the value used to update the global max sum
  (node.val + left + right).
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
     * @brief Finds the maximum path sum in the binary tree.
     * @param root The root of the binary tree.
     * @return The maximum path sum found in the entire tree.
     */
    int maxPathSum(TreeNode *root)
    {
        // Initialize maxSum to the smallest possible integer value.
        int maxSum = INT_MIN;
        // The DFS function updates maxSum by reference.
        dfs(root, maxSum);
        return maxSum;
    }

private:
    /**
     * @brief DFS function to find the max path sum that can be extended
     * upward from the current node. It updates the global max sum.
     * @param node The current node in the traversal.
     * @param maxSum Reference to the global maximum path sum found so far.
     * @return The maximum path sum starting at 'node' and going down one branch.
     */
    int dfs(TreeNode *node, int &maxSum)
    {
        // Base case: An empty node contributes 0 to the path sum.
        if (!node)
            return 0;

        // 1. Calculate max gain from left and right children.
        // We use max(0, ...) to effectively discard any subtree that returns
        // a negative sum, as including it would only decrease the total path sum.
        int leftGain = max(0, dfs(node->left, maxSum));
        int rightGain = max(0, dfs(node->right, maxSum));

        // 2. Calculate the potential **maximum V-shaped path** that passes
        //    through the current 'node' (local maximum path sum).
        // This path includes $\text{node.val}$, $\text{leftGain}$, and $\text{rightGain}$.
        int currentPathSum = node->val + leftGain + rightGain;

        // 3. Update the global maximum path sum.
        maxSum = max(maxSum, currentPathSum);

        // 4. Return the **maximum single-branch path** that can be extended
        //    *upward* to the parent node. A path extending upward cannot use
        //    both left and right branches.
        return node->val + max(leftGain, rightGain);
    }
};

int main()
{
    Solution sol;

    // Test Case 1: Expected output 6 (Path: 2 -> 1 -> 3)
    //        1
    //       / \
    //      2   3
    TreeNode *root1 = new TreeNode(1, new TreeNode(2), new TreeNode(3));
    cout << "Max Path Sum 1 (Expected 6): "
         << sol.maxPathSum(root1) << endl;

    // Test Case 2: Expected output 42 (Path: 9 -> 20 -> 15 or 9 -> 20 -> 7)
    //        -10
    //        / \
    //       9  20
    //         /  \
    //        15   7
    TreeNode *root2 = new TreeNode(-10,
                                   new TreeNode(9),
                                   new TreeNode(20, new TreeNode(15), new TreeNode(7)));

    cout << "Max Path Sum 2 (Expected 42): "
         << sol.maxPathSum(root2) << endl;

    // Note: Memory deallocation omitted for brevity in simple test harness.

    return 0;
}
