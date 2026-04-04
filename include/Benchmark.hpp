#ifndef BENCHMARK_HPP
#define BENCHMARK_HPP

#include <iostream>
#include <chrono>
#include "Parameters.hpp"
#include "DataGenerator.hpp"
#include "Sorting.hpp"

#include "DynamicArray.hpp"
#include "SinglyLinkedList.hpp"
#include "DoublyLinkedList.hpp"

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

    inline ShellGap getShellGap() {
        switch (Parameters::shellParameter) {
            case Parameters::ShellParameters::option1: return ShellGap::ORIGINAL;
            case Parameters::ShellParameters::option2: return ShellGap::KNUTH;
            case Parameters::ShellParameters::option3:
            case Parameters::ShellParameters::option4:
            default:                                   return ShellGap::KNUTH;
        }
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
        else {
            std::cerr << "\n[!] Benchmark does not support this algorithm yet!\n";
            return 0.0;
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

            if (Parameters::structure == Parameters::Structures::array) {
                DynamicArray<T> arr;
                for (int j = 0; j < Parameters::structureSize; ++j) arr.append(DataGenerator::generateRandom<T>());
                iterationTime = executeSortingAlgorithm(arr);
            }
            else if (Parameters::structure == Parameters::Structures::singleList) {
                SinglyLinkedList<T> sList;
                for (int j = 0; j < Parameters::structureSize; ++j) sList.append(DataGenerator::generateRandom<T>());
                iterationTime = executeSortingAlgorithm(sList);
            }
            else if (Parameters::structure == Parameters::Structures::doubleList) {
                DoublyLinkedList<T> dList;
                for (int j = 0; j < Parameters::structureSize; ++j) dList.append(DataGenerator::generateRandom<T>());
                iterationTime = executeSortingAlgorithm(dList);
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
    }

    inline void execute() {
        if (Parameters::dataType == Parameters::DataTypes::typeInt) runSortingTests<int>();
        else if (Parameters::dataType == Parameters::DataTypes::typeFloat) runSortingTests<float>();
        else if (Parameters::dataType == Parameters::DataTypes::typeChar) runSortingTests<char>();
        else std::cerr << "This data type in not supported yet!\n";
    }
}

#endif // BENCHMARK_HPP