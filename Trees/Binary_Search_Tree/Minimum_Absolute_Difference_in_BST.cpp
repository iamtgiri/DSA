/*
File: Minimum_Absolute_Difference_in_BST.cpp
Date: 2025-11-19 01:02

Problem: Minimum Absolute Difference in BST
Link: https://leetcode.com/problems/minimum-absolute-difference-in-bst/description/

Problem Statement:
Given the root of a Binary Search Tree (BST), return the minimum absolute difference between the values of any two different nodes in the tree.

-------------------------------------------------
Brute Force (if any, ignore if not applicable)
- Idea: Store all node values into a list by performing any traversal (pre-order, post-order, BFS). Then, sort the list and iterate through the sorted list to find the minimum difference between adjacent elements.
- Time complexity: O(N log N) (N for traversal + N log N for sorting).
- Space complexity: O(N) (To store all N node values).
- Limitations: Sorting step is unnecessary overhead when we can leverage the BST property.

Current/Optimized Approachs
- Idea: Exploit the property that **In-order Traversal of a BST yields a sorted sequence**. The minimum difference between any two nodes must occur between two consecutive elements in this sorted sequence.
- Approach: **In-order Traversal**
- Algorithm:
  1. Define a helper function `inorder(root, prev, ans)` to perform the traversal.
  2. Maintain a global minimum difference `ans` initialized to `INT_MAX`.
  3. Maintain a reference to the `prev`iously visited node's value. Initialize `prev` to `-1` (or use a pointer/optional value) to mark the first node.
  4. During traversal (L -> Root -> R):
     a. Recurse on the left child (`inorder(root->left, ...)`).
     b. **Process the current node (Root):**
        i. If `prev` is not the initial value, calculate the difference: `root->val - prev`.
        ii. Update `ans = min(ans, root->val - prev)`.
        iii. Set `prev = root->val`.
     c. Recurse on the right child (`inorder(root->right, ...)`).
- Time complexity: **O(N)**. Every node is visited exactly once.
- Space complexity: **O(H)**, where H is the height of the tree (for the recursion stack). O(log N) for balanced, O(N) for skewed.

💡 Key Pattern:
- **BST In-order Traversal Property**: The most crucial pattern for problems related to node ordering, range queries, or differences in a BST.

ℹ️ Keywords:
- In-order Traversal, BST Property, Sorted Sequence, Minimum Difference, DFS.

🗒️ Notes
- Using the `prev` variable to keep track of the value of the last *processed* node (which is the immediate predecessor in the sorted sequence) is the key to the O(N) solution.
- The base case for the difference calculation handles the very first node correctly.
-------------------------------------------------
*/

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>
#include <cmath>

using namespace std;

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
private:
    // Tracks the value of the node immediately before the current node in the sorted sequence.
    int prev_val = -1; 
    // Stores the minimum absolute difference found so far.
    int min_diff = INT_MAX;

    /**
     * @brief Performs In-order Traversal to find the minimum absolute difference.
     * @param root The current node.
     */
    void inorder_traversal(TreeNode* root) {
        if (!root) {
            return;
        }

        // 1. Traverse Left
        inorder_traversal(root->left);

        // 2. Process Root (This is where the difference check happens)
        if (prev_val != -1) {
            // The current node's value is guaranteed to be greater than prev_val
            min_diff = min(min_diff, root->val - prev_val);
        }
        
        // Update prev_val to the current node's value for the next comparison
        prev_val = root->val;

        // 3. Traverse Right
        inorder_traversal(root->right);
    }

public:
    /**
    * @brief Finds the minimum absolute difference between any two nodes in a BST.
    * @param root The root of the BST.
    * @return The minimum absolute difference.
    */
    int getMinimumDifference(TreeNode* root) {
        // Reset class members for multiple test cases (optional in LeetCode environment, but good practice)
        prev_val = -1;
        min_diff = INT_MAX;
        
        inorder_traversal(root);
        return min_diff;
    }

};

// Helper function to build the tree (not strictly part of the solution but useful for main)
TreeNode* createNode(int val) { return new TreeNode(val); }

int main() {
    Solution sol;
    
    // --- Example 1: [4, 2, 6, 1, 3]
    // In-order sequence: 1, 2, 3, 4, 6
    // Differences: |2-1|=1, |3-2|=1, |4-3|=1, |6-4|=2
    // Minimum: 1
    TreeNode* root1 = createNode(4);
    root1->left = createNode(2);
    root1->right = createNode(6);
    root1->left->left = createNode(1);
    root1->left->right = createNode(3);

    cout << "Test Case 1: [4, 2, 6, 1, 3]" << endl;
    int result1 = sol.getMinimumDifference(root1);
    cout << "Result: " << result1 << " (Expected: 1)" << endl;
    
    // --- Example 2: [1, 0, 48, null, null, 12, 49]
    // In-order sequence: 0, 1, 12, 48, 49
    // Differences: |1-0|=1, |12-1|=11, |48-12|=36, |49-48|=1
    // Minimum: 1
    TreeNode* root2 = createNode(1);
    root2->left = createNode(0);
    root2->right = createNode(48);
    root2->right->left = createNode(12);
    root2->right->right = createNode(49);
    
    cout << "\nTest Case 2: [1, 0, 48, null, null, 12, 49]" << endl;
    int result2 = sol.getMinimumDifference(root2);
    cout << "Result: " << result2 << " (Expected: 1)" << endl;

    return 0;
}