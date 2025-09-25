/*
 * File: Post-order_Traversal_of_Binary_Tree_using_2_stack.cpp
 * Date: 2025-09-25 19:30
 *
 * Problem: Post-order Traversal of Binary Tree using 2 stack
 * Link: https://leetcode.com/problems/binary-tree-postorder-traversal/
 *
 * Problem Statement:
 * Given the root of a binary tree, return the postorder traversal of its
 * nodes' values. Implement this iteratively using two stacks.
 *
 *
 * -----------------------------------------------------------------------------------
 * ❌ Brute Force
 * - Idea: The simplest approach is recursive postorder traversal, which directly
 * implements the "Left -> Right -> Root" pattern. It is the most intuitive
 * method but can be inefficient for very deep trees.
 * - Time complexity: O(N), where N is the number of nodes.
 * - Space complexity: O(H), where H is the height of the tree for the recursion
 * call stack. In the worst case, this can be O(N).
 * - Limitations: Recursive solutions may cause a stack overflow error on very
 * deep or skewed trees.
 *
 *
 * -----------------------------------------------------------------------------------
 * ✅ Optimized Approach: Iterative Traversal with Two Stacks
 * - Idea: The key insight is that postorder traversal (Left -> Right -> Root) is
 * the reverse of a modified preorder traversal (Root -> Right -> Left). We can
 * use one stack to generate the "Root -> Right -> Left" sequence and a second
 * stack to reverse this order.
 * - Approach: We'll use two stacks. The first stack (`s1`) will be for a
 * a depth-first traversal, and the second stack (`s2`) will collect the
 * nodes in the correct order for the final output.
 * - Algorithm:
 * 1. Create an empty vector `result` and handle the edge case of an empty tree.
 * 2. Initialize two stacks, `s1` and `s2`. Push the `root` onto `s1`.
 * 3. Begin a `while` loop that continues as long as `s1` is not empty.
 * a. Pop the top node (`curr`) from `s1` and immediately push it onto `s2`.
 * b. Push `curr`'s left child, if it exists, onto `s1`.
 * c. Push `curr`'s right child, if it exists, onto `s1`.
 * 4. Once `s1` is empty, all nodes have been processed and are on `s2` in the
 * "Root -> Right -> Left" order.
 * 5. Begin a second `while` loop that continues as long as `s2` is not empty.
 * a. Pop the top node from `s2` and add its value to the `result` vector.
 * 6. Return the `result` vector.
 * - Time complexity: O(N), as each node is pushed onto and popped from both
 * stacks exactly once.
 * - Space complexity: O(N), as both stacks can, in the worst case, hold
 * all the nodes of the tree.
 *
 *
 * -----------------------------------------------------------------------------------
 * 💡 Key Pattern: Two-Stack Iterative Traversal
 * - This pattern is specifically useful for problems where the desired output is
 * the reverse of a traversal that can be easily generated iteratively. The first
 * stack generates the "reversed" order, and the second stack reverses it back
 * to the correct order.
 *
 *
 * -----------------------------------------------------------------------------------
 * ℹ️ Keywords: Binary Tree, Postorder Traversal, Iterative, Stack, DFS
 *
 *
 * -----------------------------------------------------------------------------------
 * 🗒️ Notes
 * - (What did I learn?) This approach elegantly solves a complex problem. The
 * core trick lies in recognizing the relationship between postorder and a
 * modified preorder traversal. The order of pushing children (left then right)
 * ensures that the right child is processed and moved to `s2` before the left,
 * achieving the necessary "Root -> Right -> Left" order on the second stack.
 * - (Similar problems?) Iterative Preorder Traversal (one stack), Iterative
 * Inorder Traversal (one stack). The two-stack method is a less common
 * but powerful technique for specific traversal orders.
 * - (Mistakes I made?) A common mistake is to get the push order wrong on the
 * first stack (`s1`). If you push right before left, you'll get a
 * "Root -> Left -> Right" order, which is not what's needed for this
 * reversal trick.
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
     * @brief Performs an iterative postorder traversal of a binary tree using
     * two stacks.
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

        // s1: Used for the initial traversal.
        // s2: Used to reverse the order and produce the final result.
        stack<TreeNode *> s1, s2;
        // Start the traversal by pushing the root onto the first stack.
        s1.push(root);

        // This loop performs a "Root -> Left -> Right" traversal but pushes
        // nodes onto s2, resulting in a "Root -> Right -> Left" order on s2.
        while (!s1.empty())
        {
            TreeNode *curr = s1.top();
            s1.pop();
            s2.push(curr);

            // Push left child first to ensure right child is processed first
            // on the next iteration.
            if (curr->left)
                s1.push(curr->left);
            if (curr->right)
                s1.push(curr->right);
        }

        // This loop pops nodes from s2, which are now in the correct
        // postorder sequence, and adds them to the result vector.
        while (!s2.empty())
        {
            result.push_back(s2.top()->val);
            s2.pop();
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
    cout << "Example 1 Iterative Postorder Traversal (Two Stacks): ";
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