#ifndef BINARY_SEARCH_TREE_HPP
#define BINARY_SEARCH_TREE_HPP

#ifdef WIN32 // __linux__ __APPLE__

#elif __linux__

#endif
#include <iostream>

template <typename T>
class BinarySearchTree {
private:
    struct Node {
        T data;
        Node* left;
        Node* right;

        Node(T value) : data(value), left(nullptr), right(nullptr) {}
    };

    Node* root;
    int size;

    // Helper recursive function to insert a new value
    Node* insertRecursive(Node* current, T value) {
        if (current == nullptr) {
            return new Node(value);
        }

        if (value < current->data) {
            current->left = insertRecursive(current->left, value);
        }
        else {
            current->right = insertRecursive(current->right, value);
        }

        return current;
    }

    // Helper recursive function to print tree in order (sorted)
    void inorderRecursive(Node* current) const {
        if (current != nullptr) {
            inorderRecursive(current->left);
            std::cout << current->data << " ";
            inorderRecursive(current->right);
        }
    }

    // Helper recursive function to delete all nodes and prevent memory leaks
    void destroyRecursive(Node* current) {
        if (current != nullptr) {
            destroyRecursive(current->left);
            destroyRecursive(current->right);
            delete current; // Delete node after deleting its children
        }
    }

public:
    BinarySearchTree() : root(nullptr), size(0) {}

    // Prevent copy
    BinarySearchTree(const BinarySearchTree&) = delete;
    BinarySearchTree& operator=(const BinarySearchTree&) = delete;

    ~BinarySearchTree() {
        destroyRecursive(root);
    }

    // Public wrapper for inserting elements
    void insert(T value) {
        root = insertRecursive(root, value);
        size++;
    }

    // Public wrapper for displaying elements
    void displayInorder() const {
        inorderRecursive(root);
        std::cout << "\n";
    }

    [[nodiscard]] int getSize() const {
        return size;
    }
};

#endif