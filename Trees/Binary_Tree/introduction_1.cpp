#include <iostream>
#include <queue>

// Use a namespace to avoid name clashes
using namespace std;

/**
 * @class Node
 * @brief Represents a single node in a binary tree.
 * @param data The data value stored in the node.
 * @param left Pointer to the left child node.
 * @param right Pointer to the right child node.
 * Each node contains an integer data value and pointers to its left and right children.
 */
class Node
{
public:
    int data;    // The data value stored in the node.
    Node *left;  // Pointer to the left child node.
    Node *right; // Pointer to the right child node.

    /**
     * @brief Constructs a new Node object.
     * @param val The integer value to be stored in the node.
     *
     * Initializes the node with the given value and sets the child pointers to null.
     */
    Node(int val)
    {
        data = val;
        left = nullptr;
        right = nullptr;
    }
};

/**
 * @brief Main function to create a binary tree using level-order traversal (breadth-first).
 *
 * This program interactively builds a binary tree by prompting the user for node values.
 * A value of -1 indicates a null child, which is used to terminate a branch.
 */
int main()
{
    // Variable to store the root node's value
    int rootValue;

    cout << "Enter the value for the root node: ";
    cin >> rootValue;

    // Create the root node
    Node *root = new Node(rootValue);

    // Create a queue for level-order traversal
    queue<Node *> q;
    q.push(root);

    // Start the level-order traversal to build the tree
    while (!q.empty())
    {
        // Get the front node from the queue
        Node *temp = q.front();
        q.pop();

        int leftValue, rightValue;

        // Prompt for and read the left child's value
        cout << "Enter the left child of " << temp->data << " (-1 for no child): ";
        cin >> leftValue;

        // If the value is not -1, create a new node and add it to the queue
        if (leftValue != -1)
        {
            temp->left = new Node(leftValue);
            q.push(temp->left);
        }

        // Prompt for and read the right child's value
        cout << "Enter the right child of " << temp->data << " (-1 for no child): ";
        cin >> rightValue;

        // If the value is not -1, create a new node and add it to the queue
        if (rightValue != -1)
        {
            temp->right = new Node(rightValue);
            q.push(temp->right);
        }
    }

    // Note: The program ends here. The created tree is not traversed or deallocated.
    // In a complete program, you would need to add code to perform operations on the tree
    // and properly deallocate the memory to prevent memory leaks.

    return 0;
}