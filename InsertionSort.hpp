#ifndef SORTINGALGORITHMS_INSERTIONSORT_HPP
#define SORTINGALGORITHMS_INSERTIONSORT_HPP

#include <vector>

template <typename T>
using Iterator = typename std::vector<T>::iterator;

/**
 * Insertion sort iterates, consuming one input element each repetition, and growing a sorted output list. At each
 * iteration, insertion sort removes one element from the input data, finds the location it belongs within the sorted
 * list, and inserts it there. It repeats until no input elements remain.
 * @tparam T
 * @param first
 * @param last
 */
template <typename T>
void insertion_sort(Iterator<T> first, Iterator<T> last) {
    // an iterator to the element to get placed into the right place
    Iterator<T> cursor = std::next(first);
    while (cursor != last) {
        // the value of the element to get placed into the right place
        T val = *cursor;

        // the two values getting compared
        Iterator<T> r = cursor;
        Iterator<T> l = std::prev(r);
        while (r != first && *l > val) {
            // copy the value from l to r
            *r = *l;
            // decrement l and r
            r = l;
            --l;
        }
        // place the current value to the right place
        *r = val;

        ++cursor;
    }
}

#endif
