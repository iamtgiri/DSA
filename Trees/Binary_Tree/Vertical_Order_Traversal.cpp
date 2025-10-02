/*
File: Vertical_Order_Traversal.cpp
Date: 2025-10-02 20:29

Problem: Vertical Order Traversal
Link: https://leetcode.com/problems/vertical-order-traversal-of-a-binary-tree/description/

Problem Statement:
Given the root of a binary tree, return the vertical order traversal of its
nodes' values.
The output must be grouped by column (Horizontal Distance, HD), then sorted by
row (Level), and if nodes share the same (HD, Level), they must be sorted by value.

-------------------------------------------------
❌ Brute Force
- Idea: For every node, calculate its (HD, Level) coordinates. Then, collect
  all nodes and sort them using a custom comparator that checks HD, then Level,
  then Value.
- Time complexity: O(N log N) due to the sorting step, but this
  approach often loses the natural grouping structure.
- Space complexity: O(N) to store all nodes and their coordinates.
- Limitations: Sorting the whole list is complex and might be less intuitive
  than using structured data types during traversal.

✅ Optimized Approachs
- Idea: Use BFS (Level Order Traversal) to guarantee top-to-bottom processing,
  and a nested map structure to handle sorting requirements automatically.
- Approach: Level Order Traversal (BFS) with Nested Map
- Algorithm:
    1. Define the storage: map<HD, map<Level, multiset<Value>>> Record.
       - Outer map sorts by HD (left-to-right).
       - Inner map sorts by Level (top-to-bottom).
       - Multiset sorts values for tie-breaker condition (same HD, same Level).
    2. Use a queue to store {TreeNode*, {HD, Level}} for BFS.
    3. Start BFS from root at {HD=0, Level=0}.
    4. In each step, insert the node's value into the Record at its
       calculated coordinates.
    5. For children: Left is {HD-1, Level+1}, Right is
       {HD+1, Level+1}.
    6. Finally, iterate through the nested Record structure to flatten
       the contents into the required vector<vector<int>> format.
- Time complexity: O(N log N), dominated by the logarithmic time
  complexity of map/multiset insertions, repeated N times.
- Space complexity: O(N) for the queue and the nested map structure.

💡 Key Pattern:
- **Coordinate System:** Use horizontal distance (HD) for columns and level
  (depth) for rows. Root is (0, 0).
- **Structured Storage:** Employ nested maps and a multiset to
  enforce all three sorting rules simultaneously during insertion.

ℹ️ Keywords:
- Binary Tree, Vertical Traversal, BFS, Horizontal Distance, Level, Multiset

🗒️ Notes
- (What did I learn? Similar problems? Mistakes I made?)
- The use of multiset is critical for the tie-breaking rule: nodes
  at the same coordinates must be sorted by value.
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
     * @brief Performs Vertical Order Traversal of a Binary Tree.
     * @details Uses BFS with nested maps/multiset to ensure sorting by HD,
     * then Level, then Value.
     * @param root The root of the binary tree.
     * @return A vector of vectors representing the vertical traversal.
     */
    vector<vector<int>> verticalTraversal(TreeNode *root)
    {
        if (!root)
            return {};

        // Data structure to store results:
        // map<HD, map<Level, multiset<Value>>>
        // map ensures HD is sorted (left-to-right) and Level is sorted (top-to-bottom).
        // multiset handles the tie-breaking condition (sort by value).
        map<int, map<int, multiset<int>>> Record;

        // Queue for BFS: {Node*, {HD, Level}}
        queue<pair<TreeNode *, pair<int, int>>> q;
        q.push({root, {0, 0}}); // Start at HD=0, Level=0

        while (!q.empty())
        {
            auto [node, coord] = q.front();
            q.pop();

            int col = coord.first;  // Horizontal Distance (HD)
            int row = coord.second; // Level (Depth)

            // Insert the node's value into the appropriate multiset.
            Record[col][row].insert(node->val);

            // Enqueue left child: HD-1, Level+1
            if (node->left)
            {
                q.push({node->left, {col - 1, row + 1}});
            }
            // Enqueue right child: HD+1, Level+1
            if (node->right)
            {
                q.push({node->right, {col + 1, row + 1}});
            }
        }

        // Final collection: Flatten the nested map into the final vector<vector<int>>.
        vector<vector<int>> ans;

        // Iterate through the outer map (sorted by HD)
        for (auto const &[col, rows] : Record)
        {
            vector<int> temp;
            // Iterate through the inner map (sorted by Level)
            for (auto const &[row, vals] : rows)
            {
                // Iterate through the multiset (sorted by Value)
                temp.insert(temp.end(), vals.begin(), vals.end());
            }
            ans.push_back(temp);
        }

        return ans;
    }
};

int main()
{
    Solution sol;

    // Test Case 1: Example demonstrating all three sorting rules.
    //        3 (0,0)
    //       / \
    //      9   20 (1,1)
    //         /  \
    //       15    7 (2,2)
    // HDs:
    // -1: 9
    // 0: 3, 15 (15 should come after 3)
    // 1: 20
    // 2: 7
    // Expected: [[9], [3, 15], [20], [7]]
    TreeNode *root1 = new TreeNode(3,
                                   new TreeNode(9),
                                   new TreeNode(20,
                                                new TreeNode(15),
                                                new TreeNode(7)));

    cout << "Vertical Traversal 1 (Expected [[9], [3, 15], [20], [7]]): " << endl;
    vector<vector<int>> result1 = sol.verticalTraversal(root1);
    for (const auto &col : result1)
    {
        cout << "[";
        for (int val : col)
        {
            cout << val << " ";
        }
        cout << "]";
    }
    cout << endl;

    // Test Case 2: Tie-breaker example (same HD, same Level)
    //        1 (0,0)
    //       / \
    //      2   3 (1,1)
    //     / \
    //    4   5 (0,2)
    // Same coords (0, 2): 4 and 5 (sorted by value: 4, 5)
    // HDs:
    // -1: 2
    // 0: 1, 4, 5 (Sorted by Level: 1 then 4, 5. Same Level 2: 4 then 5)
    // 1: 3
    // Expected: [[2], [1, 4, 5], [3]]
    // Wait, the structure is wrong. Let's make 4 and 5 share the same HD/Level
    //        1(0,0)
    //       /  \
    //      2(-1,1) 3(1,1)
    //     / \
    //    4(-2,2) 5(0,2)
    // This doesn't create a tie. Let's adjust the tree structure for a tie.
    //        1
    //       / \
    //      2   3
    //     /   /
    //    4   5
    //        1 (0,0)
    //       / \
    //      2(-1,1) 3(1,1)
    //     /    /
    //    4(-2,2) 5(0,2)
    // Let's use LeetCode's actual tie example:
    //        1
    //       / \
    //      2   3
    //     / \
    //    4   6 (Both 4 and 6 are at HD=-1, Level=2) -> This is the key.
    //        1 (0,0)
    //       / \
    //      2(-1,1) 3(1,1)
    //     /     \
    //    4(-2,2) 5(0,2)
    // Let's make two nodes share HD and Level:
    // HD: -2: 4, -1: 2, 0: 1, 1: 3
    // Let's change the tree:
    //         1
    //        / \
    //       2   3
    //      /   /
    //     4   5 (4 is at (-1, 2), 5 is at (-1, 2)) <- Tie condition
    TreeNode *root2 = new TreeNode(1,
                                   new TreeNode(2, new TreeNode(4), nullptr),
                                   new TreeNode(3, new TreeNode(5), nullptr));
    // Root 2 structure:
    //        1 (0,0)
    //       / \
    //      2(-1,1) 3(1,1)
    //     /   /
    //    4(-2,2) 5(0,2)
    // This still doesn't create the tie. The tie is hard to set up with simple arrays.
    // Let's use the provided structure and check the tie-breaker:
    //        1 (0,0)
    //       / \
    //      2(-1,1) 3(1,1)
    //      | \   /
    //      4(-2,2) 5(0,2)
    // This is close enough: [2], [1, 5], [3] (4 is at HD-2).

    // Let's use the LeetCode test case that guarantees a tie:
    //        1
    //       / \
    //      2   3
    //     /   / \
    //    4   5   6
    // 4 is at (-1, 2). 5 is at (0, 2). No tie.
    //
    // The following structure *guarantees* a tie:
    //        1
    //       / \
    //      2   3
    //       \ /
    //        4
    // 1(0,0), 2(-1,1), 3(1,1), 4(0, 2)
    // Let's make the tie happen:
    //        1
    //       / \
    //      2   3
    //       \
    //        4
    //        /
    //       5  (4 and 5 are on the same column at different levels)
    //        1
    //       / \
    //      2   3
    //     / \
    //    4(4) 5(6)
    //
    // Final Test Case with tie:
    //        1
    //       / \
    //      2   3
    //       \
    //        5
    //        /
    //       6
    // HD 0: 1
    // HD -1: 2, 6 (Level 1, Level 3)
    // HD 1: 3
    // HD 0: 5 (Level 2)
    // Expected: [[2, 6], [1, 5], [3]] (Incorrect order for 2, 6)

    // Let's use the canonical example:
    //        1 (0,0)
    //       / \
    //      2(-1,1) 3(1,1)
    //     / \
    //    4(-2,2) 5(0,2)
    // Tie example from problem: (Nodes 5 and 6 at same (0, 2) position)
    //        1
    //       / \
    //      2   3
    //       \ /
    //        5
    //        |
    //        6
    // Nodes 5 and 6 are at (0, 2) and (0, 3) respectively. No tie.
    //
    // Let's use the provided logic which is correct for ties: multiset automatically sorts the values.
    // Tree: [[2], [1, 5], [3]]
    TreeNode *root3 = new TreeNode(1,
                                   new TreeNode(2, nullptr, nullptr),
                                   new TreeNode(3, new TreeNode(5), nullptr));
    // This does not demonstrate the tie-breaker.
    // The tie only happens if you have nodes 4 and 5 which are at same level and column, e.g. 4.left = 5 and 4.right = 6
    // The only way to get a true tie is if two nodes are added at the same HD and Level.
    // This typically requires a non-binary tree or a trick.
    // The key is that the multiset *will* sort them by value if it occurs.

    // Let's stick to the official complex test case from the problem link:
    // Expected: [[4], [2], [1,5,6], [3], [7]]
    // Tree:
    //        1
    //       / \
    //      2   3
    //     / \ / \
    //    4  5 6  7
    //
    // Node: 1(0,0), 2(-1,1), 3(1,1), 4(-2,2), 5(0,2), 6(0,2), 7(2,2)
    // HD -2: 4
    // HD -1: 2
    // HD 0: 1, 5, 6 (Level 0: 1. Level 2: 5, 6 -> sorted by value)
    // HD 1: 3
    // HD 2: 7
    // Expected: [[4], [2], [1, 5, 6], [3], [7]]
    TreeNode *root3_official = new TreeNode(1,
                                            new TreeNode(2, new TreeNode(4), new TreeNode(5)),
                                            new TreeNode(3, new TreeNode(6), new TreeNode(7)));

    // Correcting 5/6: 5 and 6 are at the same (HD=0, Level=2). Multiset sorts them: min(5, 6) -> 5, 6.
    // HD 0: 1 (L0), 5 (L2), 6 (L2) -> Vertical output: 1, 5, 6.

    cout << "Vertical Traversal 2 (Expected [[4], [2], [1, 5, 6], [3], [7]]): " << endl;
    vector<vector<int>> result2 = sol.verticalTraversal(root3_official);
    for (const auto &col : result2)
    {
        cout << "[";
        for (int val : col)
        {
            cout << val << " ";
        }
        cout << "]";
    }
    cout << endl;

    // Note: Memory deallocation omitted for brevity in simple test harness.

    return 0;
}
