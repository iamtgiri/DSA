/*
File: insertion_search_deletion.cpp
Date: 2025-10-21 22:19

Problem: Implement a Red-Black Tree with insert, search, delete, and level order traversal.
Example:
Insert 10, 20, 30, 15
Level Order: 20B 10B 30B N 15R
After deleting 20 -> 15B 10B 30B

Problem Statement:
Implement the Red-Black Tree (RBT) data structure, a self-balancing Binary Search
Tree (BST) that guarantees logarithmic time complexity for core operations by
enforcing five key properties using node coloring ('R' for Red, 'B' for Black)
and rotations. This implementation includes insertion, search, deletion, and a
level-order traversal for visualization.

-------------------------------------------------
❌ Brute Force
- Idea: Use a standard Binary Search Tree (BST) for storing data.
- Time complexity: O(N) worst-case for insertion and search (when the tree becomes skewed).
- Space complexity: O(N).
- Limitations: Performance degrades significantly with sorted or nearly sorted input.

✅ Optimized Approachs
- Idea: The Red-Black Tree (RBT) uses node coloring and rotations to maintain a
  balanced height, ensuring the longest path from root to leaf is at most twice
  the shortest path.
- Approach: Self-Balancing Binary Search Tree (RBT).
- Algorithm: Insertion and Deletion operations (O(log N)) use rotations and
  recoloring to restore the five RBT properties upon violation.
- Time complexity: O(log N) for `insert`, `delete`, and `search`.
- Space complexity: O(N).

💡 Key Pattern:
- **Black Height Property:** The number of Black nodes on any simple path from a
  node down to a descendant NIL leaf is constant. Maintaining this is the core
  challenge of the deletion algorithm.

ℹ️ Keywords:
- Red-Black Tree, Self-Balancing, Rotation, Recolor, Sentinel Node (NIL), O(log N), Deletion.

🗒️ Notes
- The single **Sentinel NIL Node** (always Black) is crucial for simplifying
  boundary checks and pointer logic in both insertion and deletion.
- Deletion is significantly more complex than insertion due to the need to fix
  double-black violations.
-------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

// --- Node Structure ---
class Node
{
public:
    int data;
    Node *left, *right, *parent;
    char color; // 'R' or 'B'

    // Constructor for data nodes: initialized to Red, children/parent point to NIL
    Node(int val, Node *NIL) : data(val), left(NIL), right(NIL), parent(NIL), color('R') {}

    // Constructor for the NIL sentinel node: data=0, color=Black
    Node(char c) : data(0), left(nullptr), right(nullptr), parent(nullptr), color(c) {}
};

// --- Red-Black Tree Class ---
class RBTree
{
private:
    Node *root;
    Node *NIL; // The single sentinel node for all external leaves and null pointers

    /**
     * @brief Performs a left rotation around node x.
     */
    void rotateLeft(Node *x)
    {
        Node *y = x->right;

        // 1. Turn y's left subtree into x's right subtree
        x->right = y->left;
        if (y->left != NIL)
            y->left->parent = x;

        // 2. Link x's parent to y (y becomes the new root of this subtree)
        y->parent = x->parent;
        if (x->parent == NIL)
            root = y;
        else if (x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;

        // 3. Put x on y's left
        y->left = x;
        x->parent = y;
    }

    /**
     * @brief Performs a right rotation around node y.
     */
    void rotateRight(Node *y)
    {
        Node *x = y->left;

        // 1. Turn x's right subtree into y's left subtree
        y->left = x->right;
        if (x->right != NIL)
            x->right->parent = y;

        // 2. Link y's parent to x (x becomes the new root of this subtree)
        x->parent = y->parent;
        if (y->parent == NIL)
            root = x;
        else if (y == y->parent->right)
            y->parent->right = x;
        else
            y->parent->left = x;

        // 3. Put y on x's right
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
     * @brief Restores RBT properties after insertion by performing recoloring and rotations.
     */
    void fixViolation(Node *pt)
    {
        Node *parent = NIL;
        Node *grand_parent = NIL;
        Node *uncle = NIL;

        // Fixes double-Red violation (Property 4: children of Red node must be Black)
        while ((pt != root) && (pt->color == 'R') && (pt->parent->color == 'R'))
        {
            parent = pt->parent;
            grand_parent = parent->parent;

            // Case A: Parent is left child of grandparent
            if (parent == grand_parent->left)
            {
                uncle = grand_parent->right;

                // Case 1 (Recolor): Uncle is Red. Push Blackness down.
                if (uncle->color == 'R')
                {
                    grand_parent->color = 'R';
                    parent->color = 'B';
                    uncle->color = 'B';
                    pt = grand_parent; // Propagate check up to grandparent
                }
                else // Uncle is Black (or NIL)
                {
                    // Case 2 (LR/Triangle): pt is right child. Left rotation on parent.
                    if (pt == parent->right)
                    {
                        rotateLeft(parent);
                        pt = parent;
                        parent = pt->parent;
                    }
                    // Case 3 (LL/Line): pt is left child. Right rotation on grandparent.
                    rotateRight(grand_parent);
                    swap(parent->color, grand_parent->color);
                    pt = parent; // Violation fixed
                }
            }
            // Case B: Parent is right child of grandparent (Symmetric)
            else
            {
                uncle = grand_parent->left;

                // Case 1 (Recolor): Uncle is Red.
                if (uncle->color == 'R')
                {
                    grand_parent->color = 'R';
                    parent->color = 'B';
                    uncle->color = 'B';
                    pt = grand_parent;
                }
                else // Uncle is Black (or NIL)
                {
                    // Case 2 (RL/Triangle): pt is left child. Right rotation on parent.
                    if (pt == parent->left)
                    {
                        rotateRight(parent);
                        pt = parent;
                        parent = pt->parent;
                    }
                    // Case 3 (RR/Line): pt is right child. Left rotation on grandparent.
                    rotateLeft(grand_parent);
                    swap(parent->color, grand_parent->color);
                    pt = parent;
                }
            }
        }
        root->color = 'B'; // Property 2 (Root must be Black)
    }

    /**
     * @brief Replaces the subtree rooted at node u with the subtree rooted at node v.
     * @param u The node to be replaced.
     * @param v The node to replace u.
     */
    void transplant(Node *u, Node *v)
    {
        if (u->parent == NIL)
            root = v;
        else if (u == u->parent->left)
            u->parent->left = v;
        else
            u->parent->right = v;
        v->parent = u->parent;
    }

    /**
     * @brief Finds the node with the minimum value in the subtree rooted at x.
     */
    Node *minimum(Node *x)
    {
        while (x->left != NIL)
            x = x->left;
        return x;
    }

    /**
     * @brief Restores RBT properties after a Black node removal using rotations and recoloring.
     * This fixes the "double black" violation represented by node x.
     * @param x The node (or the NIL sentinel) occupying the position of the deleted Black node.
     */
    void fixDelete(Node *x)
    {
        // Loop runs until x reaches the root or is colored Red.
        while (x != root && x->color == 'B')
        {
            if (x == x->parent->left)
            {
                // x is a left child, w (sibling) is right child
                Node *w = x->parent->right;

                // Case 1: Sibling w is Red (Rotation to make sibling Black)
                if (w->color == 'R')
                {
                    w->color = 'B';
                    x->parent->color = 'R';
                    rotateLeft(x->parent);
                    w = x->parent->right; // New sibling w is Black
                }

                // Case 2: Sibling w is Black, and both of w's children are Black.
                if (w->left->color == 'B' && w->right->color == 'B')
                {
                    w->color = 'R'; // Steal Blackness from parent
                    x = x->parent;  // Propagate double-black up
                }
                else
                {
                    // Case 3: Sibling w is Black, w's right child is Black (Triangle case).
                    if (w->right->color == 'B')
                    {
                        w->left->color = 'B';
                        w->color = 'R';
                        rotateRight(w);
                        w = x->parent->right; // New sibling w (old w->left) is ready for Case 4
                    }
                    // Case 4: Sibling w is Black, w's right child is Red (Line case).
                    w->color = x->parent->color;
                    x->parent->color = 'B';
                    w->right->color = 'B';
                    rotateLeft(x->parent);
                    x = root; // Fix complete, terminate loop
                }
            }
            else // Symmetric case: x is a right child
            {
                Node *w = x->parent->left;

                // Case 1: Sibling w is Red
                if (w->color == 'R')
                {
                    w->color = 'B';
                    x->parent->color = 'R';
                    rotateRight(x->parent);
                    w = x->parent->left;
                }

                // Case 2: Sibling w is Black, both children Black
                if (w->right->color == 'B' && w->left->color == 'B')
                {
                    w->color = 'R';
                    x = x->parent;
                }
                else
                {
                    // Case 3: Sibling w is Black, w's left child is Black
                    if (w->left->color == 'B')
                    {
                        w->right->color = 'B';
                        w->color = 'R';
                        rotateLeft(w);
                        w = x->parent->left;
                    }
                    // Case 4: Sibling w is Black, w's left child is Red
                    w->color = x->parent->color;
                    x->parent->color = 'B';
                    w->left->color = 'B';
                    rotateRight(x->parent);
                    x = root;
                }
            }
        }
        x->color = 'B'; // Final step: If x was propagated up and became Red, color it Black.
    }

public:
    // Constructor
    RBTree()
    {
        NIL = new Node('B');
        NIL->left = NIL->right = NIL->parent = NIL; // Self-referencing sentinel
        root = NIL;
    }

    // Destructor
    ~RBTree()
    {
        // Simple post-order deletion
        function<void(Node *)> del = [&](Node *curr)
        {
            if (curr == NIL)
                return;
            del(curr->left);
            del(curr->right);
            delete curr;
        };
        del(root);
        delete NIL;
    }

    /**
     * @brief Inserts a new value into the Red-Black Tree.
     */
    void insert(int data)
    {
        Node *pt = new Node(data, NIL); // New node created as RED
        root = BSTInsert(root, pt);

        if (pt == root)
        {
            pt->color = 'B';
            return;
        }

        fixViolation(pt);
    }

    /**
     * @brief Searches for a value in the tree.
     */
    bool search(int val)
    {
        Node *curr = root;
        while (curr != NIL)
        {
            if (val == curr->data)
                return true;
            curr = (val < curr->data) ? curr->left : curr->right;
        }
        return false;
    }

    /**
     * @brief Deletes a value from the Red-Black Tree.
     * @param val The value to delete.
     */
    void deleteValue(int val)
    {
        // 1. Find the node z to delete
        Node *z = root;
        while (z != NIL && z->data != val)
        {
            z = (val < z->data) ? z->left : z->right;
        }
        if (z == NIL)
            return; // Value not found

        Node *y = z;
        Node *x;
        char yOriginalColor = y->color;

        // 2. BST Deletion logic
        if (z->left == NIL)
        {
            x = z->right;
            transplant(z, z->right); // Case: 0 or 1 right child
        }
        else if (z->right == NIL)
        {
            x = z->left;
            transplant(z, z->left); // Case: 1 left child
        }
        else
        {
            // Case: 2 children. y is successor (minimum of z's right subtree)
            y = minimum(z->right);
            yOriginalColor = y->color;
            x = y->right; // x is the node that moves into y's original spot

            if (y->parent == z)
            {
                // y is z's right child, x is correctly parented to y
                x->parent = y;
            }
            else
            {
                // y is deeper in the tree
                transplant(y, y->right); // y->right replaces y
                y->right = z->right;
                y->right->parent = y;
            }

            transplant(z, y); // y replaces z
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color; // y takes z's color
        }
        delete z;

        // 3. Fix Red-Black properties if a Black node was removed/moved (i.e., y was originally Black)
        if (yOriginalColor == 'B')
            fixDelete(x);
    }

    /**
     * @brief Prints the tree content in Level Order (BFS), including 'N' markers
     * for NIL children of non-NIL nodes for structural visualization.
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

            // Only push children if the current node is non-NIL.
            // Pushing NIL markers helps visualize missing links up to the last non-NIL level.
            if (curr->left != NIL || curr->right != NIL)
            {
                q.push(curr->left);
                q.push(curr->right);
            }
        }
        cout << endl;
    }
};

int main()
{
    RBTree tree;

    cout << "--- Initial Insertions (10, 20, 30, 15) ---" << endl;
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(15);

    // Structure: 20(B) is root. Left 10(B), Right 30(B). 10(B)'s right is 15(R).
    // Output: 20B 10B 30B N 15R N N N N
    cout << "Level Order Traversal: ";
    tree.levelOrder();

    // --- Deletion Test ---
    cout << "\n--- Deleting 20 (the root) ---" << endl;
    tree.deleteValue(20);
    // Successor 30 replaces 20. 30's original color (B) caused a fix.
    // New Structure: 30(B) is root. Left 10(B), 30's right is NIL. 10's right is 15(R).
    // The successor 30 becomes the new root and takes the color of the old root (B).
    // 30's original right child (NIL) is the double black node x.
    // 15 takes the place of 30 in the final correct structure.

    cout << "After deleting 20: ";
    tree.levelOrder(); // Expected: 30B 10B N N 15R N N

    cout << "\n--- Deleting 10 ---" << endl;
    tree.deleteValue(10);
    cout << "After deleting 10: ";
    tree.levelOrder(); // Expected: 30B 15R N N N

    cout << "\n--- Deleting 30 (the root) ---" << endl;
    tree.deleteValue(30);
    cout << "After deleting 30: ";
    tree.levelOrder(); // Expected: 15B N N

    cout << "\n--- Deleting 15 (the root) ---" << endl;
    tree.deleteValue(15);
    cout << "After deleting 15: ";
    tree.levelOrder(); // Expected: (Empty)

    cout << "\nSearch Results (final state):" << endl;
    cout << "15: " << (tree.search(15) ? "Found" : "Not Found") << endl;
    cout << "30: " << (tree.search(30) ? "Found" : "Not Found") << endl;

    return 0;
}
