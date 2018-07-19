#include <iostream>
#include <vector>

// Insertion Sort
template<typename T>
void insertionSort(std::vector<T> &arr) {
    for (int i = 1; i < arr.size(); ++i) {
        int ptrPos = i;
        double ptrVal = arr[ptrPos];

        for (int j = i - 1; j >= -1; --j) {
            if (arr[j] > ptrVal) {
                arr[ptrPos] = arr[j];
                --ptrPos;
            }
            else {
                arr[ptrPos] = ptrVal;
                break;
            }
        }
    }
}

// QuickSort
template<typename T>
int partition(std::vector<T> &arr, int start, int end) {
    int pivot = arr[end - 1];
    int wall = start;

    for (auto item = arr.begin() + start; item < arr.begin() + end - 1; ++item) {
        if (*item < pivot) {
            std::iter_swap(item, arr.begin() + wall);
            ++wall;
        }
    }

    std::iter_swap(arr.begin() + end - 1, arr.begin() + wall);

    return wall;
}

template<typename T>
void quickSort(std::vector<T> &arr, int start, int end) {
    if (start < end - 1) {
        int pos_pivot = partition(arr, start, end);
        quickSort(arr, start, pos_pivot);
        quickSort(arr, pos_pivot + 1, end);
    }
}

// Counting Sort
void countingSort(std::vector<int> &arr, int min_val, int max_val) {
    std::vector<int> copy_arr(arr);

    int max_val_range = max_val - min_val + 1;
    std::vector<int> count(max_val_range, 0);

    for (auto item:arr) {
        ++count[item - min_val];
    }

    for (auto item = count.begin() + 1; item != count.end(); ++item) {
        *item += *(item - 1);
    }

    for (int i = 0; i < arr.size(); ++i) {
        arr[count[copy_arr[i] - min_val] - 1] = copy_arr[i];
        --count[copy_arr[i] - min_val];
    }
}

// Merge Sort
struct Segment {
public:
    int start;
    int end;
};

template<typename T>
void Merge(Segment left, Segment right, std::vector<T> &arr) {
    std::vector<int> arr_copy(arr);
    int left_ptr = left.start;
    int right_ptr = right.start;
    int index = left.start;

    while (left_ptr < left.end && right_ptr < right.end) {
        if (arr_copy[left_ptr] > arr_copy[right_ptr]) {
            arr[index] = arr_copy[right_ptr];
            right_ptr++;
        }
        else {
            arr[index] = arr_copy[left_ptr];
            left_ptr++;
        }
        index++;
    }

    // Copy the remaining elements
    while (left_ptr < left.end) {
        arr[index] = arr_copy[left_ptr];
        left_ptr++;
        index++;
    }

    while (right_ptr < right.end) {
        arr[index] = arr_copy[right_ptr];
        right_ptr++;
        index++;
    }
}

template<typename T>
void MergeSort(std::vector<T> &arr, int start, int end) {
    if (start >= end - 1) {
        return;
    }
    else {
        int half_limit = (start + end) / 2;
        MergeSort(arr, start, half_limit);
        MergeSort(arr, half_limit, end);

        Segment left{start, half_limit};
        Segment right{half_limit, end};

        Merge(left, right, arr);
    }
}
