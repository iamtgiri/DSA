/*
File: Print_Root_to_a_Node_Path_in_Binary_Tree.cpp
Date: 2025-10-08 19:32

Problem: Print Root to a Node Path in a Binary Tree
Link: https://takeuforward.org/data-structure/print-root-to-node-path-in-a-binary-tree/

Problem Statement:
Given the root of a binary tree and an integer target, return the path (as a
vector of integers) from the root to the target node. If the target node is not
present in the tree, return an empty vector.

-------------------------------------------------
❌ Brute Force
- Idea: First, find the target node using a full BFS or DFS. Once found, traverse
  from the root again, explicitly checking for the target node's location to
  build the path.
- Time complexity: O(N) to find the node + O(H) to build the path. Overall O(N).
- Space complexity: O(N) to store the result, plus auxiliary space for traversal.
- Limitations: Requires storing state or performing redundant traversal.

✅ Optimized Approachs
- Idea: Use **Depth First Search (DFS)** with **backtracking**. We build the path
  as we descend. When we hit the target, we stop and return success. If a branch
  fails, we remove the current node from the path (backtrack).
- Approach: Recursive DFS with Path Tracking and Backtracking
- Algorithm:
    1. Define a recursive function `findPath(node, target, path)`.
    2. Base Case: If `node` is null, return `false`.
    3. Add `node->val` to the `path` vector.
    4. Success Check: If `node->val == target`, return `true`.
    5. Recurse: Call `findPath` on left and right. If either returns `true`,
       return `true` immediately (this preserves the path).
    6. Backtrack: If the target was not found in the current branch, remove
       the current node from the path using `path.pop_back()` and return `false`.
- Time complexity: O(N). In the worst case, all nodes are visited once.
- Space complexity: O(H) for the recursion stack and O(H) for the path vector,
  where H is the height of the tree.

💡 Key Pattern:
- **DFS and Backtracking:** Recursion combined with adding/removing elements from
  a shared state (the `path` vector) is the canonical way to find a single
  solution (like a path) in a tree or graph.

ℹ️ Keywords:
- Binary Tree, DFS, Backtracking, Root-to-Node, Path Finding, Recursion

🗒️ Notes
- (What did I learn? Similar problems? Mistakes I made?)
- This pattern is crucial for many path-related problems (e.g., Path Sum II).
- The key is the `path.pop_back()` step, which ensures that nodes only remain
  in the vector if they are part of the successful root-to-target path.
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
     * @brief Constructor with value.
     */
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}

    // Other constructors omitted for brevity in this file.
};

class Solution
{
public:
    /**
     * @brief Public entry point to find the path from the root to the target node.
     * @param root The root of the binary tree.
     * @param target The integer value of the node to find.
     * @return A vector of integers representing the path from root to target, or empty if not found.
     */
    vector<int> pathFromRoot(TreeNode *root, int target)
    {
        vector<int> path;
        // The findPath function handles the recursion and path construction.
        findPath(root, target, path);
        return path;
    }

private:
    /**
     * @brief Recursive helper function to perform DFS and find the path to the target.
     * @param root The current node in the traversal.
     * @param target The integer value to search for.
     * @param path The path vector, passed by reference to be built.
     * @return True if the target was found in this subtree, false otherwise.
     */
    bool findPath(TreeNode *root, int target, vector<int> &path)
    {
        // Base case: Reached null pointer, target not found in this branch.
        if (!root)
            return false;

        // Add current node's value to the potential path.
        path.push_back(root->val);

        // Success condition: Target found. Return true to stop further backtracking.
        if (root->val == target)
            return true;

        // Recurse left or right. If the target is found in either child's subtree,
        // we return true, preserving the path state built so far.
        if (findPath(root->left, target, path) || findPath(root->right, target, path))
            return true;

        // Backtrack: If the target was not found in the current node's subtree (left and right returned false),
        // this node is not part of the final path, so we remove it.
        path.pop_back();
        return false;
    }
};

// Helper function to create a test tree
TreeNode *createTestTree()
{
    // Tree structure:
    //      1
    //     / \
    //    2   3
    //   / \
    //  4   5

    TreeNode *node4 = new TreeNode(4);
    TreeNode *node5 = new TreeNode(5);
    TreeNode *node2 = new TreeNode(2);
    node2->left = node4;
    node2->right = node5;
    TreeNode *node3 = new TreeNode(3);
    TreeNode *root = new TreeNode(1);
    root->left = node2;
    root->right = node3;

    return root;
}

void printPath(const vector<int> &path)
{
    if (path.empty())
    {
        cout << "Path not found." << endl;
        return;
    }
    cout << "Path: [";
    for (size_t i = 0; i < path.size(); ++i)
    {
        cout << path[i];
        if (i < path.size() - 1)
        {
            cout << " -> ";
        }
    }
    cout << "]" << endl;
}

int main()
{
    Solution sol;

    TreeNode *root = createTestTree();

    int target1 = 5;
    cout << "Target: " << target1 << endl;
    vector<int> path1 = sol.pathFromRoot(root, target1);
    // Expected: [1 -> 2 -> 5]
    printPath(path1);

    int target2 = 3;
    cout << "\nTarget: " << target2 << endl;
    vector<int> path2 = sol.pathFromRoot(root, target2);
    // Expected: [1 -> 3]
    printPath(path2);

    int target3 = 10;
    cout << "\nTarget: " << target3 << endl;
    vector<int> path3 = sol.pathFromRoot(root, target3);
    // Expected: Path not found.
    printPath(path3);

    // Note: Memory deallocation omitted for brevity in simple test harness.

    return 0;
}
