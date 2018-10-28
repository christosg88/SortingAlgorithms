#ifndef SORTINGALGORITHMS_MERGESORT_HPP
#define SORTINGALGORITHMS_MERGESORT_HPP

#include <vector>
#include <thread>

template <typename T>
using Iterator = typename std::vector<T>::iterator;

/**
 * Merge two sorted halves of an array, into another array, sorted
 * Note: we assume the two halves are stored in consecutive memory locations
 * @tparam T The type of values in the halves
 * @param first An iterator to the beginning of the first half
 * @param middle An iterator to the beginning of the second half
 * @param last An iterator to the end of the second half
 * @param aux_first An iterator to the beginning of the auxiliary vector where the merged vector will get stored
 */
template <typename T>
void merge(Iterator<T> first, Iterator<T> middle, Iterator<T> last, Iterator<T> aux_first) {
    auto left = first;
    auto right = middle;
    auto aux_last = std::next(aux_first, std::distance(first, last));

    while (aux_first != aux_last) {
        if (left != middle && (right == last || *left <= *right)) {
            *aux_first = *left;
            std::advance(left, 1);
        }
        else {
            *aux_first = *right;
            std::advance(right, 1);
        }
        std::advance(aux_first, 1);
    }
}

/**
 * Sort vec in ascending order using the Bottom Up Merge Sort algorithm
 * @tparam T The type of values in vec
 * @param vec The vector of values to get sorted
 */
template <typename T>
void merge_sort(std::vector<T> &vec) {
    // if the array is trivially sorted, return
    auto size = vec.size();
    if (size < 2) {
        return;
    }

    // create an auxiliary vector that will hold the merges for each two halves. This is faster than inplace merging but
    // costs in space
    std::vector<T> aux_vec(size);

    // start with sub-vectors of width 1 and double the width in each loop
    for (size_t width = 1; width < size; width *= 2) {
        // merge every two consecutive sub-vectors into the auxiliary vector
        for (size_t i = 0; i < size; i += 2 * width) {
            auto f = std::next(std::begin(vec), i);
            auto m = std::next(std::begin(vec), std::min(i + width, size));
            auto l = std::next(std::begin(vec), std::min(i + 2 * width, size));
            auto aux_f = std::next(std::begin(aux_vec), i);

            merge<T>(f, m, l, aux_f);
        }

        // swap the auxiliary vector with the original vector
        std::swap(vec, aux_vec);
    }
}

/**
 * Transforming function, in case not the whole vector needs to get sorted
 * @tparam T The type of values in the vector iterated by first
 * @param first An iterator to the beginning of the vector to get sorted
 * @param last An iterator to the end of the vector to get sorted
 */
template<typename T>
void merge_sort(Iterator<T> first, Iterator<T> last) {
    // create a temporary vector copying the values in the range [first, last)
    std::vector<T> vec_cpy(first, last);

    // sort the temporary vector
    merge_sort(vec_cpy);

    // swap the values from the sorted vector into the vector iterated by first
    std::swap_ranges(first, last, std::begin(vec_cpy));
}

/**
 * Sort vec in ascending order using a parallel version of Bottom Up Merge Sort algorithm, making use of all available
 * hardware threads
 * @tparam T The type of values in vec
 * @param vec The vector of values to get sorted
 */
template <typename T>
void parallel_merge_sort(std::vector<T> &vec) {
    // if the array is trivially sorted, return
    auto size = vec.size();
    if (size < 2) {
        return;
    }

    // get the number of hardware threads
    auto const num_threads = std::thread::hardware_concurrency();
    // compute the block size for each thread
    auto const block_size = size / num_threads;
    // keep the threads in a vector
    std::vector<std::thread> threads;

    // create the limits of each sub-vector to get sorted
    std::vector<std::pair<Iterator<T>, Iterator<T>>> limits;
    for (unsigned int i = 0; i < num_threads - 1; ++i) {
        limits.emplace_back(std::make_pair(std::next(std::begin(vec), i * block_size), std::next(std::begin(vec), (i + 1) * block_size)));
    }
    limits.emplace_back(std::make_pair(std::next(std::begin(vec), (num_threads - 1) * block_size), std::end(vec)));

    // sort each sub-vector using merge_sort
    for (auto &lim : limits) {
        threads.emplace_back([](Iterator<T> first, Iterator<T> last) {
            merge_sort<T>(first, last);
        }, lim.first, lim.second);
    }

    // join the spawned threads with the spawning thread
    for (auto &t : threads) {
        if (t.joinable()) {
            t.join();
        }
    }

    // create an auxiliary vector into which the num_threads sub-vectors will get merged
    std::vector<T> aux_vec(size);

    while (limits.size() > 1) {
        threads.clear();

        // create the limits of each new sub-vector to get merged
        std::vector<std::pair<Iterator<T>, Iterator<T>>> new_limits;
        // the limits of the first sub-vector
        auto lim_it = std::begin(limits);
        while (lim_it != std::end(limits)) {
            // the limits of the second sub-vector
            auto next_lim_it = std::next(lim_it);
            // the distance of the first sub-vector from the original vector
            auto first_dist = std::distance(std::begin(vec), lim_it->first);
            // the width of the new, merged sub-vector
            auto width = std::distance(lim_it->first, next_lim_it->second);

            // merge the two sub-vectors into the auxiliary vector, in a new thread
            threads.emplace_back(
                    [](Iterator<T> first, Iterator<T> middle, Iterator<T> last, Iterator<T> aux_first) {
                        merge<T>(first, middle, last, aux_first);
                    },
                    lim_it->first,
                    next_lim_it->first,
                    next_lim_it->second,
                    std::next(std::begin(aux_vec), first_dist));

            // push the limits of the merged sub-vector into new_limits
            new_limits.emplace_back(
                    std::make_pair(
                            std::next(std::begin(aux_vec), first_dist),
                            std::next(std::begin(aux_vec), first_dist + width)));

            // skip the second half
            std::advance(lim_it, 2);
        }

        // join the spawned threads with the spawning thread
        for (auto &t : threads) {
            if (t.joinable()) {
                t.join();
            }
        }

        // swap the auxiliary vector with the original vector
        std::swap(vec, aux_vec);

        // replace the old sub-vector limits with the new ones
        limits = std::move(new_limits);
    }
}

#endif
