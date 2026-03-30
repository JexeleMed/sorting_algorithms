#ifndef DOUBLY_LINKED_LIST_HPP
#define DOUBLY_LINKED_LIST_HPP

#include <iostream>

template <typename T>
class DoublyLinkedList {
private:
    struct Node {
        T data;
        Node* next;
        Node* prev;

        Node(T value) : data(value), next(nullptr), prev(nullptr) {}
    };

    Node* head;
    Node* tail;
    int count;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr), count(0) {}

    DoublyLinkedList(const DoublyLinkedList&) = delete;
    DoublyLinkedList& operator=(const DoublyLinkedList&) = delete;

    void append(T value) {
        Node* newNode = new Node(value);
        if (!head) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        count++;
    }

    void removeLast() {
        if (!tail) return;

        if (head == tail) {
            delete head;
            head = tail = nullptr;
        } else {
            Node* temp = tail;
            tail = tail->prev;
            tail->next = nullptr;
            delete temp;
        }
        count--;
    }

    void displayForward() {
        Node* current = head;
        while (current) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << "\n";
    }

    void displayBackward() {
        Node* current = tail;
        while (current) {
            std::cout << current->data << " ";
            current = current->prev;
        }
        std::cout << "\n";
    }

    void remove(T value) {
        if (!head) return;

        Node* current = head;
        while (current && current->data != value) {
            current = current->next;
        }

        if (!current) return;

        if (head == tail && current == head) {
            delete head;
            head = tail = nullptr;
            count--;
            return;
        }

        if (current == head) {
            head = head->next;
            head->prev = nullptr;
            delete current;
            count--;
            return;
        }

        if (current == tail) {
            tail = tail->prev;
            tail->next = nullptr;
            delete current;
            count--;
            return;
        }

        current->prev->next = current->next;
        current->next->prev = current->prev;
        delete current;
        count--;
    }

    void removeAt(int position) {
        if (!head || position < 0) return;

        Node* current = head;
        int index = 0;

        while (current && index < position) {
            current = current->next;
            index++;
        }

        if (!current) return;

        if (head == tail && current == head) {
            delete head;
            head = tail = nullptr;
            count--;
            return;
        }

        if (current == head) {
            head = head->next;
            head->prev = nullptr;
            delete current;
            count--;
            return;
        }

        if (current == tail) {
            tail = tail->prev;
            tail->next = nullptr;
            delete current;
            count--;
            return;
        }

        current->prev->next = current->next;
        current->next->prev = current->prev;
        delete current;
        count--;
    }


    T& operator[](int index) {
        Node* current = head;
        for (int i = 0; i < index && current != nullptr; i++) {
            current = current->next;
        }
        return current->data;
    }

    [[nodiscard]] int getSize() const {
        return count;
    }

    ~DoublyLinkedList() {
        Node* current = head;
        while (current) {
            Node* nextNode = current->next;
            delete current;
            current = nextNode;
        }
    }
};

#endif