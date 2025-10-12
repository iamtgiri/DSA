/*
File: Children_Sum_in_a_Binary_Tree.cpp
Date: 2025-10-12 22:31

Problem: Children Sum in a Binary Tree
Link: https://www.geeksforgeeks.org/problems/children-sum-parent/1

Problem Statement:
Given a binary tree, check whether it satisfies the Children Sum Property.
The Children Sum Property is satisfied if for every node, the data value of the
node is equal to the sum of the data values of its children (if they exist).
Note: For leaf nodes, the property is always true.

-------------------------------------------------
❌ Brute Force
- Idea: There is no significantly 'brute force' approach here, as any solution must check all parent nodes.
  The most straightforward approach is inherently optimal in terms of node visits.
- Time complexity: O(N)
- Space complexity: O(H)
- Limitations: Not applicable.

✅ Optimized Approachs
- Idea: Use a **Pre-order or Post-order Traversal (DFS)** to visit every node and check the Children Sum Property locally. The validity of the entire tree depends on the validity of the current node and the recursive results from its children.
- Approach: Recursive Depth-First Search (DFS).
- Algorithm:
    1. Base Case: If the node is `nullptr` or a leaf node, return `true`.
    2. Calculate the sum of the children's values. If a child is `nullptr`, its value is considered 0.
    3. Check the current node: If `root->val` is not equal to the calculated `sum`, return `false`.
    4. Recurse: Return `true` only if both `isSumProperty(root->left)` AND `isSumProperty(root->right)` return `true`.
- Time complexity: O(N). Every node is visited exactly once.
- Space complexity: O(H). Due to the recursive function call stack, where H is the height of the tree.

💡 Key Pattern:
- **Recursive Tree Property Check:** Many tree properties (like balance, height, or sum property) are checked most efficiently by combining a local check at the current node with the recursive results from its children.
- **Base Case Handling:** Correctly defining the base case for leaf nodes (`true`) is crucial.

ℹ️ Keywords:
- Binary Tree, Children Sum Property, DFS, Pre-order, Recursion

🗒️ Notes
- The provided implementation uses a clean, top-down recursive approach. It immediately returns `false` if a violation is found, ensuring quick failure.
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
     * @brief Checks if the given binary tree satisfies the Children Sum Property.
     * @param root The root of the binary tree.
     * @return true if the property is satisfied for all nodes, false otherwise.
     */
    bool isSumProperty(TreeNode *root)
    {
        // Base case: Null node or Leaf node always satisfies the property.
        if (!root || (!root->left && !root->right))
            return true;

        // Calculate the sum of children's values (0 if a child is null).
        int total = 0;
        if (root->left)
            total += root->left->val;
        if (root->right)
            total += root->right->val;

        // Check the current node's property
        if (total != root->val)
            return false;

        // Recursively check children
        return isSumProperty(root->left) && isSumProperty(root->right);
    }
};

// --- Test Helper Functions ---

// Helper function to create a test tree
TreeNode *createTree(int rootVal, TreeNode *left, TreeNode *right)
{
    return new TreeNode(rootVal, left, right);
}

int main()
{
    Solution sol;

    cout << "--- Children Sum in a Binary Tree Test Cases ---" << endl;

    // Test Case 1: Valid Tree (Simple)
    //    10
    //   /  \
    //  4    6
    TreeNode *t1_4 = createTree(4, nullptr, nullptr);
    TreeNode *t1_6 = createTree(6, nullptr, nullptr);
    TreeNode *root1 = createTree(10, t1_4, t1_6);
    bool res1 = sol.isSumProperty(root1);
    cout << "Test 1 (Valid Simple): Result = " << (res1 ? "true" : "false") << " (Expected: true)" << endl;

    // Test Case 2: Valid Tree (Complex)
    //        20
    //       /  \
    //      8    12
    //     / \   / \
    //    3   5 6   6
    TreeNode *t2_3 = createTree(3, nullptr, nullptr);
    TreeNode *t2_5 = createTree(5, nullptr, nullptr);
    TreeNode *t2_6a = createTree(6, nullptr, nullptr);
    TreeNode *t2_6b = createTree(6, nullptr, nullptr);
    TreeNode *t2_8 = createTree(8, t2_3, t2_5);     // 3 + 5 = 8 (OK)
    TreeNode *t2_12 = createTree(12, t2_6a, t2_6b); // 6 + 6 = 12 (OK)
    TreeNode *root2 = createTree(20, t2_8, t2_12);  // 8 + 12 = 20 (OK)
    bool res2 = sol.isSumProperty(root2);
    cout << "Test 2 (Valid Complex): Result = " << (res2 ? "true" : "false") << " (Expected: true)" << endl;

    // Test Case 3: Invalid Tree (Failure at Root)
    //    10
    //   /  \
    //  7    6  (7+6 = 13 != 10)
    TreeNode *t3_7 = createTree(7, nullptr, nullptr);
    TreeNode *t3_6 = createTree(6, nullptr, nullptr);
    TreeNode *root3 = createTree(10, t3_7, t3_6);
    bool res3 = sol.isSumProperty(root3);
    cout << "Test 3 (Invalid Root): Result = " << (res3 ? "true" : "false") << " (Expected: false)" << endl;

    // Test Case 4: Invalid Tree (Failure deep down)
    //        20
    //       /  \
    //      8    13
    //     / \   / \
    //    3   5 6   7 (6+7 = 13 != 13. Wait, this passes 6+7=13. Let's make it fail.)
    //        20
    //       /  \
    //      8    12
    //     / \   / \
    //    3   5 6   7 (6+7 = 13 != 12, Fails at node 12)
    TreeNode *t4_3 = new TreeNode(3);
    TreeNode *t4_5 = new TreeNode(5);
    TreeNode *t4_6 = new TreeNode(6);
    TreeNode *t4_7 = new TreeNode(7);
    TreeNode *t4_8 = createTree(8, t4_3, t4_5);    // 3 + 5 = 8 (OK)
    TreeNode *t4_12 = createTree(12, t4_6, t4_7);  // 6 + 7 = 13 (!= 12) (FAIL)
    TreeNode *root4 = createTree(20, t4_8, t4_12); // 8 + 12 = 20 (OK)
    bool res4 = sol.isSumProperty(root4);
    cout << "Test 4 (Invalid Deep): Result = " << (res4 ? "true" : "false") << " (Expected: false)" << endl;

    // Note: Memory deallocation omitted for brevity in simple test harness.

    return 0;
}
