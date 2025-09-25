/*
 * File: Binary_Tree_Postorder_Traversal.cpp
 * Date: 2025-09-25 18:36
 *
 * Problem: Binary Tree Postorder Traversal
 * Link: https://leetcode.com/problems/binary-tree-postorder-traversal/description/
 *
 * Problem Statement:
 * Given the root of a binary tree, return the postorder traversal of its
 * nodes' values.
 *
 *
 * -----------------------------------------------------------------------------------
 * ❌ Brute Force
 * - Idea: The problem itself is a classic traversal, so a brute-force approach
 * is not applicable. The most straightforward way to solve this is to
 * follow the definition of postorder traversal.
 * - Time complexity: N/A
 * - Space complexity: N/A
 * - Limitations: N/A
 *
 *
 * -----------------------------------------------------------------------------------
 * ✅ Optimized Approach: Recursive Traversal
 * - Idea: The definition of postorder traversal is "Left -> Right -> Root".
 * This structure is naturally recursive. We can recursively traverse the left
 * child, then the right child, and finally visit the current node.
 * - Approach: We'll use a helper function to perform the recursive traversal.
 * This helper function will take the current node and a reference to our
 * result vector.
 * - Algorithm:
 * 1. Create an empty vector `post` to store the result.
 * 2. Define a recursive helper function `PostOrder(node, result_vector)`:
 * a. Base case: If `node` is `nullptr`, return.
 * b. Recurse on the left subtree: Call `PostOrder(node->left, result_vector)`.
 * c. Recurse on the right subtree: Call `PostOrder(node->right, result_vector)`.
 * d. Visit the current node: Add `node->val` to `result_vector`.
 * 3. Call the helper function with the root of the tree and the result vector.
 * 4. Return the result vector.
 * - Time complexity: O(N) where N is the number of nodes in the tree. We visit
 * each node exactly once.
 * - Space complexity: O(H) where H is the height of the tree. This is for the
 * call stack of the recursive function. In the worst case (a skewed tree),
 * H can be N, so the space complexity can be O(N). In the best case
 * (a balanced tree), H is log(N), so the space complexity is O(logN).
 *
 *
 * -----------------------------------------------------------------------------------
 * 💡 Key Pattern: Tree Traversal
 * - The problem is a standard tree traversal. Recursive solutions are often the
 * most intuitive for these problems due to the inherent recursive nature of
 * trees. The three main traversals (preorder, inorder, postorder) all follow
 * the same recursive pattern with just the order of operations changed.
 *
 *
 * -----------------------------------------------------------------------------------
 * ℹ️ Keywords: Binary Tree, Postorder Traversal, Recursion, DFS (Depth-First Search)
 *
 *
 * -----------------------------------------------------------------------------------
 * 🗒️ Notes
 * - (What did I learn?) The recursive approach is elegant and concise. I also
 * recall that an iterative solution using a stack is also possible, but it's
 * a bit more complex than the iterative approaches for preorder and inorder
 * traversal. The iterative approach for postorder usually involves two stacks.
 * - (Similar problems?) Preorder Traversal, Inorder Traversal, Level Order
 * Traversal.
 * - (Mistakes I made?) Initially, I might forget the base case of the recursion
 * (when the node is nullptr), leading to infinite loops or crashes. It's
 * crucial to handle the null pointer case.
 *
 *
 * -----------------------------------------------------------------------------------
 */

#include <bits/stdc++.h>
using namespace std;

/**
 * @brief Represents a node in a binary tree.
 * @details This class provides a structure to store a value and pointers to
 * left and right child nodes, which are fundamental to building
 * and traversing binary trees.
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
     * @brief Performs a postorder traversal of a binary tree.
     * @param root The root of the binary tree.
     * @return A vector containing the nodes' values in postorder.
     */
    vector<int> postorderTraversal(TreeNode *root)
    {
        // This is the main function that the user will call.
        vector<int> Post; // Create a vector to store the result.
        // Call the recursive helper function to fill the vector.
        PostOrder(root, Post);
        // Return the final vector.
        return Post;
    }

private:
    /**
     * @brief A recursive helper function to perform postorder traversal.
     * @param root The current node in the traversal.
     * @param Post A reference to the vector storing the traversal result.
     */
    void PostOrder(TreeNode *root, vector<int> &Post)
    {
        // Base case: if the current node is null, stop the recursion.
        if (root == nullptr)
            return;

        // Postorder traversal logic:
        // 1. Recurse on the left subtree.
        PostOrder(root->left, Post);

        // 2. Recurse on the right subtree.
        PostOrder(root->right, Post);

        // 3. Visit the current node.
        Post.push_back(root->val);
    }
};

int main()
{
    // This is the main function for testing the solution.
    Solution sol;

    // Example 1:
    // Tree: 1 -> 2 (left) and 3 (right). 2 has 4 (left) and 5 (right).
    // Postorder traversal: 4 -> 5 -> 2 -> 3 -> 1
    TreeNode *root1 = new TreeNode(1);
    root1->left = new TreeNode(2);
    root1->right = new TreeNode(3);
    root1->left->left = new TreeNode(4);
    root1->left->right = new TreeNode(5);

    vector<int> result1 = sol.postorderTraversal(root1);
    cout << "Example 1 Postorder Traversal: ";
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
    cout << "Example 2 Postorder Traversal (empty tree): ";
    if (result2.empty())
    {
        cout << "[]";
    }
    cout << endl; // Expected output: []

    return 0;
}