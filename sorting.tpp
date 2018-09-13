#include <vector>
#include <algorithm>

// Insertion Sort
template<typename T>
void insertionSort(std::vector<T> &arr) {
    for (int i = 1; i < arr.size(); ++i) {
        T ptrVal = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > ptrVal) {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = ptrVal;
    }
}

// QuickSort
template<typename T>
int partition(std::vector<T> &arr, int first, int last) {
    // pick last element as pivot
    int pivot = arr[last - 1];
    int wall = first;

    for (int i = first; i < last - 1; ++i) {
        if (arr[i] < pivot) {
            std::swap(arr[i], arr[wall]);
            ++wall;
        }
    }

    std::swap(arr[last - 1], arr[wall]);

    return wall;
}

template<typename T>
void quickSort(std::vector<T> &arr, int first, int last) {
    if (first < last - 1) {
        int pos_pivot = partition(arr, first, last);
        quickSort(arr, first, pos_pivot);
        quickSort(arr, pos_pivot + 1, last);
    }
}

// Counting Sort
void countingSort(std::vector<int> &arr) {
    auto minmax = std::minmax_element(std::begin(arr), std::end(arr));
    int min_val = *minmax.first, max_val = *minmax.second;

    std::vector<int> arr_copy(arr);
    int max_val_range = max_val - min_val + 1;
    std::vector<int> count(max_val_range, 0);

    for (const auto &item:arr) {
        ++count[item - min_val];
    }

    for (auto item = count.begin() + 1; item != count.end(); ++item) {
        *item += *(item - 1);
    }

    for (size_t i = 0; i < arr.size(); ++i) {
        arr[count[arr_copy[i] - min_val] - 1] = arr_copy[i];
        --count[arr_copy[i] - min_val];
    }
}

// Merge Sort
template<typename T>
void Merge(std::pair<int, int> left, std::pair<int, int> right, std::vector<T> &arr) {
    std::vector<T> arr_copy(arr.begin() + left.first, arr.begin() + right.second);
    int left_ptr = left.first;
    int right_ptr = right.first;
    int index = left.first;

    while (left_ptr < left.second && right_ptr < right.second) {
        if (arr_copy[left_ptr - left.first] > arr_copy[right_ptr - left.first]) {
            arr[index] = arr_copy[right_ptr - left.first];
            ++right_ptr;
        }
        else {
            arr[index] = arr_copy[left_ptr - left.first];
            ++left_ptr;
        }
        ++index;
    }

    // Copy the remaining elements
    for (int i = left_ptr; i < left.second; ++i) {
        arr[index] = arr_copy[i - left.first];
        ++index;
    }

    for (int i = right_ptr; i < right.second; ++i) {
        arr[index] = arr_copy[i - left.first];
        ++index;
    }
}

template<typename T>
void MergeSort(std::vector<T> &arr, int first, int last) {
    if (first < last - 1) {
        //  middle point to divide the array into two halves
        int half_limit = first + (last - first) / 2;
        MergeSort(arr, first, half_limit);
        MergeSort(arr, half_limit, last);

        std::pair<int, int> left{first, half_limit};
        std::pair<int, int> right{half_limit, last};

        Merge(left, right, arr);
    }
}
