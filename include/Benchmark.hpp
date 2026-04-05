#ifndef BENCHMARK_HPP
#define BENCHMARK_HPP

#include <iostream>
#include <chrono>
#include <fstream>
#include "Parameters.hpp"
#include "DataGenerator.hpp"
#include "Sorting.hpp"

#include "DynamicArray.hpp"
#include "SinglyLinkedList.hpp"
#include "DoublyLinkedList.hpp"
#include "Stack.hpp"
#include "BinarySearchTree.hpp"

namespace Benchmark {

    inline PivotStrategy getPivotStrategy() {
        switch (Parameters::pivot) {
            case Parameters::Pivots::left:   return PivotStrategy::LEFT;
            case Parameters::Pivots::right:  return PivotStrategy::RIGHT;
            case Parameters::Pivots::middle: return PivotStrategy::MIDDLE;
            case Parameters::Pivots::random: return PivotStrategy::RANDOM;
            default:                         return PivotStrategy::MIDDLE;
        }
    }

    inline DataGenerator::Distribution getDistribution() {
        switch (Parameters::distribution) {
            case Parameters::Distributions::ascending:  return DataGenerator::Distribution::ASCENDING;
            case Parameters::Distributions::descending: return DataGenerator::Distribution::DESCENDING;
            case Parameters::Distributions::halfSorted: return DataGenerator::Distribution::HALF_SORTED;
            case Parameters::Distributions::random:
            default:                                    return DataGenerator::Distribution::RANDOM;
        }
    }

    inline ShellGap getShellGap() {
        switch (Parameters::shellParameter) {
            case Parameters::ShellParameters::option1: return ShellGap::ORIGINAL;
            case Parameters::ShellParameters::option2: return ShellGap::KNUTH;
            case Parameters::ShellParameters::option3:
            case Parameters::ShellParameters::option4:
            default:                                   return ShellGap::KNUTH;
        }
    }


    inline std::string getAlgorithmName() {
        switch (Parameters::algorithm) {
            case Parameters::Algorithms::bubble:    return "BubbleSort";
            case Parameters::Algorithms::cocktail:  return "CocktailSort";
            case Parameters::Algorithms::merge:     return "MergeSort";
            case Parameters::Algorithms::insertion: return "InsertionSort";
            case Parameters::Algorithms::bucket:    return "BucketSort";
            case Parameters::Algorithms::quick:     return "QuickSort";
            case Parameters::Algorithms::shell:     return "ShellSort";
            default:                                return "Unknown";
        }
    }

    inline std::string getStructureName() {
        switch (Parameters::structure) {
            case Parameters::Structures::array:      return "Array";
            case Parameters::Structures::singleList: return "SinglyLinkedList";
            case Parameters::Structures::doubleList: return "DoublyLinkedList";
            case Parameters::Structures::stack:      return "Stack";
            case Parameters::Structures::binaryTree: return "BinarySearchTree";
            default:                                 return "Unknown";
        }
    }

    inline std::string getDistributionName() {
        switch (Parameters::distribution) {
            case Parameters::Distributions::random:     return "Random";
            case Parameters::Distributions::ascending:  return "Ascending";
            case Parameters::Distributions::descending: return "Descending";
            case Parameters::Distributions::halfSorted: return "HalfSorted";
            default:                                    return "Unknown";
        }
    }
    inline std::string getDataTypeName() {
        switch (Parameters::dataType) {
            case Parameters::DataTypes::typeInt:          return "Int";
            case Parameters::DataTypes::typeFloat:        return "Float";
            case Parameters::DataTypes::typeDouble:       return "Double";
            case Parameters::DataTypes::typeChar:         return "Char";
            case Parameters::DataTypes::typeString:       return "String";
            case Parameters::DataTypes::tyleUnsignedInt:  return "UnsignedInt";
            case Parameters::DataTypes::typeUnsignedLong: return "UnsignedLong";
            case Parameters::DataTypes::typeUnsignedChar: return "UnsignedChar";
            default:                                      return "Unknown";
        }
    }

    inline void saveResultsToCSV(double averageTimeMs) {
        if (Parameters::resultsFile.empty()) return;

        // Headers if empty
        bool needsHeader = false;
        std::ifstream testFile(Parameters::resultsFile);
        if (!testFile.is_open() || testFile.peek() == std::ifstream::traits_type::eof()) {
            needsHeader = true;
        }
        testFile.close();

        // Open file (append)
        std::ofstream outFile(Parameters::resultsFile, std::ios::app);
        if (!outFile.is_open()) {
            std::cerr << "Error: Could not open or create results file: " << Parameters::resultsFile << "\n";
            return;
        }

        if (needsHeader) {
            outFile << "Algorithm;Structure;DataType;Distribution;Pivot(Quick);Size;Iterations;AverageTime_ms\n";
        }

        // Save to file
        outFile << getAlgorithmName() << ";"
                << getStructureName() << ";"
                << getDataTypeName() << ";"
                << getDistributionName() << ";"
                << static_cast<int>(Parameters::pivot) << ";"
                << Parameters::structureSize << ";"
                << Parameters::iterations << ";"
                << averageTimeMs << "\n";

        outFile.close();
    }

    template <typename Container>
    double executeSortingAlgorithm(Container& container) {
        auto start = std::chrono::high_resolution_clock::now();

        if (Parameters::algorithm == Parameters::Algorithms::quick) {
            quickSort(container, getPivotStrategy());
        }
        else if (Parameters::algorithm == Parameters::Algorithms::shell) {
            shellSort(container, getShellGap());
        }
        else if (Parameters::algorithm == Parameters::Algorithms::bucket) {
            bucketSort(container);
        }
        else if (Parameters::algorithm == Parameters::Algorithms::bubble) {
            bubbleSort(container);
        }
        else if (Parameters::algorithm == Parameters::Algorithms::cocktail) {
            cocktailSort(container);
        }
        else if (Parameters::algorithm == Parameters::Algorithms::insertion) {
            insertionSort(container);
        }
        else if (Parameters::algorithm == Parameters::Algorithms::merge) {
            mergeSort(container);
        }
        else {
            std::cerr << "\n[!] Benchmark does not support this algorithm yet!\n";
            return 0.0;
        }

        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> elapsed = end - start;
        return elapsed.count();
    }

    template <typename T>
    double testStackSorting(int size, DataGenerator::Distribution dist) {
        DynamicArray<T> rawData;
        DataGenerator::populate<DynamicArray<T>, T>(rawData, size, dist);

        Stack<T> stack;
        for (int j = 0; j < rawData.getSize(); ++j) stack.push(rawData[j]);

        auto start = std::chrono::high_resolution_clock::now();

        DynamicArray<T> temp;
        while (!stack.empty()) {
            temp.append(stack.top());
            stack.pop();
        }

        if (Parameters::algorithm == Parameters::Algorithms::quick) quickSort(temp, getPivotStrategy());
        else if (Parameters::algorithm == Parameters::Algorithms::shell) shellSort(temp, getShellGap());
        else if (Parameters::algorithm == Parameters::Algorithms::bucket) bucketSort(temp);
        else if (Parameters::algorithm == Parameters::Algorithms::bubble) bubbleSort(temp);
        else if (Parameters::algorithm == Parameters::Algorithms::cocktail) cocktailSort(temp);
        else if (Parameters::algorithm == Parameters::Algorithms::insertion) insertionSort(temp);
        else if (Parameters::algorithm == Parameters::Algorithms::merge) mergeSort(temp);

        for (int j = temp.getSize() - 1; j >= 0; --j) {
            stack.push(temp[j]);
        }

        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> elapsed = end - start;
        return elapsed.count();
    }

    template <typename T>
    double testTreeSorting(int size, DataGenerator::Distribution dist) {
        DynamicArray<T> rawData;
        DataGenerator::populate<DynamicArray<T>, T>(rawData, size, dist);

        auto start = std::chrono::high_resolution_clock::now();

        BinarySearchTree<T> bst;
        for (int j = 0; j < rawData.getSize(); ++j) {
            bst.insert(rawData[j]);
        }

        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> elapsed = end - start;
        return elapsed.count();
    }

    template <typename T>
    void runSortingTests() {
        if (Parameters::structureSize <= 0 || Parameters::iterations <= 0) {
            std::cerr << "Error: Size of structure and number of iterations must be bigger than zero!\n";
            return;
        }

        double totalTimeMs = 0.0;
        std::cout << "Data generation. Starting benchmark (" << Parameters::iterations << " iterations)...\n";

        for (int i = 0; i < Parameters::iterations; ++i) {
            double iterationTime = 0.0;

            auto currentDist = getDistribution();
            if (Parameters::structure == Parameters::Structures::array) {
                DynamicArray<T> arr;
                DataGenerator::populate<DynamicArray<T>, T>(arr, Parameters::structureSize, currentDist);
                iterationTime = executeSortingAlgorithm(arr);
            }
            else if (Parameters::structure == Parameters::Structures::singleList) {
                SinglyLinkedList<T> sList;
                DataGenerator::populate<SinglyLinkedList<T>, T>(sList, Parameters::structureSize, currentDist);
                iterationTime = executeSortingAlgorithm(sList);
            }
            else if (Parameters::structure == Parameters::Structures::doubleList) {
                DoublyLinkedList<T> dList;
                DataGenerator::populate<DoublyLinkedList<T>, T>(dList, Parameters::structureSize, currentDist);
                iterationTime = executeSortingAlgorithm(dList);
            }
            else if (Parameters::structure == Parameters::Structures::stack) {
                iterationTime = testStackSorting<T>(Parameters::structureSize, currentDist);
            }
            else if (Parameters::structure == Parameters::Structures::binaryTree) {
                iterationTime = testTreeSorting<T>(Parameters::structureSize, currentDist);
            }
            else {
                std::cerr << "\n[!] This structure is not handled in benchmark!\n";
                return;
            }

            totalTimeMs += iterationTime;
        }

        double avgTime = totalTimeMs / Parameters::iterations;
        std::cout << "--------------------------------------\n";
        std::cout << "Sorting ended! Average time: " << avgTime << " ms\n";
        std::cout << "Total time: " << totalTimeMs << " ms\n";
        std::cout << "--------------------------------------\n";
        saveResultsToCSV(avgTime);
    }

    template <typename T>
    void runSingleFileTest() {
        if (Parameters::inputFile.empty() || Parameters::outputFile.empty()) {
            std::cerr << "Error: Input and output files must be specified for single file mode!\n";
            return;
        }

        // Open input file
        std::ifstream inFile(Parameters::inputFile);
        if (!inFile.is_open()) {
            std::cerr << "Error: Could not open input file: " << Parameters::inputFile << "\n";
            return;
        }

        int n;
        if (!(inFile >> n) || n <= 0) {
            std::cerr << "Error: Invalid or missing data size in input file!\n";
            inFile.close();
            return;
        }

        // Load data into appropriate structure
        DynamicArray<T> arr;
        SinglyLinkedList<T> sList;
        DoublyLinkedList<T> dList;

        for (int i = 0; i < n; ++i) {
            T value;
            if (!(inFile >> value)) {
                std::cerr << "Error: Not enough data in input file!\n";
                inFile.close();
                return;
            }

            if (Parameters::structure == Parameters::Structures::array) arr.append(value);
            else if (Parameters::structure == Parameters::Structures::singleList) sList.append(value);
            else if (Parameters::structure == Parameters::Structures::doubleList) dList.append(value);
            else {
                std::cerr << "Error: Unsupported structure for single file mode!\n";
                inFile.close();
                return;
            }
        }
        inFile.close();

        // Execute sorting
        std::cout << "Data loaded. Sorting started...\n";
        double sortTime = 0.0;

        if (Parameters::structure == Parameters::Structures::array) sortTime = executeSortingAlgorithm(arr);
        else if (Parameters::structure == Parameters::Structures::singleList) sortTime = executeSortingAlgorithm(sList);
        else if (Parameters::structure == Parameters::Structures::doubleList) sortTime = executeSortingAlgorithm(dList);

        std::cout << "Sorting finished in " << sortTime << " ms.\n";

        // Save to output file
        std::ofstream outFile(Parameters::outputFile);
        if (!outFile.is_open()) {
            std::cerr << "Error: Could not open output file: " << Parameters::outputFile << "\n";
            return;
        }

        outFile << n << "\n";
        for (int i = 0; i < n; ++i) {
            if (Parameters::structure == Parameters::Structures::array) outFile << arr[i] << " ";
            else if (Parameters::structure == Parameters::Structures::singleList) outFile << sList[i] << " ";
            else if (Parameters::structure == Parameters::Structures::doubleList) outFile << dList[i] << " ";
        }
        outFile << "\n";
        outFile.close();

        std::cout << "Results successfully saved to " << Parameters::outputFile << "\n";
    }

inline void execute() {
        if (Parameters::runMode == Parameters::RunModes::benchmark) {
            if (Parameters::dataType == Parameters::DataTypes::typeInt) runSortingTests<int>();
            else if (Parameters::dataType == Parameters::DataTypes::typeFloat) runSortingTests<float>();
            else if (Parameters::dataType == Parameters::DataTypes::typeDouble) runSortingTests<double>();
            else if (Parameters::dataType == Parameters::DataTypes::typeChar) runSortingTests<char>();
            else if (Parameters::dataType == Parameters::DataTypes::typeString) runSortingTests<std::string>();
            else if (Parameters::dataType == Parameters::DataTypes::tyleUnsignedInt) runSortingTests<unsigned int>();
            else if (Parameters::dataType == Parameters::DataTypes::typeUnsignedLong) runSortingTests<unsigned long>();
            else if (Parameters::dataType == Parameters::DataTypes::typeUnsignedChar) runSortingTests<unsigned char>();
            else std::cerr << "This data type in not supported yet!\n";
        }
        else if (Parameters::runMode == Parameters::RunModes::singleFile) {
            if (Parameters::dataType == Parameters::DataTypes::typeInt) runSingleFileTest<int>();
            else if (Parameters::dataType == Parameters::DataTypes::typeFloat) runSingleFileTest<float>();
            else if (Parameters::dataType == Parameters::DataTypes::typeDouble) runSingleFileTest<double>();
            else if (Parameters::dataType == Parameters::DataTypes::typeChar) runSingleFileTest<char>();
            else if (Parameters::dataType == Parameters::DataTypes::typeString) runSingleFileTest<std::string>();
            else if (Parameters::dataType == Parameters::DataTypes::tyleUnsignedInt) runSingleFileTest<unsigned int>();
            else if (Parameters::dataType == Parameters::DataTypes::typeUnsignedLong) runSingleFileTest<unsigned long>();
            else if (Parameters::dataType == Parameters::DataTypes::typeUnsignedChar) runSingleFileTest<unsigned char>();
            else std::cerr << "This data type in not supported yet!\n";
        }
    }
}

#endif // BENCHMARK_HPP