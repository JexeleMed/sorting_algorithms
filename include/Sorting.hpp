#ifndef SORTING_HPP
#define SORTING_HPP

#include <type_traits>
#include <random>
#include "DynamicArray.hpp"

// ------- SHELL SORT -------
enum class ShellGap {
    ORIGINAL, // N/2, N/4, N/8...
    KNUTH     // 1, 4, 13, 40...
};

template <typename Container>
void shellSort(Container& arr, ShellGap gapType = ShellGap::ORIGINAL) {
    int n = arr.getSize();
    if (n <= 1) return;

    if (gapType == ShellGap::ORIGINAL) {
        for (int gap = n / 2; gap > 0; gap /= 2) {
            for (int i = gap; i < n; ++i) {
                auto temp = arr[i];
                int j;

                for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                    arr[j] = arr[j - gap];
                }
                arr[j] = temp;
            }
        }
    }
    else if (gapType == ShellGap::KNUTH) {
        int gap = 1;
        while (gap < n / 3) {
            gap = gap * 3 + 1;
        }

        while (gap > 0) {
            for (int i = gap; i < n; ++i) {
                auto temp = arr[i];
                int j;

                for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                    arr[j] = arr[j - gap];
                }
                arr[j] = temp;
            }
            gap /= 3;
        }
    }
}


// ------- QUICK SORT -------


enum class PivotStrategy {
    LEFT,
    RIGHT,
    MIDDLE,
    RANDOM
};

template <typename Container>
int partition(Container& arr, int low, int high, PivotStrategy strategy) {
    int pivotIndex;

    // Pivot choice
    switch (strategy) {
        case PivotStrategy::LEFT:
            pivotIndex = low;
            break;
        case PivotStrategy::RIGHT:
            pivotIndex = high;
            break;
        case PivotStrategy::MIDDLE:
            pivotIndex = low + (high - low) / 2;
            break;
        case PivotStrategy::RANDOM: {
            static std::random_device rd;
            static std::mt19937 gen(rd());
            std::uniform_int_distribution<int> dist(low, high);
            pivotIndex = dist(gen);
            break;
        }
        default:
            pivotIndex = high; // Fallback (Lomuto default)
            break;
    }

    // Lomuto setup. Switch position of the pivot to right
    auto tempPivot = arr[pivotIndex];
    arr[pivotIndex] = arr[high];
    arr[high] = tempPivot;

    auto pivotValue = arr[high];

    // Index of the smaller element
    int i = low - 1;

    for (int j = low; j < high; ++j) {
        // If current element is smaller than the pivot
        if (arr[j] < pivotValue) {
            i++;
            // Swap arr[i] and arr[j]
            auto temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    // Swap the pivot element with the element at i + 1
    auto tempFinal = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = tempFinal;

    // Return the partitioning index
    return i + 1;
}

// Recursive Quick Sort function
template <typename Container>
void quickSortRecursive(Container& arr, int low, int high, PivotStrategy strategy) {
    if (low < high) {
        int pi = partition(arr, low, high, strategy);

        quickSortRecursive(arr, low, pi - 1, strategy);
        quickSortRecursive(arr, pi + 1, high, strategy);
    }
}

// Public wrapper function to start Quick Sort (default RIGHT, because of Lomuto)
template <typename Container>
void quickSort(Container& arr, PivotStrategy strategy = PivotStrategy::RIGHT) {
    int n = arr.getSize();
    if (n <= 1) return;
    quickSortRecursive(arr, 0, n - 1, strategy);
}



// ------- BUCKET SORT -------
template <typename Container>
void bucketSort(Container& arr) {
    int n = arr.getSize();
    if (n <= 1) return;

    // Check the range
    using ValueType = std::remove_reference_t<decltype(arr[0])>;

    ValueType minVal = arr[0];
    ValueType maxVal = arr[0];

    for (int i = 1; i < n; ++i) {
        if (arr[i] < minVal) minVal = arr[i];
        if (arr[i] > maxVal) maxVal = arr[i];
    }

    // If elements are the same it's sorted
    if (minVal == maxVal) return;

    // Create dynamic buckets
    int numBuckets = n;
    auto* buckets = new DynamicArray<ValueType>[numBuckets];

    // Divide elements into the buckets
    for (int i = 0; i < n; ++i) {
        // Relative position of the element (from 0.0 to 1.0)
        double range = static_cast<double>(maxVal) - static_cast<double>(minVal);
        double normalized = (static_cast<double>(arr[i]) - static_cast<double>(minVal)) / range;

        // Multiply by (numBuckets - 1) to get the correct bucket index
        int bucketIndex = static_cast<int>(normalized * (numBuckets - 1));

        buckets[bucketIndex].append(arr[i]);
    }

    // Sort each individual bucket
    for (int i = 0; i < numBuckets; ++i) {
        if (buckets[i].getSize() > 1) {
            shellSort(buckets[i], ShellGap::KNUTH);
        }
    }

    // Gather elements into the original array
    int currentIndex = 0;
    for (int i = 0; i < numBuckets; ++i) {
        for (int j = 0; j < buckets[i].getSize(); ++j) {
            arr[currentIndex] = buckets[i][j];
            currentIndex++;
        }
    }

    delete[] buckets;
}

#endif