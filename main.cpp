#include "sorting.tpp"

#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

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

    std::cout << "------------Counting Sort-------------" << '\n';
    nums_cpy = nums;    // copy assignment
    countingSort(nums_cpy);
    if (nums_cpy != sorted) std::cout << "wrong sort!\n";

    std::cout << "------------Insertion Sort------------" << '\n';
    nums_cpy = nums;    // copy assignment
    insertionSort(nums_cpy);
    if (nums_cpy != sorted) std::cout << "wrong sort!\n";

    std::cout << "------------QuickSort-----------------" << '\n';
    nums_cpy = nums;    // copy assignment
    quickSort(nums_cpy, 0, NUM_NUMS);
    if (nums_cpy != sorted) std::cout << "wrong sort!\n";

    std::cout << "------------Merge Sort----------------" << '\n';
    nums_cpy = nums;    // copy assignment
    MergeSort(nums_cpy, 0, NUM_NUMS);
    if (nums_cpy != sorted) std::cout << "wrong sort!\n";

    return 0;
}
