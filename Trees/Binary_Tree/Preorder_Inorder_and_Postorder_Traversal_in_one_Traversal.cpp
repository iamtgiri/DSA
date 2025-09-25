/*
 * File: Preorder_Inorder_and_Postorder_Traversal_in_one_Traversal.cpp
 * Date: 2025-09-25 19:44
 *
 * Problem: Preorder, Inorder, and Postorder Traversal in one Traversal
 * Link: URL (Not provided, but this is a common interview problem)
 *
 * Problem Statement:
 * Given the root of a binary tree, return the preorder, inorder, and postorder
 * traversals of its nodes' values in a single traversal pass.
 *
 * -----------------------------------------------------------------------------------
 * ❌ Brute Force
 * - Idea: The simplest approach is to perform three separate traversals of the
 * tree: one for preorder, one for inorder, and one for postorder. This
 * can be done using either recursion or a simple iterative method for each.
 * - Time complexity: O(3N) which simplifies to O(N). Each node is visited
 * three times.
 * - Space complexity: O(3H) which simplifies to O(H), where H is the height
 * of the tree, for the recursion call stacks or auxiliary stacks.
 * - Limitations: This method is inefficient as it involves redundant tree
 * traversals, which is not optimal for large trees.
 *
 *
 * -----------------------------------------------------------------------------------
 * ✅ Optimized Approach: Single Iterative Traversal with State Management
 * - Idea: We can combine all three traversals into a single pass by keeping
 * track of a node's "state." Each node will be processed three times: once
 * for its preorder position, once for inorder, and once for postorder. We
 * can use a stack of pairs to store both the node and its current state.
 * - Approach: We will use a stack of `pair<TreeNode*, int>`, where the integer
 * `int` represents the state of the node.
 * - State 1: The node has been visited for the first time (Preorder).
 * - State 2: The node's left subtree has been processed (Inorder).
 * - State 3: Both the node's left and right subtrees have been processed
 * (Postorder).
 * - Algorithm:
 * 1. Initialize three empty vectors: `preorder`, `inorder`, and `postorder`.
 * 2. Handle the edge case: if the root is null, return.
 * 3. Create a stack of `pair<TreeNode*, int>` and push the root with a
 * state of 1: `st.push({root, 1})`.
 * 4. Enter a `while` loop that continues as long as the stack is not empty.
 * a. Get the top pair from the stack and pop it. Let the pair be
 * `{node, state}`.
 * b. If `state == 1`:
 * - This is the first visit. Add `node->val` to the `preorder` vector.
 * - Increment the state to 2 and push the pair back onto the stack.
 * - If a left child exists, push it onto the stack with state 1.
 * c. If `state == 2`:
 * - This is the second visit, after the left subtree. Add `node->val`
 * - to the `inorder` vector.
 * - Increment the state to 3 and push the pair back onto the stack.
 * - If a right child exists, push it onto the stack with state 1.
 * d. If `state == 3`:
 * - This is the third and final visit, after both subtrees. Add
 * - `node->val` to the `postorder` vector. No need to push it back.
 * 5. The loop terminates when the stack is empty. The three vectors now hold
 * the complete traversals.
 * - Time complexity: O(N), as each node is pushed onto and popped from the
 * stack three times, for a total of a constant number of operations per node.
 * - Space complexity: O(H), where H is the height of the tree. This is for the
 * stack, and in the worst-case skewed tree, it can be O(N).
 *
 *
 * -----------------------------------------------------------------------------------
 * 💡 Key Pattern: State-Based Traversal
 * - This is an advanced DFS technique that uses a state variable to simulate
 * different processing stages of a single traversal. It's a powerful and
 * space-efficient way to solve problems that require multiple traversal
 * results.
 *
 *
 * -----------------------------------------------------------------------------------
 * ℹ️ Keywords: Binary Tree, Preorder, Inorder, Postorder, Iterative, Stack,
 * Single Traversal, State Management
 *
 *
 * -----------------------------------------------------------------------------------
 * 🗒️ Notes
 * - (What did I learn?) This technique is an elegant solution to a common
 * problem, showing how a single iterative pass can collect all three traversal
 * types. The use of a `pair` to store state is crucial for this approach.
 * - (Similar problems?) This is a generalization of iterative preorder, inorder,
 * and postorder traversals, highlighting the underlying similarity in their
 * structure.
 * - (Mistakes I made?) Getting the state transitions or the push order for the
 * children wrong can lead to incorrect traversal results. The logic must be
 * followed precisely to maintain the correct order.
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
     * @brief Performs preorder, inorder, and postorder traversals in a single
     * iterative pass using a stack and state management.
     * @param root The root of the binary tree.
     * @param preorder A reference to the vector to store the preorder traversal.
     * @param inorder A reference to the vector to store the inorder traversal.
     * @param postorder A reference to the vector to store the postorder
     * traversal.
     */
    void allTraversals(TreeNode *root, vector<int> &preorder, vector<int> &inorder, vector<int> &postorder)
    {
        // Handle the edge case of an empty tree.
        if (!root)
            return;

        // The stack will hold pairs of {node, state}.
        stack<pair<TreeNode *, int>> st;
        // Start the traversal by pushing the root with state 1.
        st.push({root, 1});

        // The loop continues as long as there are nodes to process.
        while (!st.empty())
        {
            // Get the top pair from the stack and pop it.
            auto &top = st.top();
            TreeNode *node = top.first;
            int state = top.second;
            st.pop();

            // Check the current state of the node.
            if (state == 1)
            {
                // State 1: First visit. This is the preorder position.
                preorder.push_back(node->val);
                // Increment the state for the next visit.
                top.second++;
                st.push(top); // Push back with state 2.
                // Move to the left child, starting with state 1.
                if (node->left)
                    st.push({node->left, 1});
            }
            else if (state == 2)
            {
                // State 2: Second visit, after the left subtree.
                // This is the inorder position.
                inorder.push_back(node->val);
                // Increment the state for the next visit.
                top.second++;
                st.push(top); // Push back with state 3.
                // Move to the right child, starting with state 1.
                if (node->right)
                    st.push({node->right, 1});
            }
            else
            {
                // State 3: Third and final visit, after both subtrees.
                // This is the postorder position.
                postorder.push_back(node->val);
                // No need to push back, as this node is fully processed.
            }
        }
    }
};

int main()
{
    // This is the main function for testing the solution.
    Solution sol;

    // Example 1:
    // Tree: 1 -> 2 (left) and 3 (right). 2 has 4 (left) and 5 (right).
    // Preorder: 1, 2, 4, 5, 3
    // Inorder: 4, 2, 5, 1, 3
    // Postorder: 4, 5, 2, 3, 1
    TreeNode *root1 = new TreeNode(1);
    root1->left = new TreeNode(2);
    root1->right = new TreeNode(3);
    root1->left->left = new TreeNode(4);
    root1->left->right = new TreeNode(5);

    vector<int> preorder, inorder, postorder;
    sol.allTraversals(root1, preorder, inorder, postorder);

    cout << "Preorder Traversal: ";
    for (int val : preorder)
    {
        cout << val << " ";
    }
    cout << endl;

    cout << "Inorder Traversal: ";
    for (int val : inorder)
    {
        cout << val << " ";
    }
    cout << endl;

    cout << "Postorder Traversal: ";
    for (int val : postorder)
    {
        cout << val << " ";
    }
    cout << endl;

    // Clean up memory
    delete root1->left->left;
    delete root1->left->right;
    delete root1->left;
    delete root1->right;
    delete root1;

    return 0;
}