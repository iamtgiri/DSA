/*
File: Top_View_of_Binary_Tree.cpp
Date: 2025-10-01 21:14

Problem: Top View of Binary Tree
Link: https://www.geeksforgeeks.org/problems/top-view-of-binary-tree/1

Problem Statement:
Given a Binary Tree, get the top view of it. The top view is the set of nodes
visible when the tree is viewed from the top. A node is visible if no other
node is located strictly above it at the same horizontal distance.

-------------------------------------------------
❌ Brute Force
- Idea: For every horizontal distance (HD), traverse the entire tree multiple
  times to find the node at the minimum depth for that HD.
- Time complexity:  O(N^2)
- Space complexity:  O(N)
- Limitations: Highly inefficient due to repeated traversals.

✅ Optimized Approachs
- Idea: Traverse the tree while tracking the horizontal distance (HD) of each
  node. For the Top View, we only care about the *first* node we encounter
  at a given HD. BFS naturally finds nodes layer by layer (top-to-bottom).
- Approach: Level Order Traversal (BFS) with Horizontal Distance Mapping
- Algorithm:
    1. Use a **map** (e.g., std::map<int, int>) to store the result,
       where  key  is the horizontal distance (HD) and  value  is
       the node's value. Using  std::map  ensures keys are sorted, giving
       the left-to-right order for the final result.
    2. Use a **queue** to store pairs of (TreeNode* , HD) for BFS.
    3. Start BFS: Root node has HD=0.
    4. When visiting a node, if its HD is **not yet present** in the map, add it.
       (Since BFS explores top-to-bottom, the first node seen at any HD is the
       topmost node at that HD).
    5. The left child has  HD-1 ; the right child has  HD+1 .
    6. After BFS, iterate through the map to collect the values in order of keys.
- Time complexity:  O}(N \log N), due to N nodes inserted into the map
  (or  O}(N) if using  std::unordered_map  followed by sorting keys).
- Space complexity:  O}(N) for the map and queue.

💡 Key Pattern:
- **Horizontal Distance (HD):** Assign  HD=0 to the root,  HD-1 
  for left,  HD+1  for right.
- **BFS + Map:** Use BFS to guarantee top-to-bottom traversal (minimum depth
  first). Use a map to store the first element seen for each HD.

ℹ️ Keywords:
- Binary Tree, Top View, BFS, Level Order, Horizontal Distance, Map

🗒️ Notes
- (What did I learn? Similar problems? Mistakes I made?)
- **Difference from Bottom View:** For Top View, we only insert into the map
  if the HD is *new*. For Bottom View, we *always* update the map, ensuring
  the deepest node is stored.
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
     * @brief Finds the top view of the binary tree using BFS and Horizontal Distance mapping.
     * @param root The root of the binary tree.
     * @return A vector containing the nodes visible from the top, in left-to-right order.
     */
    vector<int> topView(TreeNode *root)
    {
        if (!root)
            return {};

        // map<Horizontal Distance, Node Value>
        // std::map automatically sorts by key (HD), ensuring left-to-right order.
        map<int, int> topViewMap;

        // queue<pair<Node*, Horizontal Distance>> for BFS
        queue<pair<TreeNode *, int>> q;

        q.emplace(root, 0); // Start at HD 0

        while (!q.empty())
        {
            auto [node, hd] = q.front();
            q.pop();

            // Key condition for Top View:
            // If this horizontal distance (hd) is seen for the first time,
            // the current node is the highest/topmost node at this position.
            if (topViewMap.find(hd) == topViewMap.end())
            {
                topViewMap[hd] = node->val;
            }

            // Enqueue children with updated HD
            if (node->left)
            {
                q.emplace(node->left, hd - 1);
            }
            if (node->right)
            {
                q.emplace(node->right, hd + 1);
            }
        }

        // Convert the map values into a result vector (which is naturally sorted by HD)
        vector<int> ans;
        for (auto const &[hd, val] : topViewMap)
        {
            ans.push_back(val);
        }

        return ans;
    }
};

int main()
{
    Solution sol;

    // Test Case 1: Example from GFG/LeetCode concept
    //        1
    //       / \
    //      2   3
    //     / \
    //    4   5
    // Top View: 4, 2, 1, 3 (5 is hidden by 2/1)
    TreeNode *root1 = new TreeNode(1,
                                   new TreeNode(2, new TreeNode(4), new TreeNode(5)),
                                   new TreeNode(3));

    cout << "Tree 1 Top View (Expected 4 2 1 3): ";
    for (int val : sol.topView(root1))
    {
        cout << val << " ";
    }
    cout << endl;

    // Test Case 2: Tree with deeper nodes at same HD
    //        1
    //       / \
    //      2   3
    //     / \ / \
    //    4  5 6  7
    //   /
    //  8
    // HDs: 4(-2), 2(-1), 1(0), 3(1), 7(2)
    // Nodes at HD=0: 1 (level 0), 5 (level 2), 6 (level 2)
    // Top View: 4, 2, 1, 3, 7 (8 is hidden by 4/2)
    TreeNode *root2 = new TreeNode(1, new TreeNode(2, new TreeNode(4, new TreeNode(8), nullptr), new TreeNode(5)),
                                   new TreeNode(3, new TreeNode(6), new TreeNode(7)));

    cout << "Tree 2 Top View (Expected 8 4 2 1 3 7): ";
    // Correction: 8 is at HD=-2, 4 is at HD=-2. 8 is deeper, so 4 is visible.
    // HDs:
    // -2: 4
    // -1: 2, 8 (4 is visible over 8) -> Wait, 8 is a child of 4. HD: 4(-2) -> 8(-3).
    // Let's re-verify HDs:
    // 1(0)
    // 2(-1), 3(1)
    // 4(-2), 5(0), 6(0), 7(2)
    // 8(-3)
    // Top View Map: -3: 8, -2: 4, -1: 2, 0: 1, 1: 3, 2: 7
    // Expected: 8 4 2 1 3 7
    for (int val : sol.topView(root2))
    {
        cout << val << " ";
    }
    cout << endl;

    // Note: Memory deallocation omitted for brevity in simple test harness.

    return 0;
}
