#ifndef SORTINGALGORITHMS_QUICKSORT_HPP
#define SORTINGALGORITHMS_QUICKSORT_HPP

#include <vector>

template <typename T>
using Iterator = typename std::vector<T>::iterator;

/**
 * Partition the range of values into two parts, with the left part holding the values less than a pivot value, and the
 * right part holding the values greater than the pivot value. Return an iterator to the value next of the pivot which
 * separates the two parts.
 * @tparam T The type of values in the vector iterated by first
 * @param first An iterator to the beginning of the vector to get partitioned
 * @param last An iterator past the end of the vector to get partitioned
 */
template<typename T>
Iterator<T> partition(Iterator<T> first, Iterator<T> last) {
    auto prev_last = std::prev(last);
    auto pivot = *prev_last;

    auto place_here = first;
    auto cursor = first;
    while (cursor != prev_last) {
        if (*cursor < pivot) {
            std::swap(*cursor, *place_here);
            std::advance(place_here, 1);
        }
        std::advance(cursor, 1);
    }

    std::swap(*place_here, *prev_last);

    return std::next(place_here);
}

/**
 * Sort the values in the range [first, last) in ascending order using the Quick Sort algorithm with the Lomuto
 * partition scheme
 * Note: The performance can improve by using the Hoare partition scheme and a better way to select the pivot than
 *       always selecting the last element in the vector.
 * @tparam T The type of values in the vector iterated by first
 * @param first An iterator to the beginning of the vector to get sorted
 * @param last An iterator past the end of the vector to get sorted
 */
template<typename T>
void quick_sort(Iterator<T> first, Iterator<T> last) {
    if (std::distance(first, last) > 1) {
        // p is an iterator to the element AFTER the pivot value
        auto p = partition<T>(first, last);
        // p will not participate in any further partition
        quick_sort<T>(first, std::prev(p));
        quick_sort<T>(p, last);
    }
}

#endif
