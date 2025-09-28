/*
File: Identical_Trees.cpp
Date: 2025-09-27 11:50

Problem: Identical Trees
Link: https://leetcode.com/problems/same-tree/description/

Problem Statement:
Given the roots of two binary trees, $\text{p}$ and $\text{q}$, write a function to
check if they are the same or not. Two trees are considered the same if they
are structurally identical and the nodes have the same values.

-------------------------------------------------
❌ Brute Force
- Idea: The only way to ensure both structure and content match is to
  traverse both trees simultaneously and compare nodes. This is optimal.
- Time complexity: O(N), where N is the number of nodes in the smaller tree.
- Space complexity: O(H) (recursion stack).
- Limitations: None, serves as the baseline for the optimal approach.

✅ Optimized Approachs
- Idea: Use synchronized traversal (DFS or BFS) to check corresponding nodes
  at the same time.
- Approach: Depth-First Search (DFS) via recursion is the cleanest.
- Algorithm:
    - Recursive (DFS):
        - If both nodes are $\text{nullptr}$, return true. (Base case 1)
        - If only one node is $\text{nullptr}$ or their values differ, return false.
        - Recurse on $\text{(p->left, q->left)}$ AND $\text{(p->right, q->right)}$.
    - Iterative (BFS):
        - Use a queue to store pairs of nodes $\text{(p, q)}$.
        - In each step, check the null/value conditions for the dequeued pair.
- Time complexity: O(N), where N is the number of nodes in the smaller tree.
- Space complexity: O(H) for recursion (worst case O(N)) or O(W) for BFS.

💡 Key Pattern:
- Simultaneous Tree Traversal (DFS/BFS)
- Early exit on mismatch in structure (null vs non-null) or value.

ℹ️ Keywords:
- Binary Tree, Same Tree, Identical, DFS, BFS, Structure, Value

🗒️ Notes
- (What did I learn? Similar problems? Mistakes I made?)
- The key is handling the three base/stop conditions correctly: both null,
  one null, or values don't match.
- Iterative BFS is useful to avoid deep recursion stacks on skewed trees.
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
     * @brief Checks if two trees are the same using recursion (DFS).
     * @param p The root of the first tree.
     * @param q The root of the second tree.
     * @return True if the trees are structurally identical and have the same values.
     */
    bool isSameTreeRec(TreeNode *p, TreeNode *q)
    {
        // Case 1: Both nodes are null, structures match at this point.
        if (!p && !q)
            return true;

        // Case 2: One node is null OR their values differ. Mismatch found.
        if (!p || !q || p->val != q->val)
            return false;

        // Case 3: Recursively check the left subtrees AND the right subtrees.
        return isSameTreeRec(p->left, q->left) && isSameTreeRec(p->right, q->right);
    }

    /**
     * @brief Checks if two trees are the same using iteration (BFS).
     * @param p The root of the first tree.
     * @param q The root of the second tree.
     * @return True if the trees are structurally identical and have the same values.
     */
    bool isSameTreeItr(TreeNode *p, TreeNode *q)
    {
        // Queue to store pairs of corresponding nodes.
        queue<pair<TreeNode *, TreeNode *>> qPairs;
        qPairs.push({p, q});

        // Continue until all reachable nodes have been checked.
        while (!qPairs.empty())
        {
            TreeNode *node_p = qPairs.front().first;
            TreeNode *node_q = qPairs.front().second;
            qPairs.pop();

            // Check if both are null (Case 1: Match).
            if (!node_p && !node_q)
                continue;

            // Check if one is null or values differ (Case 2: Mismatch).
            if (!node_p || !node_q || node_p->val != node_q->val)
                return false;

            // Enqueue left children.
            qPairs.push({node_p->left, node_q->left});
            // Enqueue right children.
            qPairs.push({node_p->right, node_q->right});
        }

        // If the traversal completes without returning false, they are identical.
        return true;
    }

    // Main public function defaulting to the recursive approach.
    bool isSameTree(TreeNode *p, TreeNode *q)
    {
        return isSameTreeRec(p, q);
    }
};

int main()
{
    Solution sol;

    // Test Case 1: Identical Trees (Expected: True)
    //   p: [1, 2, 3]    q: [1, 2, 3]
    TreeNode *p1 = new TreeNode(1, new TreeNode(2), new TreeNode(3));
    TreeNode *q1 = new TreeNode(1, new TreeNode(2), new TreeNode(3));

    cout << "Test Case 1 (Identical):" << endl;
    cout << "DFS Result: " << (sol.isSameTree(p1, q1) ? "True" : "False") << endl;
    cout << "BFS Result: " << (sol.isSameTreeItr(p1, q1) ? "True" : "False") << endl;
    cout << endl;

    // Test Case 2: Different Structure (Expected: False)
    //   p: [1, 2]      q: [1, null, 2]
    TreeNode *p2 = new TreeNode(1, new TreeNode(2), nullptr);
    TreeNode *q2 = new TreeNode(1, nullptr, new TreeNode(2));

    cout << "Test Case 2 (Structure Mismatch):" << endl;
    cout << "DFS Result: " << (sol.isSameTree(p2, q2) ? "True" : "False") << endl;
    cout << "BFS Result: " << (sol.isSameTreeItr(p2, q2) ? "True" : "False") << endl;
    cout << endl;

    // Test Case 3: Different Values (Expected: False)
    //   p: [1, 2, 1]    q: [1, 1, 2]
    TreeNode *p3 = new TreeNode(1, new TreeNode(2), new TreeNode(1));
    TreeNode *q3 = new TreeNode(1, new TreeNode(1), new TreeNode(2));

    cout << "Test Case 3 (Value Mismatch):" << endl;
    cout << "DFS Result: " << (sol.isSameTree(p3, q3) ? "True" : "False") << endl;
    cout << "BFS Result: " << (sol.isSameTreeItr(p3, q3) ? "True" : "False") << endl;
    cout << endl;

    // Clean up memory (simple example cleanup, real code uses smart pointers).
    delete p1->left;
    delete p1->right;
    delete p1;
    delete q1->left;
    delete q1->right;
    delete q1;

    delete p2->left;
    delete p2;
    delete q2->right;
    delete q2;

    delete p3->left;
    delete p3->right;
    delete p3;
    delete q3->left;
    delete q3->right;
    delete q3;

    return 0;
}
