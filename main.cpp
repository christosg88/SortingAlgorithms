#include "sorting.tpp"

#include <iostream>
#include <vector>
#include <algorithm>

template<typename T>
std::ostream &operator<<(std::ostream &stream, std::vector<T> &vec) {
    for (const auto &item : vec) {
        stream << item << " ";
    }
    return stream;
}

int main() {
    std::cout << "------------Counting Sort-------------" << '\n';
    std::vector<int> arr_countS = {1, 4, 3, 5, 6, 2, 1, 2};
    int min = *std::min_element(std::begin(arr_countS), std::end(arr_countS));
    int max = *std::max_element(std::begin(arr_countS), std::end(arr_countS));
    std::cout << "Unsorted: = " << arr_countS << '\n';
    countingSort(arr_countS, min, max);
    std::cout << "Sorted:   = " << arr_countS << "\n\n";

    std::cout << "------------Insertion Sort------------" << '\n';
    std::vector<double> arr_insertionS = {1.0, 2.14, 4.3, 2.33, 5.67};
    std::cout << "Unsorted: = " << arr_insertionS << '\n';
    insertionSort(arr_insertionS);
    std::cout << "Sorted:   = " << arr_insertionS << "\n\n";

    std::cout << "------------QuickSort-----------------" << '\n';
    std::vector<int> arr_quickS = {5, 6, 7, 2, -1, 2, 1, 2};
    std::cout << "Unsorted: = " << arr_quickS << '\n';
    quickSort(arr_quickS, 0, arr_quickS.size());
    std::cout << "Sorted:   = " << arr_quickS << "\n\n";

    std::cout << "------------Merge Sort----------------" << '\n';
    std::vector<int> arr_mergeS = {124, 26, 47, 12, -12, 42, 51, 12};
    std::cout << "Unsorted: = " << arr_mergeS << '\n';
    MergeSort(arr_mergeS, 0, arr_mergeS.size());
    std::cout << "Sorted:   = " << arr_mergeS << "\n\n";

    return 0;
}
