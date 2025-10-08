/*
File: Maximum_width_of_a_Binary_Tree.cpp
Date: 2025-10-09 00:31

Problem: Maximum width of a Binary Tree
Link: https://leetcode.com/problems/maximum-width-of-binary-tree/description/

Problem Statement:
Given the root of a binary tree, return the maximum width of the tree. The width
is the maximum distance between any two non-null nodes in the same level. The
distance between two nodes is the index difference between them (using a 1-based
indexing system where the root is index 1, its left child is 2, and its right
child is 3, and so on, following a complete binary tree structure). The distance
is calculated as (index_of_last_node - index_of_first_node + 1).

-------------------------------------------------
❌ Brute Force
- Idea: Perform a standard Level Order Traversal (BFS). At each level, find the
  first and last non-null node. Count all the nodes and null positions between
  them (inclusive).
- Time complexity: O(N^2) in the worst case (skewed tree). For a complete tree,
  it would be O(N), but tracking positions correctly in a skewed tree without
  indices becomes complex and potentially slow.
- Space complexity: O(N) to store nodes at the widest level in the queue.
- Limitations: Hard to correctly calculate the width (distance) across null gaps
  without an explicit indexing system, leading to inefficient complexity if attempted.

✅ Optimized Approachs
- Idea: Use **Level Order Traversal (BFS)** combined with **Complete Binary Tree Indexing**.
  In a complete binary tree, if a parent is at index i, its left child is 2i+1
  and its right child is 2i+2. This relative distance remains correct even when
  nodes are missing.
- Approach: BFS with Indexed Nodes
- Algorithm:
    1. Initialize `max_width = 0`. Use a queue to store `pair<TreeNode*, unsigned long long>`.
    2. Start BFS with the root at index 0: `q.push({root, 0})`.
    3. For each level:
        a. Store the index of the first node (`first_index = q.front().second`).
        b. Iterate through all nodes on the current level.
        c. For the current node at index i:
            - If left child exists, push it with index 2i+1.
            - If right child exists, push it with index 2i+2.
        d. The index of the last node popped in this loop is `last_index`.
        e. Calculate current width: `width = last_index - first_index + 1`.
        f. Update `max_width = max(max_width, width)`.
- Time complexity: O(N). Every node is processed exactly once.
- Space complexity: O(W) where W is the maximum width of the tree (number of nodes at the widest level). In the worst case, $W \approx N/2$, so O(N).

💡 Key Pattern:
- Level Indexing: Using the mathematical properties of a complete binary tree's
  level-order indexing (2i+1, 2i+2) to measure distance/width in sparse trees.
  Note on Index Overflow: Use `unsigned long long` for indices to prevent overflow,
  as indices can grow very large even for moderately deep trees.

ℹ️ Keywords:
- Binary Tree, BFS, Level Order Traversal, Indexing, Width, Maximum Distance, unsigned long long

🗒️ Notes
- (What did I learn? Similar problems? Mistakes I made?)
- Crucial lesson: When calculating width across null gaps, standard BFS won't work;
  we need the implicit positions. The `unsigned long long` is vital; indices can
  reach $2^{50}$ even for depth 50, which overflows a standard 32-bit integer.
- The small optimization of normalizing the level's start index to 0 (i.e., using
  `index = index - first` before calculating children's indices) is sometimes
  used to prevent huge numbers, but the current solution uses large integers which is also standard.
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
     * @brief Calculates the maximum width of the binary tree using BFS and indexing.
     * @param root The root of the binary tree.
     * @return The maximum width found across all levels.
     */
    int widthOfBinaryTree(TreeNode *root)
    {
        if (!root)
            return 0;

        // Queue stores {node pointer, index}
        queue<pair<TreeNode *, unsigned long long>> q;
        // Start root at index 0.
        q.push({root, 0});
        int maxwidth = 0;

        while (!q.empty())
        {
            int size = q.size();

            // Get the index of the first node in the current level
            unsigned long long first_index = q.front().second;
            unsigned long long last_index = first_index; // Initialize last index with first's index

            // Process all nodes at the current level
            for (int i = 0; i < size; ++i)
            {
                auto [node, index] = q.front();
                q.pop();

                // Update the last index seen on this level
                last_index = index;

                // Index children using the standard complete tree formula:
                // Left: 2*i + 1
                // Right: 2*i + 2
                // Since the indices can become very large, we use unsigned long long.

                // NOTE: A common trick to prevent overflow on very deep trees is to
                // rebase the current index: long long cur_id = index - first_index;
                // and then calculate children's indices as 2*cur_id + 1 and 2*cur_id + 2.
                // We will use the large unsigned long long type to handle standard cases.

                if (node->left)
                    q.push({node->left, 2 * index + 1});
                if (node->right)
                    q.push({node->right, 2 * index + 2});
            }

            // The width of the current level is (last_index - first_index + 1).
            maxwidth = max(maxwidth, (int)(last_index - first_index + 1));
        }

        return maxwidth;
    }
};

// Helper function to create a test tree
TreeNode *createTestTree()
{
    // Tree structure:
    //          1(0)
    //         / \
    //      3(1)  2(2)
    //     / \   / \
    //    5(3)  N N   9(6)
    //   / \
    //  6(7) N
    // Max Width is at Level 3: (9) - (5) + 1 = 6 - 3 + 1 = 4.

    TreeNode *node6 = new TreeNode(6);
    TreeNode *node9 = new TreeNode(9);
    TreeNode *node5 = new TreeNode(5);
    node5->left = node6; // Index 7

    TreeNode *node3 = new TreeNode(3, node5, nullptr); // Index 1
    TreeNode *node2 = new TreeNode(2, nullptr, node9); // Index 2

    TreeNode *root = new TreeNode(1, node3, node2); // Index 0

    return root;
}

int main()
{
    Solution sol;

    TreeNode *root1 = createTestTree();

    // Test 1: Max width 4 (Level 3: nodes 5 and 9, indices 3 and 6)
    int width1 = sol.widthOfBinaryTree(root1);
    cout << "Test 1: Tree with nodes 1,3,2,5,9,6. Max Width: " << width1 << " (Expected: 4)" << endl;

    // Test 2: Simple tree
    //        1(0)
    //       /
    //      2(1)
    // Max Width 1.
    TreeNode *root2 = new TreeNode(1, new TreeNode(2), nullptr);
    int width2 = sol.widthOfBinaryTree(root2);
    cout << "Test 2: Tree with nodes 1, 2. Max Width: " << width2 << " (Expected: 1)" << endl;

    // Test 3: Wider tree
    //         1(0)
    //        /  \
    //       3(1) 2(2)
    //      /
    //     5(3)
    // Max width 2 (Level 2: 3 and 2, indices 1 and 2). Width: 2-1+1 = 2
    TreeNode *root3 = new TreeNode(1, new TreeNode(3, new TreeNode(5), nullptr), new TreeNode(2));
    int width3 = sol.widthOfBinaryTree(root3);
    cout << "Test 3: Tree with nodes 1,3,2,5. Max Width: " << width3 << " (Expected: 2)" << endl;

    // Note: Memory deallocation omitted for brevity in simple test harness.

    return 0;
}
