#ifndef SORTINGALGORITHMS_VECTOR_HELPERS_HPP
#define SORTINGALGORITHMS_VECTOR_HELPERS_HPP

#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

/**
 * Generate a vector of ints of size num_nums, in the range [min_val, max_val]
 * @param num_nums The number of values in the returned vector
 * @param min_val The minimum value in the returned vector
 * @param max_val The maximum value in the returned vector
 * @return The vector containing num_nums uniformly distributed random values in the range [min_val, max_val]
 */
template<typename T>
typename std::enable_if<std::is_integral<T>::value, std::vector<T>>::type
generate_random_vector(size_t num_nums, T min_val, T max_val) {
    // create the random device, the generator and the distribution
    std::random_device dev;
    std::mt19937 gen(dev());
    std::uniform_int_distribution<T> dist(min_val, max_val);

    // fill the vector with the random values
    std::vector<T> nums(num_nums);
    for (auto &num : nums) {
        num = dist(gen);
    }

    return nums;
}

/**
 * Print the values stored in a vector
 * @tparam T The type of values stored in the vector
 * @param stream The output stream where the values will be printed
 * @param vec The vector whose values will get printed
 * @return The output stream where the values will have been printed
 */
template<typename T>
std::ostream &operator<<(std::ostream &stream, const std::vector<T> &vec) {
    for (auto const &item : vec) {
        stream << item << " ";
    }
    // delete the last space and enter a new line instead
    stream << "\b\n";
    return stream;
}

/**
 * Check if two vectors contain the same values and in the same order
 * @tparam T The type of values in the vectors
 * @param a The first vector
 * @param b The second vector
 * @return true if the contents are the same, else false
 */
template<typename T>
bool operator==(std::vector<T> const &a, std::vector<T> const &b) {
    // if the vectors have different sizes, they are different
    if (a.size() != b.size()) {
        return false;
    }

    // check the values in the vectors one by one
    for (auto it_a = std::begin(a), it_b = std::begin(b); it_a != std::end(a); ++it_a, ++it_b) {
        // if any pair of values differs, return false
        if (*it_a != *it_b) {
            return false;
        }
    }

    // if all values were equal return true
    return true;
}

/**
 * Check if two vectors don't contain the same values and in the same order
 * @tparam T The type of values in the vectors
 * @param a The first vector
 * @param b The second vector
 * @return true if the contents differ, else false
 */
template<typename T>
bool operator!=(const std::vector<T> &a, const std::vector<T> &b) {
    return !(a == b);
}

#endif
