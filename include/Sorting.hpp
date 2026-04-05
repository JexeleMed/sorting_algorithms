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
    using ValueType = std::remove_reference_t<decltype(arr[0])>;

    if constexpr (!std::is_arithmetic_v<ValueType>) {
        std::cerr << "\n[!] Bucket Sort is not supported for non-numeric types (e.g., std::string)!\n";
        return;
    }
    else {
        int n = arr.getSize();
        if (n <= 1) return;

        ValueType minVal = arr[0];
        ValueType maxVal = arr[0];

        for (int i = 1; i < n; ++i) {
            if (arr[i] < minVal) minVal = arr[i];
            if (arr[i] > maxVal) maxVal = arr[i];
        }

        if (minVal == maxVal) return;

        int numBuckets = n;
        auto* buckets = new DynamicArray<ValueType>[numBuckets];

        for (int i = 0; i < n; ++i) {
            double range = static_cast<double>(maxVal) - static_cast<double>(minVal);
            double normalized = (static_cast<double>(arr[i]) - static_cast<double>(minVal)) / range;
            int bucketIndex = static_cast<int>(normalized * (numBuckets - 1));
            buckets[bucketIndex].append(arr[i]);
        }

        for (int i = 0; i < numBuckets; ++i) {
            if (buckets[i].getSize() > 1) {
                shellSort(buckets[i], ShellGap::KNUTH);
            }
        }

        int currentIndex = 0;
        for (int i = 0; i < numBuckets; ++i) {
            for (int j = 0; j < buckets[i].getSize(); ++j) {
                arr[currentIndex] = buckets[i][j];
                currentIndex++;
            }
        }

        delete[] buckets;
    }
}


// ------- BUBBLE SORT -------
template <typename Container>
void bubbleSort(Container& arr) {
    int n = arr.getSize();
    if (n <= 1) return;

    for (int i = 0; i < n - 1; ++i) {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                auto temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

// ------- COCKTAIL SORT -------
template <typename Container>
void cocktailSort(Container& arr) {
    int n = arr.getSize();
    if (n <= 1) return;

    bool swapped = true;
    int start = 0;
    int end = n - 1;

    while (swapped) {
        swapped = false;

        for (int i = start; i < end; ++i) {
            if (arr[i] > arr[i + 1]) {
                auto temp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = temp;
                swapped = true;
            }
        }

        if (!swapped) break;

        swapped = false;
        end--;

        for (int i = end - 1; i >= start; --i) {
            if (arr[i] > arr[i + 1]) {
                auto temp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = temp;
                swapped = true;
            }
        }
        start++;
    }
}

// ------- INSERTION SORT -------
template <typename Container>
void insertionSort(Container& arr) {
    int n = arr.getSize();
    if (n <= 1) return;

    for (int i = 1; i < n; ++i) {
        auto key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

// ------- MERGE SORT -------
template <typename Container>
void merge(Container& arr, int left, int mid, int right) {
    using ValueType = std::remove_reference_t<decltype(arr[0])>;

    int n1 = mid - left + 1;
    int n2 = right - mid;

    DynamicArray<ValueType> L;
    DynamicArray<ValueType> R;

    for (int i = 0; i < n1; ++i) {
        L.append(arr[left + i]);
    }
    for (int j = 0; j < n2; ++j) {
        R.append(arr[mid + 1 + j]);
    }

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

template <typename Container>
void mergeSortRecursive(Container& arr, int left, int right) {
    if (left >= right) return;

    int mid = left + (right - left) / 2;
    mergeSortRecursive(arr, left, mid);
    mergeSortRecursive(arr, mid + 1, right);

    merge(arr, left, mid, right);
}

template <typename Container>
void mergeSort(Container& arr) {
    int n = arr.getSize();
    if (n <= 1) return;
    mergeSortRecursive(arr, 0, n - 1);
}

#endif