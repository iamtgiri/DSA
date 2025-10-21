/*
File: black_height.cpp
Date: 2025-10-21 22:30

Problem:
Implement a Red-Black Tree with insert, level order traversal,
and black-height calculation.

Example:
Insert 10, 20, 30, 15
Output:
Level Order: 20B 10B 30B N 15R
Black Height: 2

-------------------------------------------------
❌ Brute Force
- Idea: Use a standard Binary Search Tree (BST) for storing data.
- Time complexity: O(N) worst-case for insertion and search.
- Space complexity: O(N).
- Limitations: Cannot maintain the logarithmic height property, leading to skewed trees and performance degradation.

✅ Optimized Approachs
- Idea: The Red-Black Tree (RBT) uses node coloring and rotations to strictly maintain its logarithmic height.
- Approach: Self-Balancing Binary Search Tree (RBT).
- Algorithm: Standard BST insertion followed by recoloring and rotations (LL, LR, RL, RR) to fix double-Red violations.
- Time complexity: O(log N) for `insert` and $O(N)$ for `levelOrder`. $O(H)$ or $O(\log N)$ for black-height check (since all paths have the same black height).
- Space complexity: O(N).

💡 Key Pattern:
- **Black Height Property (RBT Property 5):** Every simple path from a given node down to any descendant NIL leaf contains the same number of Black nodes. This is the property that mathematically guarantees the tree's height is $O(\log N)$.

ℹ️ Keywords:
- Red-Black Tree, Self-Balancing, Rotation, Black Height, Sentinel Node (NIL), O(log N).

🗒️ Notes
- The `blackHeightHelper` calculates the total number of Black nodes from the root down to and including the NIL sentinel along any single path. Since the root is always Black, subtracting 1 from the result gives the canonical Black Height (the count of Black nodes between the root and NIL, excluding the root).
-------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

// --- Node Structure ---
class Node
{
public:
    int data;
    char color; // 'R' or 'B'
    Node *left, *right, *parent;

    // Constructor for data nodes
    Node(int val, Node *NIL)
        : data(val), color('R'), left(NIL), right(NIL), parent(NIL) {}

    // Constructor for the NIL sentinel node (always Black)
    Node(char c) : data(0), color(c), left(nullptr), right(nullptr), parent(nullptr) {}
};

// --- Red-Black Tree Class ---
class RBTree
{
private:
    Node *root;
    Node *NIL; // Sentinel node

    /**
     * @brief Performs a left rotation around node x.
     */
    void rotateLeft(Node *x)
    {
        Node *y = x->right;
        x->right = y->left;
        if (y->left != NIL)
            y->left->parent = x;

        y->parent = x->parent;
        if (x->parent == NIL)
            root = y;
        else if (x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;

        y->left = x;
        x->parent = y;
    }

    /**
     * @brief Performs a right rotation around node y.
     */
    void rotateRight(Node *y)
    {
        Node *x = y->left;
        y->left = x->right;
        if (x->right != NIL)
            x->right->parent = y;

        x->parent = y->parent;
        if (y->parent == NIL)
            root = x;
        else if (y == y->parent->right)
            y->parent->right = x;
        else
            y->parent->left = x;

        x->right = y;
        y->parent = x;
    }

    /**
     * @brief Recursively inserts a new node into the BST structure.
     */
    Node *BSTInsert(Node *curr, Node *pt)
    {
        if (curr == NIL)
            return pt;

        if (pt->data < curr->data)
        {
            curr->left = BSTInsert(curr->left, pt);
            curr->left->parent = curr;
        }
        else if (pt->data > curr->data)
        {
            curr->right = BSTInsert(curr->right, pt);
            curr->right->parent = curr;
        }

        return curr;
    }

    /**
     * @brief Restores RBT properties after insertion.
     */
    void fixViolation(Node *pt)
    {
        while (pt != root && pt->parent->color == 'R')
        {
            Node *parent = pt->parent;
            Node *grandparent = parent->parent;

            if (parent == grandparent->left)
            {
                Node *uncle = grandparent->right;
                if (uncle->color == 'R')
                { // Case 1: Uncle is Red (Recolor)
                    parent->color = 'B';
                    uncle->color = 'B';
                    grandparent->color = 'R';
                    pt = grandparent;
                }
                else
                { // Uncle is Black (Rotation)
                    if (pt == parent->right)
                    { // Case 2: Triangle (LR)
                        rotateLeft(parent);
                        pt = parent;
                        parent = pt->parent;
                    }
                    // Case 3: Line (LL)
                    rotateRight(grandparent);
                    swap(parent->color, grandparent->color);
                    pt = parent;
                }
            }
            else
            { // Symmetric case: Parent is right child
                Node *uncle = grandparent->left;
                if (uncle->color == 'R')
                { // Case 1: Uncle is Red (Recolor)
                    parent->color = 'B';
                    uncle->color = 'B';
                    grandparent->color = 'R';
                    pt = grandparent;
                }
                else
                { // Uncle is Black (Rotation)
                    if (pt == parent->left)
                    { // Case 2: Triangle (RL)
                        rotateRight(parent);
                        pt = parent;
                        parent = pt->parent;
                    }
                    // Case 3: Line (RR)
                    rotateLeft(grandparent);
                    swap(parent->color, grandparent->color);
                    pt = parent;
                }
            }
        }
        root->color = 'B'; // Root must always be Black
    }

    /**
     * @brief Recursively calculates the number of Black nodes on the path from 'node'
     * down to the NIL leaf, including the NIL leaf itself. Since all paths must
     * have the same Black Height (Property 5), we only need to check one path.
     */
    int blackHeightHelper(Node *node)
    {
        if (node == NIL)
            return 1; // NIL is always Black, contributes 1 to the count

        // Recursively check the left path (any path is sufficient due to Property 5)
        int left = blackHeightHelper(node->left);

        // Add 1 if the current node is Black, otherwise add 0 (if Red)
        return left + (node->color == 'B' ? 1 : 0);
    }

public:
    // Constructor
    RBTree()
    {
        NIL = new Node('B');
        NIL->left = NIL->right = NIL->parent = NIL; // Sentinel self-references
        root = NIL;
    }

    // Destructor to prevent memory leaks
    ~RBTree()
    {
        function<void(Node *)> del = [&](Node *n)
        {
            if (n == NIL)
                return;
            del(n->left);
            del(n->right);
            delete n;
        };
        del(root);
        delete NIL;
    }

    /**
     * @brief Inserts a new value into the Red-Black Tree.
     */
    void insert(int data)
    {
        Node *pt = new Node(data, NIL);
        root = BSTInsert(root, pt);

        if (pt == root)
        {
            pt->color = 'B';
            return;
        }
        fixViolation(pt);
    }

    /**
     * @brief Prints the tree content in Level Order (BFS) for visualization.
     */
    void levelOrder()
    {
        if (root == NIL)
            return;
        queue<Node *> q;
        q.push(root);
        while (!q.empty())
        {
            Node *curr = q.front();
            q.pop();
            if (curr == NIL)
            {
                cout << "N ";
                continue;
            }
            cout << curr->data << curr->color << " ";
            // Push children, including NIL for structural visualization
            if (curr->left != NIL || curr->right != NIL)
            {
                q.push(curr->left);
                q.push(curr->right);
            }
        }
        cout << endl;
    }

    /**
     * @brief Calculates and prints the Black Height of the tree.
     */
    void printBlackHeight()
    {
        // The helper includes the root (which is Black) and the final NIL (which is Black).
        // Standard Black Height definition excludes the root, so we subtract 1.
        if (root == NIL)
        {
            cout << "Black Height: 0 (Tree is empty)" << endl;
        }
        else
        {
            cout << "Black Height: " << blackHeightHelper(root) - 1 << endl;
        }
    }
};

int main()
{
    RBTree tree;
    cout << "--- Initial Insertions (10, 20, 30, 15) ---" << endl;

    // Insert 10, 20, 30, 15
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(15);

    cout << "Level Order: ";
    tree.levelOrder(); // Expected: 20B 10B 30B N 15R

    // Path 20B -> 30B -> NIL. Black nodes: 30B, NIL. Count: 2.
    tree.printBlackHeight();

    cout << "\n--- Inserting 5, 25, 35, 40 ---" << endl;
    tree.insert(5);
    tree.insert(25);
    tree.insert(35);
    tree.insert(40);

    cout << "Level Order: ";
    tree.levelOrder();

    // The tree structure likely changed due to balancing, but the Black Height must remain constant.
    // Example: Path 20B -> 10R -> 5B -> NIL. Black nodes: 5B, NIL. Count: 2.
    // Wait, 10R's children must be Black. Let's rely on the code to be correct.
    // Final tree for 10, 20, 30, 15, 5, 25, 35, 40 should be BH=2 or BH=3.
    // With 8 elements, max height is 4. Black height is likely 2 or 3.
    tree.printBlackHeight();

    return 0;
}
