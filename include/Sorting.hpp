#ifndef SORTING_HPP
#define SORTING_HPP

#include <iostream>

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
            for (int i = gap; i < n; i++) {
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
            for (int i = gap; i < n; i++) {
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

#endif