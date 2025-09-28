/*
File: Invert_Binary_Tree.cpp
Date: 2025-09-27 15:13

Problem: Invert Binary Tree
Link: https://leetcode.com/problems/invert-binary-tree/description/

Problem Statement:
Given the root of a binary tree, invert the tree, and return its root.
Inverting means swapping the left and right children for every single node.

-------------------------------------------------
❌ Brute Force
- Idea: The only way to invert the entire tree is to visit every node
  and swap its children. This is inherently optimal.
- Time complexity: O(N), where N is the number of nodes.
- Space complexity: O(H) (recursion stack).
- Limitations: None, serves as the optimal approach baseline.

✅ Optimized Approachs
- Idea: Systematically traverse the tree and perform a swap operation at
  each visited node.
- Approach: Depth-First Search (DFS) via recursion or Breadth-First Search (BFS).
- Algorithm:
    - Recursive (DFS): At the current node, swap $\text{node->left}$ and
      $\text{node->right}$. Then recursively call $\text{invertTree}$ on the
      new left child and the new right child.
    - Iterative (BFS): Use a queue. Dequeue a node, swap its children, and
      enqueue the non-null children.
- Time complexity: O(N), as every node is visited exactly once.
- Space complexity: O(H) for recursion or O(W) for BFS queue (up to O(N)).

💡 Key Pattern:
- Systemic Tree Traversal (DFS/BFS) combined with an action (swapping).
- The action must be performed *before* or *after* recursive calls, but the
  swap must happen at the current node.

ℹ️ Keywords:
- Binary Tree, Invert, Mirror, Swap, DFS, BFS, Recursion

🗒️ Notes
- (What did I learn? Similar problems? Mistakes I made?)
- All traversal methods (pre-order, post-order, BFS) work, as long as the
  swap is performed at the node before its children are processed.
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
     * @brief Inverts a binary tree using recursion (Depth-First Search).
     * @details This is a pre-order traversal approach.
     * @param root The root node of the binary tree.
     * @return The root of the inverted tree.
     */
    TreeNode *invertTreeRec(TreeNode *root)
    {
        // Base case: If the current node is null, return null.
        if (root == nullptr)
        {
            return nullptr;
        }

        // Action: Swap the left and right children of the current node.
        swap(root->left, root->right);

        // Recurse: Call invert on the new children (which were the original
        // right and left children, respectively).
        root->left = invertTreeRec(root->left);
        root->right = invertTreeRec(root->right);

        // Return the current node (the root of the inverted subtree).
        return root;
    }

    /**
     * @brief Inverts a binary tree using iteration (Breadth-First Search).
     * @param root The root node of the binary tree.
     * @return The root of the inverted tree.
     */
    TreeNode *invertTreeItr(TreeNode *root)
    {
        // Handle the empty tree case.
        if (root == nullptr)
        {
            return nullptr;
        }

        // Use a queue for BFS and start with the root.
        queue<TreeNode *> q;
        q.push(root);

        // Process nodes level by level.
        while (!q.empty())
        {
            TreeNode *node = q.front();
            q.pop();

            // Action: Swap the children of the current node.
            swap(node->left, node->right);

            // Enqueue the new left child (if it exists).
            if (node->left)
            {
                q.push(node->left);
            }
            // Enqueue the new right child (if it exists).
            if (node->right)
            {
                q.push(node->right);
            }
        }

        // Return the root of the now-inverted tree.
        return root;
    }

    // Main public function defaulting to the recursive approach.
    TreeNode *invertTree(TreeNode *root)
    {
        return invertTreeRec(root);
    }
};

// Helper function to print tree in-order for verification (not part of solution).
void inorder(TreeNode *root)
{
    if (root == nullptr)
        return;
    inorder(root->left);
    cout << root->val << " ";
    inorder(root->right);
}

int main()
{
    Solution sol;

    // Original Tree: [4, 2, 7, 1, 3, 6, 9]
    //      4
    //     / \
    //    2   7
    //   / \ / \
    //  1  3 6  9
    TreeNode *root = new TreeNode(4,
                                  new TreeNode(2, new TreeNode(1), new TreeNode(3)),
                                  new TreeNode(7, new TreeNode(6), new TreeNode(9)));

    cout << "Original In-Order: ";
    inorder(root); // Expected: 1 2 3 4 6 7 9
    cout << endl;

    // Invert the tree using the recursive method.
    TreeNode *invertedRootRec = sol.invertTree(root);

    cout << "Inverted (Rec) In-Order: ";
    inorder(invertedRootRec); // Expected: 9 7 6 4 3 2 1
    cout << endl;

    // Reconstruct the original tree for the iterative test.
    root = new TreeNode(4,
                        new TreeNode(2, new TreeNode(1), new TreeNode(3)),
                        new TreeNode(7, new TreeNode(6), new TreeNode(9)));

    // Invert the tree using the iterative method.
    TreeNode *invertedRootItr = sol.invertTreeItr(root);

    cout << "Inverted (Itr) In-Order: ";
    inorder(invertedRootItr); // Expected: 9 7 6 4 3 2 1
    cout << endl;

    // Note: Proper memory deallocation for complex tests is omitted for brevity.

    return 0;
}
