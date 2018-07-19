#include <vector>
#include <algorithm>

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
int partition(std::vector<T> &arr, int first, int last) {
    int pivot = arr[last - 1];
    int wall = first;

    for (auto item = arr.begin() + first; item < arr.begin() + last - 1; ++item) {
        if (*item < pivot) {
            std::iter_swap(item, arr.begin() + wall);
            ++wall;
        }
    }

    std::iter_swap(arr.begin() + last - 1, arr.begin() + wall);

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
    int min_val, max_val;
    min_val = max_val = arr[0];
    for (const auto &val : arr) {
        if (val < min_val) {
            min_val = val;
        }
        else if (val > max_val) {
            max_val = val;
        }
    }

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
    int first;
    int last;
};

template<typename T>
void Merge(Segment left, Segment right, std::vector<T> &arr) {
    std::vector<int> arr_copy(arr);
    int left_ptr = left.first;
    int right_ptr = right.first;
    int index = left.first;

    while (left_ptr < left.last && right_ptr < right.last) {
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
    while (left_ptr < left.last) {
        arr[index] = arr_copy[left_ptr];
        left_ptr++;
        index++;
    }

    while (right_ptr < right.last) {
        arr[index] = arr_copy[right_ptr];
        right_ptr++;
        index++;
    }
}

template<typename T>
void MergeSort(std::vector<T> &arr, int first, int last) {
    if (first >= last - 1) {
        return;
    }
    else {
        int half_limit = (first + last) / 2;
        MergeSort(arr, first, half_limit);
        MergeSort(arr, half_limit, last);

        Segment left{first, half_limit};
        Segment right{half_limit, last};

        Merge(left, right, arr);
    }
}
