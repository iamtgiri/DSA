/*
File: Average_of_Levels_in_Binary_Tree.cpp
Date: 2025-11-19 00:39

Problem: Average of Levels in Binary Tree
Link: https://leetcode.com/problems/average-of-levels-in-binary-tree/description/

Problem Statement:
Given the root of a binary tree, return the average value of the nodes on each level in the form of an array. Answers within 10^-5 of the actual answer will be accepted.

-------------------------------------------------
Brute Force (if any, ignore if not applicable)
- Idea: Depth-First Search (DFS) or Pre-order Traversal. Use recursion and pass the current depth/level index to track which level a node belongs to. Store all nodes in a map or a list of lists, indexed by level.
- Time complexity: O(N) (Visit every node once).
- Space complexity: O(H) for recursion stack + O(N) for storing all node values grouped by level.
- Limitations: Less direct for level-based grouping; requires external structure (like a map) to accumulate sums per level.

Current/Optimized Approachs
- Idea: Use Level Order Traversal (BFS), which naturally groups nodes by level using a queue.
- Approach: **Breadth-First Search (BFS) / Level Order Traversal**
- Algorithm:
  1. Initialize a queue and push the `root`. Initialize the result vector.
  2. While the queue is not empty:
     a. Get the size of the queue (`size`), representing the number of nodes on the current level.
     b. Initialize a `double` sum (`sum = 0.0`) for the current level to maintain precision and prevent integer overflow.
     c. Iterate `size` times (processing *exactly* the nodes of the current level):
        i. Dequeue the current node.
        ii. Add its value to `sum`.
        iii. Enqueue its non-null children (left and right).
     d. Calculate the average (`sum / size`) and push it to the result vector.
- Time complexity: O(N). Every node is processed exactly once.
- Space complexity: O(W), where W is the maximum width of the tree (the maximum number of nodes in any single level). W is at most N/2 + 1, so O(N) in the worst case.

💡 Key Pattern:
- **Level Order Traversal:** Whenever a problem asks for an operation per level (e.g., sum, count, average, max/min), BFS is the most intuitive and clean approach.

ℹ️ Keywords:
- BFS, Queue, Level Order, Traversal, Binary Tree, Average.

🗒️ Notes
- Using `double` for `sum` and division is critical to meet the precision requirements of the problem.
-------------------------------------------------
*/

#include <iostream>
#include <vector>
#include <queue>
#include <numeric>
#include <iomanip>

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
     * @brief Computes the average value of nodes at each level of a binary tree.
     * @param root The root node of the binary tree.
     * @return A vector of doubles representing the average value of each level.
     */
    vector<double> averageOfLevels(TreeNode *root)
    {
        if (!root)
            return {};

        vector<double> ans;
        queue<TreeNode *> q;
        q.push(root);

        while (!q.empty())
        {
            // Store the current size of the queue (number of nodes in the current level)
            int size = q.size();
            // Use double for sum to maintain precision and avoid overflow
            double sum = 0.0;

            // Process all nodes at the current level
            for (int i = 0; i < size; ++i)
            {
                TreeNode *node = q.front();
                q.pop();

                sum += node->val;

                // Enqueue children for the next level
                if (node->left)
                    q.push(node->left);
                if (node->right)
                    q.push(node->right);
            }

            // Calculate and store the average for the current level
            ans.push_back(sum / size);
        }
        return ans;
    }
};

// Helper function to build the tree from a vector (for testing)
TreeNode *buildTree(const vector<int *> &nodes, int index)
{
    if (index >= nodes.size() || nodes[index] == nullptr)
    {
        return nullptr;
    }
    TreeNode *root = new TreeNode(*(nodes[index]));
    root->left = buildTree(nodes, 2 * index + 1);
    root->right = buildTree(nodes, 2 * index + 2);
    return root;
}

int main()
{
    Solution sol;

    // --- Example 1: [3, 9, 20, null, null, 15, 7]
    // Level 0: 3 / 1 = 3.0
    // Level 1: (9 + 20) / 2 = 14.5
    // Level 2: (15 + 7) / 2 = 11.0
    // Expected: [3.0, 14.5, 11.0]
    int n3 = 3, n9 = 9, n20 = 20, n15 = 15, n7 = 7;
    vector<int *> nodes1 = {&n3, &n9, &n20, nullptr, nullptr, &n15, &n7};
    TreeNode *root1 = buildTree(nodes1, 0);

    cout << "Test Case 1: [3, 9, 20, null, null, 15, 7]" << endl;
    vector<double> result1 = sol.averageOfLevels(root1);
    cout << "Result: ";
    for (double avg : result1)
    {
        cout << fixed << setprecision(5) << avg << " ";
    }
    cout << " (Expected: 3.00000 14.50000 11.00000)" << endl;

    // --- Example 2: [2147483647, 2147483647, 2147483647] (Testing large numbers and precision)
    // Level 0: 2147483647 / 1 = 2147483647.0
    // Level 1: (2147483647 + 2147483647) / 2 = 2147483647.0
    // Expected: [2147483647.0, 2147483647.0]
    int nmax = 2147483647; // Max int value
    vector<int *> nodes2 = {&nmax, &nmax, &nmax};
    TreeNode *root2 = buildTree(nodes2, 0);

    cout << "\nTest Case 2: [2147483647, 2147483647, 2147483647]" << endl;
    vector<double> result2 = sol.averageOfLevels(root2);
    cout << "Result: ";
    for (double avg : result2)
    {
        cout << fixed << setprecision(1) << avg << " ";
    }
    cout << " (Expected: 2147483647.0 2147483647.0)" << endl;

    return 0;
}