#include "sorting.tpp"

#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

template<typename T>
std::ostream &operator<<(std::ostream &stream, const std::vector<T> &vec) {
    for (const auto &item : vec) {
        stream << item << " ";
    }
    stream << "\b\n";
    return stream;
}

template<typename T>
bool operator==(const std::vector<T> &a, const std::vector<T> &b) {
    if (a.size() != b.size()) {
        return false;
    }

    auto it_a = a.begin();
    auto it_b = b.begin();

    while (it_a != a.end()) {
        if (*it_a != *it_b) {
            return false;
        }

        ++it_a;
        ++it_b;
    }

    return true;
}

template<typename T>
bool operator!=(const std::vector<T> &a, const std::vector<T> &b) {
    return !(a == b);
}

int main() {
    const int NUM_NUMS = 100000;
    const int MIN_VAL = -1000, MAX_VAL = 1000;

    // fill a vector with NUM_NUMS random numbers in the range [MIN_VAL, MAX_VAL] that follow a uniform distribution
    std::random_device dev;
    std::mt19937 gen(dev());
    std::uniform_int_distribution<int> dist(MIN_VAL, MAX_VAL);
    std::vector<int> nums(NUM_NUMS);
    std::generate(nums.begin(), nums.end(), [&dist, &gen]() {
        return dist(gen);
    });

    std::vector<int> sorted(nums);
    std::sort(sorted.begin(), sorted.end());

    std::vector<int> nums_cpy;

    std::chrono::time_point<std::chrono::high_resolution_clock> start;
    std::chrono::time_point<std::chrono::high_resolution_clock> stop;

    std::cout << "Counting Sort: ";
    nums_cpy = nums;    // copy assignment
    start = std::chrono::high_resolution_clock::now();
    countingSort(nums_cpy);
    stop = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count() << "ms\n";
    if (nums_cpy != sorted) std::cout << "wrong sort!\n";

    std::cout << "Insertion Sort: ";
    nums_cpy = nums;    // copy assignment
    start = std::chrono::high_resolution_clock::now();
    insertionSort(nums_cpy);
    stop = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count() << "ms\n";
    if (nums_cpy != sorted) std::cout << "wrong sort!\n";

    std::cout << "QuickSort: ";
    nums_cpy = nums;    // copy assignment
    start = std::chrono::high_resolution_clock::now();
    quickSort(nums_cpy, 0, NUM_NUMS);
    stop = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count() << "ms\n";
    if (nums_cpy != sorted) std::cout << "wrong sort!\n";

    std::cout << "Merge Sort: ";
    nums_cpy = nums;    // copy assignment
    start = std::chrono::high_resolution_clock::now();
    MergeSort(nums_cpy, 0, NUM_NUMS);
    stop = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count() << "ms\n";
    if (nums_cpy != sorted) std::cout << "wrong sort!\n";

    return 0;
}
