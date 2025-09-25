/*
 * File: Post-order_Traversal_of_Binary_Tree_using_1_stack.cpp
 * Date: 2025-09-25 19:36
 *
 * Problem: Post-order Traversal of Binary Tree using 1 stack
 * Link: https://leetcode.com/problems/binary-tree-postorder-traversal/
 *
 * Problem Statement:
 * Given the root of a binary tree, return the postorder traversal of its
 * nodes' values. Implement this iteratively using a single stack.
 *
 *
 * -----------------------------------------------------------------------------------
 * ❌ Brute Force
 * - Idea: The simplest approach is recursive postorder traversal, which directly
 * implements the "Left -> Right -> Root" pattern.
 * - Time complexity: O(N), where N is the number of nodes.
 * - Space complexity: O(H), where H is the height of the tree for the recursion
 * call stack. In the worst case, this can be O(N).
 * - Limitations: Recursive solutions may cause a stack overflow error on very
 * deep or skewed trees.
 *
 *
 * -----------------------------------------------------------------------------------
 * ✅ Optimized Approach: Iterative Traversal with a Single Stack
 * - Idea: Postorder traversal requires visiting a parent node after both its
 * left and right subtrees have been fully processed. With a single stack,
 * we need a way to track whether we've already handled a node's children
 * before processing the node itself.
 * - Approach: We'll use a single stack and a `lastVisited` pointer to keep
 * track of the node that was most recently added to the result. This helps
 * us decide whether to descend into a right child or to process the parent
 * node.
 * - Algorithm:
 * 1. Create an empty `result` vector and handle the edge case of a null root.
 * 2. Initialize a stack, a `curr` pointer to `root`, and a `lastVisited`
 * pointer to `nullptr`.
 * 3. Enter a `while` loop that continues as long as `curr` is not null or
 * the stack is not empty.
 * a. First, traverse as far left as possible: `while (curr != nullptr)`,
 * push `curr` onto the stack and move `curr` to `curr->left`. This saves
 * the path for backtracking.
 * b. Once at the leftmost node of a subtree, get a reference to the top
 * node on the stack (`topNode`).
 * c. Check if the right child of `topNode` exists and hasn't been visited.
 * If `topNode->right` is not null AND `topNode->right` is not equal to
 * `lastVisited`, it means we need to process the right subtree. Set `curr`
 * to `topNode->right` to descend into it.
 * d. Otherwise (if the right child is null or has already been visited),
 * we can finally process `topNode`. Pop it from the stack, add its value
 * to `result`, and update `lastVisited` to `topNode`. Set `curr` to
 * `nullptr` to avoid re-entering a loop.
 * 4. Return the `result` vector.
 * - Time complexity: O(N), as each node is visited and processed once.
 * - Space complexity: O(H), where H is the height of the tree, for the stack.
 * In the worst case (a skewed tree), the space is O(N).
 *
 *
 * -----------------------------------------------------------------------------------
 * 💡 Key Pattern: Single-Stack Postorder Traversal
 * - This is a sophisticated and space-efficient iterative DFS pattern. It uses
 * a "peek" operation on the stack combined with a state-tracking variable
 * (`lastVisited`) to correctly identify when a parent node can be processed.
 * It's a key interview problem that demonstrates a deep understanding of
 * iterative algorithms.
 *
 *
 * -----------------------------------------------------------------------------------
 * ℹ️ Keywords: Binary Tree, Postorder Traversal, Iterative, Stack, DFS
 *
 *
 * -----------------------------------------------------------------------------------
 * 🗒️ Notes
 * - (What did I learn?) The single-stack postorder traversal is tricky. The
 * `lastVisited` pointer is essential to prevent infinite loops and ensure
 * that the right child is processed before the parent. The logic is: "If
 * the right child exists and we haven't visited it yet, go right. Otherwise,
 * we're done with the children, so process the current node."
 * - (Similar problems?) Iterative Inorder and Preorder traversals are simpler
 * variations of this iterative DFS pattern.
 * - (Mistakes I made?) Forgetting to correctly handle the `lastVisited` check is
 * a common source of errors. Also, accidentally re-entering a left subtree
 * by not setting `curr = nullptr` is another potential bug.
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
     * @brief Performs an iterative postorder traversal of a binary tree
     * using a single stack.
     * @param root The root of the binary tree.
     * @return A vector containing the nodes' values in postorder.
     */
    vector<int> postorderTraversal(TreeNode *root)
    {
        // This vector will store the final result.
        vector<int> result;
        // Handle the edge case of an empty tree.
        if (!root)
            return result;

        // The stack will be used to keep track of nodes to visit.
        stack<TreeNode *> st;
        // The `curr` pointer navigates the tree.
        TreeNode *curr = root;
        // The `lastVisited` pointer helps us know if we've processed a
        // node's right subtree.
        TreeNode *lastVisited = nullptr;

        // The main loop continues as long as there are nodes to process
        // or a path to backtrack.
        while (!st.empty() || curr != nullptr)
        {
            // First, traverse to the leftmost leaf of the current subtree,
            // pushing all ancestors onto the stack.
            while (curr != nullptr)
            {
                st.push(curr);
                curr = curr->left;
            }

            // Once we are at a leaf (or have processed its left subtree),
            // get a reference to the node on top of the stack.
            TreeNode *topNode = st.top();

            // Check if the right child of the top node exists and
            // hasn't been processed yet.
            if (topNode->right != nullptr && lastVisited != topNode->right)
            {
                // If so, we need to process the right subtree.
                curr = topNode->right;
            }
            else
            {
                // If not, we have finished with both subtrees (or there was
                // no right subtree). We can now process the current node.
                st.pop();
                result.push_back(topNode->val);
                // Mark this node as the last one visited.
                lastVisited = topNode;
                // Set `curr` to `nullptr` to ensure the loop doesn't
                // incorrectly try to go right again and instead
                // continues by processing the next node on the stack.
                curr = nullptr;
            }
        }

        // Return the final postorder traversal.
        return result;
    }
};

int main()
{
    // This is the main function for testing the solution.
    Solution sol;

    // Example 1:
    // Tree: 1 -> 2 (left) and 3 (right). 2 has 4 (left) and 5 (right).
    // Postorder: 4 -> 5 -> 2 -> 3 -> 1
    TreeNode *root1 = new TreeNode(1);
    root1->left = new TreeNode(2);
    root1->right = new TreeNode(3);
    root1->left->left = new TreeNode(4);
    root1->left->right = new TreeNode(5);

    vector<int> result1 = sol.postorderTraversal(root1);
    cout << "Example 1 Iterative Postorder Traversal (Single Stack): ";
    for (int val : result1)
    {
        cout << val << " ";
    }
    cout << endl; // Expected output: 4 5 2 3 1

    // Clean up memory
    delete root1->left->left;
    delete root1->left->right;
    delete root1->left;
    delete root1->right;
    delete root1;

    // Example 2: Empty tree
    TreeNode *root2 = nullptr;
    vector<int> result2 = sol.postorderTraversal(root2);
    cout << "Example 2 Iterative Postorder Traversal (empty tree): ";
    if (result2.empty())
    {
        cout << "[]";
    }
    cout << endl; // Expected output: []

    return 0;
}