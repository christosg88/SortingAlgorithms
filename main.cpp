#include "CountingSort.hpp"
#include "MergeSort.hpp"
#include "QuickSort.hpp"

#include "vector_helpers.hpp"
#include "timeit.hpp"

#include <iostream>
#include <vector>
#include <cassert>

int main() {
    auto nums = generate_random_vector<int>(10'000'000, -1'000, 1'000);

    auto sorted(nums);
    ti::ti cpp_sort_timer("std::sort");
    std::sort(sorted.begin(), sorted.end());
    cpp_sort_timer.finish();

    auto nums_cpy(nums);
    ti::ti counting_sort_timer("Counting Sort");
    counting_sort<int>(std::begin(nums_cpy), std::end(nums_cpy));
    counting_sort_timer.finish();
    assert(nums_cpy == sorted);

    nums_cpy = nums;
    ti::ti parallel_counting_sort_timer("Parallel Counting Sort");
    parallel_counting_sort<int>(std::begin(nums_cpy), std::end(nums_cpy));
    parallel_counting_sort_timer.finish();
    assert(nums_cpy == sorted);

    nums_cpy = nums;
    ti::ti merge_sort_timer("Merge Sort");
    merge_sort<int>(nums_cpy);
    merge_sort_timer.finish();
    assert(nums_cpy == sorted);

    nums_cpy = nums;
    ti::ti parallel_merge_sort_timer("Parallel Merge Sort");
    parallel_merge_sort<int>(nums_cpy);
    parallel_merge_sort_timer.finish();
    assert(nums_cpy == sorted);

    nums_cpy = nums;
    ti::ti quick_sort_timer("Quick Sort");
    quick_sort<int>(std::begin(nums_cpy), std::end(nums_cpy));
    quick_sort_timer.finish();
    assert(nums_cpy == sorted);

    return 0;
}
