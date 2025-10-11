/*
File: Two_Sum_In_BST.cpp
Date: 2025-10-11 21:19

Problem: Two Sum In BST
Link: https://leetcode.com/problems/two-sum-iv-input-is-a-bst/description/

Problem Statement:
Given the root of a Binary Search Tree and an integer k, return true if there
exist two distinct elements in the BST such that their sum equals k.

-------------------------------------------------
❌ Brute Force (Flatten to Array + Two Pointers)
- Idea: Perform an **Inorder Traversal** to flatten the BST into a sorted array. Then, use the standard **Two-Pointer** technique (one from the start, one from the end) to find the target sum.
- Time complexity: O(N). O(N) for traversal and O(N) for the two-pointer search.
- Space complexity: O(N) to store the array, plus O(H) for the recursion stack. Total O(N).
- Limitations: Requires O(N) auxiliary space for the explicit array, which is inefficient compared to the in-place BST structure.

✅ Optimized Approachs (DFS with Hash Set)
- Idea: Traverse the tree using Depth First Search (DFS). For each node with value `x`, check if the required complement, `k - x`, has already been visited and stored in a hash set.
- Approach: DFS combined with an `unordered_set`.
- Algorithm:
    1. Initialize an empty hash set `seen`.
    2. Define a recursive DFS function.
    3. At each node, check if `k - node->val` exists in `seen`. If yes, return `true`.
    4. Insert `node->val` into `seen`.
    5. Recursively call DFS on the left and right children.
- Time complexity: O(N). Every node is visited once, and hash set operations (insertion/lookup) are O(1) on average.
- Space complexity: O(N) to store all node values in the hash set, plus O(H) for the recursion stack. Total O(N).

💡 Key Pattern:
- **Hash Set for Complement:** Applying the classic Two Sum pattern to a tree, where the hash set efficiently tracks visited elements and checks for the required complement.

ℹ️ Keywords:
- Two Sum, Binary Search Tree, BST, Hash Set, DFS, Inorder Traversal

🗒️ Notes
- The optimal solution in terms of auxiliary space is $O(H)$ using two iterators (one forward, one backward) built on top of the BST structure, effectively simulating the two-pointer approach without storing the full array. However, the hash set method is the cleanest $O(N)$ solution.
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
     * @brief Finds if a target sum k exists using Inorder Traversal and Two Pointers (O(N) time, O(N) space).
     * @param root The root of the BST.
     * @param k The target sum.
     * @return True if two nodes sum up to k, false otherwise.
     */
    bool findTargetBruteForce(TreeNode *root, int k)
    {
        vector<int> arr;
        // Step 1: Flatten the tree into a sorted array (Inorder Traversal)
        inorder(root, arr);

        // Step 2: Use Two Pointers
        int left = 0, right = arr.size() - 1;
        while (right > left)
        {
            long long sum = (long long)arr[left] + arr[right];
            if (sum == k)
                return true;
            else if (sum < k)
                ++left;
            else
                --right;
        }
        return false;
    }

    /**
     * @brief Finds if a target sum k exists using DFS and a Hash Set (O(N) time, O(N) space).
     * @param root The root of the BST.
     * @param k The target sum.
     * @return True if two nodes sum up to k, false otherwise.
     */
    bool findTarget(TreeNode *root, int k)
    {
        unordered_set<int> seen;
        return dfs(root, seen, k);
    }

private:
    /**
     * @brief Recursive DFS helper for the hash set approach.
     */
    bool dfs(TreeNode *node, unordered_set<int> &seen, int k)
    {
        if (!node)
            return false;

        // Check if the complement exists
        int complement = k - node->val;
        if (seen.count(complement))
            return true;

        // Record the current node's value
        seen.insert(node->val);

        // Recursively search left and right subtrees
        return dfs(node->left, seen, k) || dfs(node->right, seen, k);
    }

    /**
     * @brief Helper function to perform Inorder Traversal and populate the array.
     */
    void inorder(TreeNode *root, vector<int> &arr)
    {
        if (!root)
            return;
        inorder(root->left, arr);
        arr.push_back(root->val);
        inorder(root->right, arr);
    }
};

// Helper function to create a test BST
TreeNode *createTestBST()
{
    // BST structure:
    //          5
    //        /   \
    //       3     6
    //      / \     \
    //     2   4     7
    // Inorder sequence: 2, 3, 4, 5, 6, 7

    TreeNode *node2 = new TreeNode(2);
    TreeNode *node4 = new TreeNode(4);
    TreeNode *node3 = new TreeNode(3, node2, node4);

    TreeNode *node7 = new TreeNode(7);
    TreeNode *node6 = new TreeNode(6, nullptr, node7);

    TreeNode *root = new TreeNode(5, node3, node6);

    return root;
}

int main()
{
    Solution sol;

    TreeNode *root = createTestBST();

    cout << "--- Two Sum In BST Test Cases (Tree: 2, 3, 4, 5, 6, 7) ---" << endl;

    // Test 1: k=9 (3 + 6 = 9). Expected: true
    int k1 = 9;
    bool res1 = sol.findTarget(root, k1);
    cout << "K=" << k1 << ": " << (res1 ? "True" : "False") << " (Expected: True)" << endl;

    // Test 2: k=10 (3 + 7 = 10 or 4 + 6 = 10). Expected: true
    int k2 = 10;
    bool res2 = sol.findTarget(root, k2);
    cout << "K=" << k2 << ": " << (res2 ? "True" : "False") << " (Expected: True)" << endl;

    // Test 3: k=4 (2 + 2 needed - disallowed/not present). Expected: false
    int k3 = 4;
    bool res3 = sol.findTarget(root, k3);
    cout << "K=" << k3 << ": " << (res3 ? "True" : "False") << " (Expected: False)" << endl;

    // Test 4: k=15 (Max sum is 6+7=13). Expected: false
    int k4 = 15;
    bool res4 = sol.findTarget(root, k4);
    cout << "K=" << k4 << ": " << (res4 ? "True" : "False") << " (Expected: False)" << endl;

    // Test 5: k=7 (3 + 4 = 7). Expected: true
    int k5 = 7;
    bool res5 = sol.findTarget(root, k5);
    cout << "K=" << k5 << ": " << (res5 ? "True" : "False") << " (Expected: True)" << endl;

    // Note: Memory deallocation omitted for brevity in simple test harness.

    return 0;
}
