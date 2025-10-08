/*
File: Inorder_Successor-Predecessor_in_BST.cpp
Date: 2025-10-09 02:46

Problem: Inorder Successor/Predecessor in BST
Link: https://www.geeksforgeeks.org/problems/predecessor-and-successor/1

Problem Statement:
Given a Binary Search Tree (BST) and a key value, find the Inorder Predecessor
and Inorder Successor of the key. Note that the key might or might not be present
in the BST.

-------------------------------------------------
❌ Brute Force
- Idea: Perform a full Inorder Traversal of the BST and store all node values in a
  sorted array/list. Then, linearly search this list for the key. The element
  before the key is the predecessor, and the element after is the successor.
- Time complexity: O(N) for traversal + O(N) for linear search = O(N).
- Space complexity: O(N) to store the inorder sequence.
- Limitations: Performs an unnecessary full traversal and uses linear space,
  failing to leverage the inherent sorted structure of the BST.

✅ Optimized Approachs
- Idea: Exploit the **BST property** by simultaneously searching for the key and
  tracking the best candidate for the predecessor (the largest value less than
  the key) and successor (the smallest value greater than the key).
- Approach: Single-Pass Iterative Traversal
- Algorithm:
    1. Initialize `predecessor = nullptr` and `successor = nullptr`.
    2. Traverse the tree iteratively starting from the `root`.
    3. If `curr->val == key`:
        - **Predecessor:** If `curr->left` exists, the predecessor is the rightmost
          node in the left subtree.
        - **Successor:** If `curr->right` exists, the successor is the leftmost
          node in the right subtree. Break the loop.
    4. If `curr->val > key`:
        - The current node is a possible successor, update `successor = curr`.
        - Move left: `curr = curr->left`.
    5. If `curr->val < key`:
        - The current node is a possible predecessor, update `predecessor = curr`.
        - Move right: `curr = curr->right`.
- Time complexity: O(H). We only traverse down one branch, where H is the height
  of the BST. This is O($\log N$) for a balanced BST.
- Space complexity: O(1) (Iterative approach) as no extra space is used beyond
  pointers.

💡 Key Pattern:
- **Simultaneous Tracking:** Using the main search traversal to constantly update
  the best candidate nodes for both predecessor and successor, eliminating the
  need for a second traversal or stack/array storage.

ℹ️ Keywords:
- Binary Search Tree, BST, Inorder Tracessor, Inorder Successor, Iterative, O(H), O(log N)

🗒️ Notes
- (What did I learn? Similar problems? Mistakes I made?)
- This single-pass iterative approach handles two cases simultaneously: finding pre/suc
  when the key node *is* present, and finding pre/suc when the key node is *not* present.
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
     * @brief Finds the Inorder Predecessor and Successor for a given key in a BST.
     * @param root The root of the BST.
     * @param key The value for which predecessor and successor are sought.
     * @return A vector containing {predecessor_node, successor_node}. Nullptr if none exists.
     */
    vector<TreeNode *> findPreSuc(TreeNode *root, int key)
    {
        TreeNode *pre = nullptr;
        TreeNode *succ = nullptr;
        TreeNode *curr = root;

        // Phase 1: Search for the key and update global pre/succ candidates.
        while (curr)
        {
            if (curr->val == key)
            {
                // Case 1: Key node found.

                // Predecessor is the rightmost node in the left subtree (if it exists).
                if (curr->left)
                {
                    TreeNode *temp = curr->left;
                    while (temp->right)
                        temp = temp->right;
                    pre = temp;
                }

                // Successor is the leftmost node in the right subtree (if it exists).
                if (curr->right)
                {
                    TreeNode *temp = curr->right;
                    while (temp->left)
                        temp = temp->left;
                    succ = temp;
                }

                // We found the node and its immediate neighbors, so we can stop.
                break;
            }
            else if (curr->val > key)
            {
                // Current node is greater than key, so it's a potential successor.
                succ = curr;
                curr = curr->left;
            }
            else
            { // curr->val < key
                // Current node is less than key, so it's a potential predecessor.
                pre = curr;
                curr = curr->right;
            }
        }

        return {pre, succ};
    }
};

// Helper function to create a test BST (same as in LCA BST)
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

    // Lambda to safely print the result
    auto printResult = [](const vector<TreeNode *> &res, int key)
    {
        string pre_val = res[0] ? to_string(res[0]->val) : "NULL";
        string suc_val = res[1] ? to_string(res[1]->val) : "NULL";
        cout << "Key " << key << ": Predecessor=" << pre_val << ", Successor=" << suc_val << endl;
    };

    cout << "--- Testing Inorder Successor/Predecessor in BST ---" << endl;

    // Test 1: Key exists, internal node (4). Expected: Pre=3, Suc=5
    vector<TreeNode *> res1 = sol.findPreSuc(root, 4);
    cout << "Test 1 (Key 4, Internal): ";
    printResult(res1, 4);

    // Test 2: Key exists, has only one child (8). Expected: Pre=7, Suc=9
    vector<TreeNode *> res2 = sol.findPreSuc(root, 8);
    cout << "Test 2 (Key 8, One Child): ";
    printResult(res2, 8);

    // Test 3: Key exists, leaf node (9). Expected: Pre=8, Suc=NULL
    vector<TreeNode *> res3 = sol.findPreSuc(root, 9);
    cout << "Test 3 (Key 9, Leaf Max): ";
    printResult(res3, 9);

    // Test 4: Key does NOT exist (1). Expected: Pre=0, Suc=2
    vector<TreeNode *> res4 = sol.findPreSuc(root, 1);
    cout << "Test 4 (Key 1, Missing): ";
    printResult(res4, 1);

    // Test 5: Key does NOT exist (10). Expected: Pre=9, Suc=NULL
    vector<TreeNode *> res5 = sol.findPreSuc(root, 10);
    cout << "Test 5 (Key 10, Missing Max): ";
    printResult(res5, 10);

    // Test 6: Key does NOT exist (-1). Expected: Pre=NULL, Suc=0
    vector<TreeNode *> res6 = sol.findPreSuc(root, -1);
    cout << "Test 6 (Key -1, Missing Min): ";
    printResult(res6, -1);

    // Note: Memory deallocation omitted for brevity in simple test harness.

    return 0;
}
