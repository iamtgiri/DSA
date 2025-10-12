/*
File: Largest_BST_in_Binary_Tree.cpp
Date: 2025-10-12 22:07

Problem: Largest BST in Binary Tree
Link: https://www.geeksforgeeks.org/problems/largest-bst/1

Problem Statement:
Given a binary tree, find the size of the largest subtree which is also a valid
Binary Search Tree (BST).

-------------------------------------------------
❌ Brute Force
- Idea: For every node in the given tree, treat it as the root of a potential BST.
  For each such node, check if the subtree is a valid BST (O(N) check) and calculate its size.
- Time complexity: O(N^2). Checking and counting a subtree takes O(size of subtree), leading to an aggregate O(N^2).
- Space complexity: O(H). For the recursive call stack.
- Limitations: Highly inefficient due to redundant checks on overlapping subtrees.

✅ Optimized Approachs
- Idea: Use a single **Post-order Traversal (DFS)** to simultaneously validate the BST property and calculate the size and required boundaries (min/max values) for the parent node in a single pass. This is **Dynamic Programming** on the tree structure.
- Approach: Recursive Post-order DFS returning Subtree Information.
- Algorithm:
    1. Define a helper structure (`Info`) to return four key pieces of data from a subtree: `isBST`, `size`, `minVal`, and `maxVal`.
    2. The base case for an empty node returns `isBST=true`, `size=0`, `minVal=INT_MAX`, and `maxVal=INT_MIN`.
    3. Recursively call `dfs` on the left and right children (Post-order).
    4. Check the three BST conditions for the current `root`:
        a. `left.isBST` and `right.isBST` must be true.
        b. `root->val` must be greater than `left.maxVal`.
        c. `root->val` must be less than `right.minVal`.
    5. If all conditions pass, the current subtree is a BST. Calculate `currSize = left.size + right.size + 1`, update the global `maxSize`, and return `isBST=true` with the new min/max bounds.
    6. If any condition fails, return `isBST=false`.
- Time complexity: O(N). Every node is visited and processed exactly once.
- Space complexity: O(H). For the recursive function call stack.

💡 Key Pattern:
- **Post-order/Bottom-Up Traversal:** Essential when a node's property depends on a summary of its children (like the max value in the left subtree).
- **Consolidated State (Info Struct):** Returning validity, size, and boundary values together enables the $O(N)$ single-pass solution.

ℹ️ Keywords:
- Binary Search Tree, BST, DFS, Post-order, Dynamic Programming, Subtree Size, Min/Max

🗒️ Notes
- The logic is nearly identical to the "Maximum Sum BST" problem, demonstrating a powerful tree DP pattern. The sentinel values `INT_MAX` and `INT_MIN` in the base case are crucial for correctly handling null children.
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

class Solution {
public:
    /**
     * @brief Global variable to track the maximum size of a valid BST found so far.
     */
    int maxSize = 0;

    /**
     * @brief Struct to hold the required information from a subtree.
     */
    struct Info {
        bool isBST;
        int size;   // Size (node count) of the BST subtree
        int minVal; // Minimum value in the subtree
        int maxVal; // Maximum value in the subtree
    };

    /**
     * @brief Recursive DFS (Post-order) to validate BST and calculate size.
     */
    Info dfs(TreeNode* root) {
        // Base Case: Empty node is a valid BST of size 0.
        // INT_MAX (min) and INT_MIN (max) ensure the parent's BST checks pass correctly.
        if (!root) return {true, 0, INT_MAX, INT_MIN};

        // Post-order traversal: Recurse on children first
        Info left = dfs(root->left);
        Info right = dfs(root->right);

        // Check if the current subtree is a valid BST
        if (left.isBST && right.isBST &&                  // 1. Children must be BSTs
            root->val > left.maxVal &&                    // 2. Root must be > Max of left subtree
            root->val < right.minVal) {                   // 3. Root must be < Min of right subtree
            
            // If valid: Calculate size and update global max
            int currSize = left.size + right.size + 1;
            maxSize = max(maxSize, currSize);
            
            // Return valid Info: New min/max are determined by the current root or children's min/max
            return {true, currSize, min(root->val, left.minVal),
                             max(root->val, right.maxVal)};
        }

        // If invalid: Set isBST to false. Return large/small sentinel values 
        // to prevent parent from forming a BST, and size 0.
        return {false, 0, INT_MIN, INT_MAX};
    }

    /**
     * @brief Main function to find the size of the largest BST.
     * @param root The root of the binary tree.
     * @return The maximum size found.
     */
    int largestBst(TreeNode* root) {
        maxSize = 0; // Reset
        dfs(root);
        return maxSize;
    }

};

// --- Test Helper Functions ---

TreeNode* createTestTree1() {
    // Tree Structure where the largest BST is a proper subtree (size 3)
    //         60
    //       /    \
    //      65     70  <-- Valid BST of size 3 (65, 70, 80)
    //     /      /  \
    //    50     65  80
    // Root 60 fails BST property: 60 < 65 (max of left is 65).
    
    TreeNode* n50 = new TreeNode(50);
    TreeNode* n65_l = new TreeNode(65, n50, nullptr); // Left subtree max 65
    
    TreeNode* n65_r = new TreeNode(65);
    TreeNode* n80 = new TreeNode(80);
    TreeNode* n70 = new TreeNode(70, n65_r, n80); // Right subtree is BST of size 3 (min 65, max 80)
    
    TreeNode* root = new TreeNode(60, n65_l, n70); // Root fails: 60 < 65
    
    return root; 
}

TreeNode* createTestTree2() {
    // Tree: Whole tree is a BST. Size 3.
    //          10
    //         /  \
    //        1    20
    
    TreeNode* n1 = new TreeNode(1);
    TreeNode* n20 = new TreeNode(20);
    TreeNode* root = new TreeNode(10, n1, n20); 
    return root;
}

TreeNode* createTestTree3() {
    // Tree: Max size is 1 (no subtree of size > 1 is a BST)
    //          10
    //         /  \
    //        20   5
    //       / \
    //      1  30 
    
    TreeNode* n1 = new TreeNode(1);
    TreeNode* n30 = new TreeNode(30);
    TreeNode* n5 = new TreeNode(5);
    TreeNode* n20 = new TreeNode(20, n1, n30); 
    TreeNode* root = new TreeNode(10, n20, n5); 
    
    // Subtree at 20 fails (30 is greater than 20 but on the right, which is fine, 
    // but the final check: 1 < 20 < 30 passes. Size 3.)
    // Wait, the rule is max(left) < root->val < min(right).
    // Subtree at 20: Left max is 1. Right min is 30. 20 < 30. Passes. Size 3.
    // Whole tree at 10: Left max is 30. Right min is 5. 10 < 30 (fails).
    // Max BSTs: {20, 1, 30} size 3, {5} size 1. Max size 3. Let's create a clear size 1 example.
    
    // Clear size 1 example:
    //          50
    //         /  \
    //        60   40
    
    TreeNode* n60 = new TreeNode(60);
    TreeNode* n40 = new TreeNode(40);
    TreeNode* root_fail = new TreeNode(50, n60, n40); // 50 < 60 fails, 50 > 40 passes. Fails at root.
    return root_fail;
}


int main() {
    Solution sol;
    
    cout << "--- Largest BST in Binary Tree Test Cases ---" << endl;
    
    // Test Case 1: Max Size is 3 (subtree rooted at 70)
    TreeNode* root1 = createTestTree1();
    int res1 = sol.largestBst(root1);
    cout << "Test 1 (Subtree Max): Result = " << res1 << " (Expected: 3)" << endl; 

    // Test Case 2: Max Size is 3 (whole tree is a BST)
    TreeNode* root2 = createTestTree2();
    int res2 = sol.largestBst(root2);
    cout << "Test 2 (Full Tree Max): Result = " << res2 << " (Expected: 3)" << endl;

    // Test Case 3: Max Size is 1 (only single nodes are valid BSTs)
    TreeNode* root3 = createTestTree3();
    int res3 = sol.largestBst(root3);
    cout << "Test 3 (Max size 1): Result = " << res3 << " (Expected: 1)" << endl;

    // Note: Memory deallocation omitted for brevity in simple test harness.

    return 0;
}
