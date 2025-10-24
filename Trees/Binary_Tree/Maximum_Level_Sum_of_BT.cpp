/*
File: Maximum_Level_Sum_of_BT.cpp
Date: 2025-10-24 22:42

Problem: Maximum Level Sum of a Binary Tree
Link: https://leetcode.com/problems/maximum-level-sum-of-a-binary-tree/description/

Problem Statement:
Given the root of a binary tree, the level of its root is 1, the level of its children is 2, and so on.
Return the smallest level x such that the sum of all the values of nodes at level x is maximal.

-------------------------------------------------
❌ Brute Force
- Idea: Using an arbitrary graph traversal method (like DFS) to collect all node values into a hash map or array, where the index represents the level. This is not strictly "brute force" as all $O(N)$ nodes must be visited, but it is less direct than BFS.
- Time complexity: O(N)
- Space complexity: O(N) for recursion stack or map storage.
- Limitations: Inefficiently manages level-by-level grouping compared to BFS.

✅ Optimized Approachs
- Idea: Use Breadth-First Search (BFS) to naturally process the tree layer by layer, calculating the sum for each level before advancing.
- Approach: Level Order Traversal (BFS).
- Algorithm:
    1. Initialize a queue with the root node.
    2. Initialize `max_sum = INT_MIN`, `max_level = 1`, and `current_level = 1`.
    3. Loop while the queue is not empty:
        a. Get the size of the current level's nodes (`size`).
        b. Calculate the `current_sum` by iterating `size` times: dequeue a node, add its value, and enqueue its children (if they exist).
        c. If `current_sum` is greater than `max_sum`, update `max_sum` to `current_sum` and `max_level` to `current_level`.
        d. Increment `current_level`.
    4. Return `max_level`.
- Time complexity: O(N), where N is the number of nodes (each node is visited and processed exactly once).
- Space complexity: O(W), where W is the maximum width of the tree, which can be up to O(N) in the worst case.

💡 Key Pattern:
- **Level Order Traversal:** Using BFS with queue size checking is the standard pattern for problems requiring level-by-level processing of a tree.

ℹ️ Keywords:
- BFS, Queue, Binary Tree, Level Order Traversal, Max/Min Tracking.

🗒️ Notes
- The problem asks for the *smallest* level index in case of ties. The BFS approach naturally handles this because we only update `max_level` when the new sum is *strictly greater* (`prevsum < currsum`).
-------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

// Definition for a binary tree node.
struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution
{
public:
    /**
     * @brief Finds the level with the maximum sum of node values.
     * @param root The root of the binary tree.
     * @return The 1-based index of the level with the maximum sum.
     */
    int maxLevelSum(TreeNode *root)
    {
        if (!root)
            return 0;

        queue<TreeNode *> q;
        q.push(root);

        int currlevel = 1;
        int maxlevel = 1;

        // prevsum stores the maximum sum found so far (initialized to lowest possible value)
        long long maxsum = LLONG_MIN;

        while (!q.empty())
        {
            int size = q.size();
            long long currsum = 0; // Use long long to prevent overflow

            for (int i = 0; i < size; ++i)
            {
                TreeNode *node = q.front();
                q.pop();

                currsum += node->val;

                if (node->left)
                    q.push(node->left);
                if (node->right)
                    q.push(node->right);
            }

            // Note: If sums are equal, we stick with the smaller level index (maxlevel),
            // which is guaranteed by the strictly less than check.
            if (currsum > maxsum)
            {
                maxlevel = currlevel;
                maxsum = currsum;
            }

            ++currlevel;
        }
        return maxlevel;
    }
};

// Helper function to create a tree (used for testing)
TreeNode *createTree(vector<int> &nodes, int i)
{
    if (i >= nodes.size() || nodes[i] == -1)
    {
        return nullptr;
    }
    TreeNode *root = new TreeNode(nodes[i]);
    root->left = createTree(nodes, 2 * i + 1);
    root->right = createTree(nodes, 2 * i + 2);
    return root;
}

void deleteTree(TreeNode *root)
{
    if (!root)
        return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

int main()
{
    Solution sol;

    cout << "--- Maximum Level Sum of a Binary Tree ---\n";

    // Test Case 1: Standard case
    // Tree: [1, 7, 0, 7, -8, null, null]
    // Level 1 Sum: 1
    // Level 2 Sum: 7 + 0 = 7
    // Level 3 Sum: 7 + (-8) = -1
    // Max Sum: 7, Level: 2
    vector<int> nodes1 = {1, 7, 0, 7, -8, -1, -1};
    TreeNode *root1 = createTree(nodes1, 0);
    cout << "Test 1 (Standard): Max Level Sum is at Level " << sol.maxLevelSum(root1) << " (Expected: 2)" << endl;
    deleteTree(root1);

    // Test Case 2: Max sum is the root (Level 1)
    // Tree: [100, 2, 3]
    // Level 1 Sum: 100
    // Level 2 Sum: 2 + 3 = 5
    // Max Sum: 100, Level: 1
    vector<int> nodes2 = {100, 2, 3};
    TreeNode *root2 = createTree(nodes2, 0);
    cout << "Test 2 (Root Max): Max Level Sum is at Level " << sol.maxLevelSum(root2) << " (Expected: 1)" << endl;
    deleteTree(root2);

    // Test Case 3: Ties (problem asks for smallest level index)
    // Tree: [1, 1, 1, 1, 1, 1, 1]
    // Level 1 Sum: 1
    // Level 2 Sum: 2
    // Level 3 Sum: 4
    // Max Sum: 4, Level: 3 (No tie in this example)
    // Let's create a tie example:
    // Tree: [989, null, 10250, 98693, -89388, null, -32127]
    // Level 1: 989
    // Level 2: 10250
    // Level 3: 98693 + (-89388) = 9305
    // Level 4: -32127
    // Max Sum: 10250 (Level 2) vs 9305 (Level 3) -> Level 2 wins

    // Let's force a tie with negative numbers:
    // Tree: [10, -5, -5, 15, -15, 15, -15]
    // L1: 10
    // L2: -5 + (-5) = -10
    // L3: 15 + (-15) + 15 + (-15) = 0
    // L4: Empty
    // Max is 10 at L1

    // Let's create a tie-breaker (L2 = L3)
    // Tree: [0, 10, 10, 5, 5, 5, 5]
    // L1: 0
    // L2: 10 + 10 = 20
    // L3: 5 + 5 + 5 + 5 = 20
    // Max Sum: 20. Tie at L2 and L3. Should return L2 (the smallest index).
    vector<int> nodes3 = {0, 10, 10, 5, 5, 5, 5};
    TreeNode *root3 = createTree(nodes3, 0);
    cout << "Test 3 (Tie Breaker): Max Level Sum is at Level " << sol.maxLevelSum(root3) << " (Expected: 2)" << endl;
    deleteTree(root3);

    return 0;
}
