#ifndef STACK_HPP
#define STACK_HPP

#include <iostream>

template <typename T>
class Stack {
private:
    struct Node {
        T data;
        Node* next;

        Node(T value) : data(value), next(nullptr) {}
    };

    Node* topNode;
    int size;

    void displayRecursive(Node* node) const {
        if (node == nullptr) {
            return;
        }
        displayRecursive(node->next);
        std::cout << node->data << " ";
    }

public:
    Stack() : topNode(nullptr), size(0) {}

    Stack(const Stack&) = delete;
    Stack& operator=(const Stack&) = delete;

    void push(const T& value) {
        Node* newNode = new Node(value);
        newNode->next = topNode;
        topNode = newNode;
        size++;
    }

    void pop() {
        if (empty()) {
            std::cerr << "Stack is empty!" << "\n";
            return;
        }
        Node* temp = topNode;
        topNode = topNode->next;
        delete temp;
        size--;
    }

    T& top() {
        if (empty()) {
            std::cerr << "Error: Stack is empty! Returning default value." << "\n";
            static T dummy_value{};
            return dummy_value;
        }
        return topNode->data;
    }

    [[nodiscard]] bool empty() const {
        return topNode == nullptr;
    }

    [[nodiscard]] int getSize() const {
        return size;
    }

    void display() const {
        displayRecursive(topNode);
        std::cout << "\n";
    }

    bool operator==(const Stack<T>& other) const {
        if (size != other.size) return false;

        Node* current1 = topNode;
        Node* current2 = other.topNode;
        while (current1 != nullptr && current2 != nullptr) {
            if (current1->data != current2->data) {
                return false;
            }
            current1 = current1->next;
            current2 = current2->next;
        }
        return true;
    }

    ~Stack() {
        while (!empty()) {
            pop();
        }
    }
};

#endif