#include <iostream>
#include "DynamicArray.hpp"
#include "DoublyLinkedList.hpp"
#include "SinglyLinkedList.hpp"
#include "Stack.hpp"
#include "BinarySearchTree.hpp"
#include "Sorting.hpp"
#include "Parameters.hpp"

int main(int argc, char** argv) {
if (Parameters::readParameters(argc - 1, argv + 1) != 0) {
        std::cerr << "\nParsing error. Use -h or --help for help.\n";
        return -1;
    }

    // HELP
    if (Parameters::runMode == Parameters::RunModes::help) {
        Parameters::help();
        return 0;
    }

    // SINGLE FILE
    if (Parameters::runMode == Parameters::RunModes::singleFile) {
        std::cout << "\n=== SINGLE FILE ===\n";
        std::cout << "Input file: " << Parameters::inputFile << "\n";
        std::cout << "To be handled.\n";
    }

    // BENCHMARK
    if (Parameters::runMode == Parameters::RunModes::benchmark) {
        std::cout << "\n=== BENCHMARK ===\n";
        Parameters::printParameters();
        std::cout << "\n============================================\n";
        std::cout << "   RUNNING TESTS!    \n";
        std::cout << "============================================\n\n";

        std::cout << "--- TESTING DYNAMIC ARRAY ---\n";
        DynamicArray<int> arr;
        arr.append(10);
        arr.append(20);
        arr.append(30);
        arr.append(40);
        std::cout << "Array size: " << arr.getSize() << "\n";
        std::cout << "Array elements: ";
        arr.display();

        std::cout << "\n--- TESTING DOUBLY LINKED LIST ---\n";
        DoublyLinkedList<int> dll;
        dll.append(100);
        dll.append(200);
        dll.append(300);
        std::cout << "DLL size: " << dll.getSize() << "\n";
        std::cout << "DLL forward: ";
        dll.displayForward();
        std::cout << "DLL backward: ";
        dll.displayBackward();

        std::cout << "\n--- TESTING SINGLY LINKED LIST ---\n";
        SinglyLinkedList<int> sll;
        sll.append(1000);
        sll.append(2000);
        sll.append(3000);
        std::cout << "SLL size: " << sll.getSize() << "\n";
        std::cout << "SLL elements: ";
        sll.display();

        std::cout << "\n--- TESTING STACK ---\n";
        Stack<int> stack;
        stack.push(1);
        stack.push(2);
        stack.push(3);
        std::cout << "Stack size: " << stack.getSize() << "\n";
        std::cout << "Stack top element: " << stack.top() << "\n";
        std::cout << "Stack elements (top to bottom): ";
        stack.display();

        std::cout << "\n--- TESTING BINARY SEARCH TREE ---\n";
        BinarySearchTree<int> bst;
        bst.insert(50);
        bst.insert(30);
        bst.insert(70);
        bst.insert(20);
        bst.insert(40);
        std::cout << "BST size: " << bst.getSize() << "\n";
        std::cout << "BST inorder (should be sorted): ";
        bst.displayInorder();

        std::cout << "\nAll structures compiled and executed successfully!\n";

        std::cout << "\n--- TESTING SHELL SORT ---\n";
        DynamicArray<int> arr1;
        arr1.append(45);
        arr1.append(12);
        arr1.append(89);
        arr1.append(33);
        arr1.append(1);
        arr1.append(9);

        std::cout << "Before sorting: ";
        arr1.display();

        shellSort(arr1, ShellGap::KNUTH);

        std::cout << "After sorting:     ";
        arr1.display();

        std::cout << "\n--- TESTING QUICK SORT ---\n";
        DynamicArray<int> arr2;
        arr2.append(50);
        arr2.append(23);
        arr2.append(9);
        arr2.append(18);
        arr2.append(61);
        arr2.append(32);

        std::cout << "Before Quick Sort: ";
        arr2.display();

        quickSort(arr2, PivotStrategy::MIDDLE);

        std::cout << "After Quick Sort:    ";
        arr2.display();

        std::cout << "\n--- TESTING BUCKET SORT ---\n";
        DynamicArray<int> arr3;

        arr3.append(78);
        arr3.append(17);
        arr3.append(39);
        arr3.append(26);
        arr3.append(72);
        arr3.append(94);
        arr3.append(21);
        arr3.append(12);
        arr3.append(23);
        arr3.append(68);

        std::cout << "Before Bucket Sort: ";
        arr3.display();

        bucketSort(arr3);

        std::cout << "After Bucket Sort:    ";
        arr3.display();
    }

    return 0;
}