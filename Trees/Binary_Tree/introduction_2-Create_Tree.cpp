#include <iostream>
#include <memory>   // For std::unique_ptr and std::make_unique

/**
 * @class Node
 * @brief Represents a node in a binary tree.
 *
 * Each node stores an integer value and has unique ownership of its left
 * and right children using std::unique_ptr. This prevents memory leaks by
 * automatically deallocating the tree when the root goes out of scope.
 */
class Node {
public:
    int data;
    std::unique_ptr<Node> left;
    std::unique_ptr<Node> right;

    /**
     * @brief Constructs a Node with a given value.
     * @param val The integer value to be stored in the node.
     */
    explicit Node(int val) : data(val) {}

    /**
     * @brief Constructs a Node with a given value and children.
     * @param val The integer value.
     * @param l A unique pointer to the left child.
     * @param r A unique pointer to the right child.
     */
    Node(int val, std::unique_ptr<Node> l, std::unique_ptr<Node> r)
        : data(val), left(std::move(l)), right(std::move(r)) {}
};

/**
 * @brief Recursively creates a binary tree by prompting the user for input.
 *
 * The tree is built in a pre-order fashion. A value of -1 indicates a null child.
 * For example, to create a tree with root 1, left child 2, and right child 3,
 * the input sequence would be: `1, 2, -1, -1, 3, -1, -1`.
 *
 * @param parent_val The value of the parent node, used for clearer prompts.
 * @return A unique pointer to the root of the newly created subtree.
 */
std::unique_ptr<Node> createBinaryTree(int parent_val = -1) {
    int x;
    if (parent_val == -1) {
        std::cout << "Enter root value (-1 for an empty tree): ";
    } else {
        std::cout << "Enter child of " << parent_val << " (-1 for null): ";
    }

    std::cin >> x;

    if (x == -1) {
        return nullptr;
    }

    // Use std::make_unique for safe and efficient allocation.
    auto temp = std::make_unique<Node>(x);
    temp->left = createBinaryTree(x);
    temp->right = createBinaryTree(x);

    return temp;
}

/**
 * @brief Performs an in-order traversal of the binary tree and prints node values.
 *
 * In-order traversal visits the left subtree, then the root, then the right subtree.
 * The function takes a const pointer to prevent modification of the tree data.
 *
 * @param root A pointer to the root of the subtree to traverse.
 */
void inorderTraversal(const Node* root) {
    if (!root) {
        return;
    }
    inorderTraversal(root->left.get());
    std::cout << root->data << " ";
    inorderTraversal(root->right.get());
}

int main() {
    std::cout << "Note: Enter -1 to represent a null node." << std::endl;
    // auto is used for cleaner code when the type is long.
    auto root = createBinaryTree();

    std::cout << "In-order Traversal: ";
    // Use .get() to pass the raw pointer for non-owning functions.
    inorderTraversal(root.get());
    std::cout << std::endl;

    // The unique_ptr 'root' automatically deallocates the entire tree when it goes out of scope.
    return 0;
}