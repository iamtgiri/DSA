/*
 * File: Iterative_Inorder_Traversal_of_Binary_Tree.cpp
 * Date: 2025-09-25 19:22
 *
 * Problem: Iterative Inorder Traversal of Binary Tree
 * Link: https://leetcode.com/problems/binary-tree-inorder-traversal/
 *
 * Problem Statement:
 * Given the root of a binary tree, return the inorder traversal of its
 * nodes' values. Implement this iteratively.
 *
 *
 * -----------------------------------------------------------------------------------
 * ❌ Brute Force
 * - Idea: The problem is a classic traversal. A recursive solution is the
 * most straightforward approach. It directly follows the "Left -> Root ->
 * Right" pattern.
 * - Time complexity: O(N) where N is the number of nodes.
 * - Space complexity: O(H) where H is the height of the tree, for the function
 * call stack. In a skewed tree, this can be O(N).
 * - Limitations: A recursive solution can lead to a stack overflow error for
 * very deep trees.
 *
 *
 * -----------------------------------------------------------------------------------
 * ✅ Optimized Approach: Iterative Traversal with a Stack
 * - Idea: We can simulate the recursion using an explicit stack to keep track
 * of the nodes to be visited. The inorder traversal requires us to process
 * a node after its entire left subtree has been visited.
 * - Approach: We'll use a `curr` pointer to navigate the tree and a stack to
 * store the nodes on the path from the root to the current node. We'll
 * continuously move left, pushing nodes onto the stack, until we reach a
 * leaf's null left child. Then, we pop from the stack, process the node, and
 * move to its right child.
 * - Algorithm:
 * 1. Create an empty vector `result` and an empty stack `st`.
 * 2. Initialize a pointer `curr` to the `root`.
 * 3. Begin a `while` loop that continues as long as `curr` is not null or
 * the stack is not empty.
 * a. Inside this loop, create another `while` loop that runs as long as
 * `curr` is not null. In this inner loop, we push `curr` onto the stack
 * and move `curr` to its left child (`curr = curr->left`). This pushes
 * all left-path ancestors onto the stack.
 * b. After the inner loop, we have reached the leftmost node of a subtree.
 * Pop the top node from the stack, set it as the new `curr`, and add
 * its value to `result`. This is the "Root" step of the inorder traversal.
 * c. Finally, move `curr` to its right child (`curr = curr->right`). The
 * outer loop will then continue, either descending the new right subtree's
 * left path or processing another node from the stack.
 * 4. Return the `result` vector.
 * - Time complexity: O(N), as each node is visited and processed once.
 * - Space complexity: O(H) where H is the height of the tree, for the stack.
 * In the worst case (a skewed tree), the space complexity can be O(N).
 *
 *
 * -----------------------------------------------------------------------------------
 * 💡 Key Pattern: Iterative Inorder Traversal
 * - This pattern is a standard iterative implementation of DFS. It's unique
 * because of the two-step process: first, traverse down the left subtree,
 * saving nodes on the stack; second, process a node and then traverse its
 * right subtree.
 *
 *
 * -----------------------------------------------------------------------------------
 * ℹ️ Keywords: Binary Tree, Inorder Traversal, Iterative, Stack, DFS
 *
 *
 * -----------------------------------------------------------------------------------
 * 🗒️ Notes
 * - (What did I learn?) This approach provides a non-recursive way to perform
 * inorder traversal, which is essential for handling large, deep trees that
 * might cause stack overflow in recursive solutions. The dual-condition
 * `while (curr != nullptr || !st.empty())` is key to ensuring the traversal
 * completes.
 * - (Similar problems?) Iterative Preorder Traversal, Iterative Postorder
 * Traversal. All three share the stack-based iterative DFS pattern but differ
 * in their exact logic for pushing, popping, and processing nodes.
 * - (Mistakes I made?) Forgetting to handle the right subtree after processing
 * a node is a common error. The line `curr = curr->right;` is what allows
 * the traversal to continue beyond the left-most path.
 *
 *
 * -----------------------------------------------------------------------------------
 */

#include <bits/stdc++.h>
using namespace std;

/**
 * @class TreeNode
 * @brief Represents a single node in a binary tree.
 * @details This class provides a structure to store a value and pointers to
 * left and right child nodes, which are fundamental to building and
 * traversing binary trees.
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
     * @brief Performs an iterative inorder traversal of a binary tree.
     * @param root The root of the binary tree.
     * @return A vector containing the nodes' values in inorder.
     */
    vector<int> inorderTraversal(TreeNode *root)
    {
        // This vector will store the final result.
        vector<int> result;
        // The stack will be used to simulate the recursion.
        stack<TreeNode *> st;
        // A pointer to navigate the tree.
        TreeNode *curr = root;

        // Continue the traversal as long as we have nodes to visit or
        // nodes on the stack to backtrack to.
        while (curr != nullptr || !st.empty())
        {
            // Step 1: Descend to the leftmost node of the current subtree,
            // pushing all ancestors onto the stack.
            while (curr != nullptr)
            {
                st.push(curr);
                curr = curr->left;
            }

            // Step 2: After reaching the leftmost node (curr is now nullptr),
            // backtrack by popping from the stack.
            curr = st.top();
            st.pop();
            // Process the popped node by adding its value to the result.
            result.push_back(curr->val);

            // Step 3: Move to the right child to begin the process on the
            // right subtree.
            curr = curr->right;
        }

        // Return the final result vector.
        return result;
    }
};

int main()
{
    // This is the main function for testing the solution.
    Solution sol;

    // Example 1:
    // Tree: 1 -> 2 (left) and 3 (right). 2 has 4 (left) and 5 (right).
    // Inorder: 4 -> 2 -> 5 -> 1 -> 3
    TreeNode *root1 = new TreeNode(1);
    root1->left = new TreeNode(2);
    root1->right = new TreeNode(3);
    root1->left->left = new TreeNode(4);
    root1->left->right = new TreeNode(5);

    vector<int> result1 = sol.inorderTraversal(root1);
    cout << "Example 1 Iterative Inorder Traversal: ";
    for (int val : result1)
    {
        cout << val << " ";
    }
    cout << endl; // Expected output: 4 2 5 1 3

    // Clean up memory
    delete root1->left->left;
    delete root1->left->right;
    delete root1->left;
    delete root1->right;
    delete root1;

    // Example 2: Empty tree
    TreeNode *root2 = nullptr;
    vector<int> result2 = sol.inorderTraversal(root2);
    cout << "Example 2 Iterative Inorder Traversal (empty tree): ";
    if (result2.empty())
    {
        cout << "[]";
    }
    cout << endl; // Expected output: []

    return 0;
}