/*
File: Flatten_Binary_Tree_to_Linked_List.cpp
Date: 2025-09-27 16:16

Problem: Flatten Binary Tree to Linked List
Link: https://leetcode.com/problems/flatten-binary-tree-to-linked-list/description/

Problem Statement:
Given the root of a binary tree, flatten it into a "linked list" in-place.
The "linked list" should use the same $\text{TreeNode}$ class where the $\text{right}$
child pointer points to the next node in the list, and the $\text{left}$ child
pointer is always $\text{nullptr}$. The list should follow the tree's **pre-order**
traversal sequence.

-------------------------------------------------
❌ Brute Force
- Idea: Perform a pre-order traversal and store all node pointers in a list.
  Then, iterate through the list to rewire the nodes.
- Time complexity: O(N) for traversal + O(N) for rewiring = O(N).
- Space complexity: O(N) to store the list of pointers.
- Limitations: Uses O(N) auxiliary space, violating the in-place requirement
  for optimization.

✅ Optimized Approachs
- Idea: Rewire the tree structure during traversal to achieve O(1) space,
  or use O(H) recursion stack space.
- Approach: Post-order DFS (Reverse Pre-order) or Iterative Pre-order with Stack.
- Algorithm:
    - **Recursive (Post-order, O(H) space):**
        1. Recursively flatten the $\text{left}$ subtree and the $\text{right}$ subtree.
        2. Store the original $\text{right}$ subtree as $\text{temp}$.
        3. Move the flattened $\text{left}$ subtree to the current $\text{root->right}$.
        4. Set $\text{root->left}$ to $\text{nullptr}$.
        5. Attach the original $\text{right}$ subtree ($\text{temp}$) to the end of the
           new $\text{root->right}$ (the former left subtree).
    - **Iterative (Pre-order with Stack, O(H) space):**
        1. Use a stack to mimic pre-order traversal (push right, then left).
        2. Maintain a $\text{prev}$ pointer to track the last node processed.
        3. For each node popped from the stack: set $\text{prev->right = node}$ and
           $\text{prev->left = nullptr}$. Update $\text{prev}$ to $\text{node}$.
- Time complexity: O(N), as every node is visited and modified once.
- Space complexity: O(H) for recursion stack or O(H) for the stack (worst case O(N)).

💡 Key Pattern:
- **Tree Rearrangement In-Place:** Modifying the tree structure while traversing.
- **Pre-order Sequence:** The order of the final linked list is always pre-order.
- **Temporary Pointers:** Critical for storing the right subtree while the left
  subtree is being inserted.

ℹ️ Keywords:
- Binary Tree, Flatten, Linked List, In-place, Pre-order, DFS, Stack

🗒️ Notes
- (What did I learn? Similar problems? Mistakes I made?)
- The recursive solution provided in the code is the common post-order strategy.
  It's simpler to implement but uses recursion stack space.
- The iterative solution (using a stack for pre-order) is also common but requires
  careful handling of the $\text{prev}$ pointer.
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
private:
    // Helper pointer for the reverse post-order solution (Morris Traversal variant)
    TreeNode *prev = nullptr;

public:
    /**
     * @brief Flattens a binary tree into a linked list using Reverse Post-order
     * (Recursive) traversal.
     * @details This is the most common and conceptually clean recursive solution.
     * @param root The root node of the binary tree (passed by value, modified in-place).
     */
    void flattenRec(TreeNode *root)
    {
        if (!root)
            return;

        // 1. Flatten the right subtree first (reverse pre-order logic).
        flattenRec(root->right);
        // 2. Flatten the left subtree.
        flattenRec(root->left);

        // 3. Rewire: Move the current node's left child to its right.
        TreeNode *leftSubtree = root->left;
        TreeNode *rightSubtree = root->right;

        // Connect the flattened left subtree to the right pointer.
        root->right = leftSubtree;
        // The left pointer must be null.
        root->left = nullptr;

        // 4. Attach the original flattened right subtree to the end of the
        //    new right side (which was the left subtree).
        if (root->right)
        {
            // Find the tail of the new right list (the old left list).
            TreeNode *curr = root->right;
            while (curr->right)
            {
                curr = curr->right;
            }
            // Attach the old right subtree to the tail.
            curr->right = rightSubtree;
        }
        else
        {
            // If the left subtree was null, attach the right subtree directly.
            root->right = rightSubtree;
        }
    }

    /**
     * @brief Flattens a binary tree into a linked list using Iterative Pre-order
     * traversal with a stack.
     * @details This is typically used for interview purposes to show an O(H) space
     * non-recursive solution.
     * @param root The root node of the binary tree (modified in-place).
     */
    void flattenItr(TreeNode *root)
    {
        if (!root)
            return;

        // Stack to simulate pre-order traversal: push right, then left.
        stack<TreeNode *> st;
        st.push(root);

        while (!st.empty())
        {
            TreeNode *node = st.top();
            st.pop();

            // Push right child first, so it is processed later.
            if (node->right)
                st.push(node->right);
            // Push left child second, so it is processed immediately after the node.
            if (node->left)
                st.push(node->left);

            // If there is a next node in the pre-order sequence, rewire the current node.
            if (!st.empty())
            {
                // The next node in the stack top is the next node in the list.
                node->right = st.top();
            }
            else
            {
                // If stack is empty, this is the last node, so set right to nullptr.
                node->right = nullptr;
            }
            // The left pointer must always be null.
            node->left = nullptr;
        }
    }

    /**
     * @brief Public function to flatten the tree.
     * @param root The root node of the binary tree (modified in-place).
     */
    void flatten(TreeNode *root)
    {
        // We will use the Iterative approach for efficiency.
        flattenItr(root);
    }
};

// Helper function to print the flattened linked list structure.
void printFlattened(TreeNode *root)
{
    TreeNode *curr = root;
    while (curr)
    {
        cout << curr->val;
        if (curr->right)
        {
            cout << " -> ";
        }
        // Ensure left is null for verification.
        if (curr->left)
        {
            cout << " (ERROR: left is not null) ";
            break;
        }
        curr = curr->right;
    }
    cout << endl;
}

int main()
{
    Solution sol;

    // Test Case 1: Standard Tree (Expected: 1 -> 2 -> 3 -> 4 -> 5 -> 6)
    //        1
    //       / \
    //      2   5
    //     / \   \
    //    3  4    6
    TreeNode *root1 = new TreeNode(1,
                                   new TreeNode(2, new TreeNode(3), new TreeNode(4)),
                                   new TreeNode(5, nullptr, new TreeNode(6)));

    cout << "Test Case 1 (Iterative Flatten):" << endl;
    sol.flatten(root1);
    printFlattened(root1);

    // Test Case 2: Left-skewed Tree (Expected: 1 -> 2 -> 3)
    //      1
    //     /
    //    2
    //   /
    //  3
    TreeNode *root2 = new TreeNode(1, new TreeNode(2, new TreeNode(3), nullptr), nullptr);

    cout << "\nTest Case 2 (Recursive Flatten):" << endl;
    sol.flattenRec(root2);
    printFlattened(root2);

    // Test Case 3: Right-skewed Tree (Expected: 1 -> 2 -> 3)
    // 1 -> 2 -> 3 (Already a list)
    TreeNode *root3 = new TreeNode(1, nullptr, new TreeNode(2, nullptr, new TreeNode(3)));

    cout << "\nTest Case 3 (Recursive Flatten - Already Flat):" << endl;
    sol.flattenRec(root3);
    printFlattened(root3);

    // Clean up memory (simple example cleanup).
    // Note: Manual cleanup for flattened list is complex, ideally use smart pointers.
    // We rely on the program exiting for this simple test harness.

    return 0;
}
