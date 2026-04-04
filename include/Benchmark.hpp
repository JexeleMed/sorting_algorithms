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