#ifndef SORTINGALGORITHMS_COUNTINGSORT_HPP
#define SORTINGALGORITHMS_COUNTINGSORT_HPP

#include <vector>
#include <algorithm>
#include <thread>
#include <future>

template <typename T>
using Iterator = typename std::vector<T>::iterator;

/**
 * Find the number of occurrences for each value in the vector, and store it into value - min_val. There are totally max_val - min_val + 1 counts.
 * @tparam T The type of values in the vector
 * @param first An iterator to the first element in the vector
 * @param last An iterator to the last element in the vector
 * @param min_val The minimum value in the vector
 * @param max_val The maximum value in the vector
 * @return A vector containing the occurrences for each value in the iterated vector
 */
template<typename T>
std::vector<size_t>
count_values(Iterator<T> first, Iterator<T> last, T min_val, T max_val) {
    size_t max_val_range = max_val - min_val + 1;
    std::vector<size_t> counts(max_val_range, 0);

    for (; first != last; ++first) {
        ++counts[*first - min_val];
    }

    return counts;
}

/**
 * Template specialization of Counting Sort for integer types
 * Note: There can be an implementation for non-integer types, if there exists a mapping from the input type to an
 * integer. std::hash() does that, but the interval of the returned value is huge so it can't be used
 * @param nums The vector of numbers to sort
 */
template<typename T>
typename std::enable_if<std::is_integral<T>::value>::type
counting_sort(Iterator<T> first, Iterator<T> last) {
    if (std::distance(first, last) < 2) {
        return;
    }

    auto min_max = std::minmax_element(first, last);
    T min_val = *min_max.first;
    T max_val = *min_max.second;

    auto counts = count_values<T>(first, last, min_val, max_val);

    auto it = first;
    for (size_t i = 0; i < counts.size(); ++i) {
        std::fill_n(it, counts[i], i + min_val);
        std::advance(it, counts[i]);
    }
}

/**
 * Template specialization of Parallel Counting Sort for integer types
 * Note: The performance depends on the range of values in nums. If the range is large enough, the cost for creating the
 * vector containing the counts, balances the value of parallel counting
 * @param nums The vector of numbers to sort
 */
template<typename T>
typename std::enable_if<std::is_integral<T>::value>::type
parallel_counting_sort(Iterator<T> first, Iterator<T> last) {
    auto size = std::distance(first, last);
    if (size < 2) {
        return;
    }

    auto min_max = std::minmax_element(first, last);
    T min_val = *min_max.first;
    T max_val = *min_max.second;

    // get the number of hardware threads
    auto const num_threads = std::thread::hardware_concurrency();
    // compute the block size for each thread
    auto const block_size = size / num_threads;
    // keep the futures in a vector
    std::vector<std::future<std::vector<size_t>>> futures(num_threads);

    // split the nums into equal blocks and count the values in each block in each thread
    for (unsigned int i = 0; i < num_threads - 1; ++i) {
        futures[i] = std::async(
                std::launch::async,
                count_values<T>,
                std::next(first, i * block_size),
                std::next(first, (i + 1) * block_size),
                min_val,
                max_val);
    }
    futures[num_threads - 1] = std::async(
            std::launch::async,
            count_values<T>,
            std::next(first, (num_threads - 1) * block_size),
            last,
            min_val,
            max_val);

    // merge all vector counts into one
    auto counts = futures[0].get();
    for (unsigned int i = 1; i < num_threads; ++i) {
        auto extra_counts = futures[i].get();
        for (unsigned int c = 0; c < counts.size(); ++c) {
            counts[c] += extra_counts[c];
        }
    }

    // fill the beginning vector with the sorted values
    auto it = first;
    for (size_t i = 0; i < counts.size(); ++i) {
        std::fill_n(it, counts[i], i + min_val);
        std::advance(it, counts[i]);
    }
}

#endif
