#ifndef SORTING_HPP
#define SORTING_HPP

#include <vector>

template<typename T>
void insertionSort(std::vector<T> &arr);

template<typename T>
void quickSort(std::vector<T> &arr, int first, int last);

void countingSort(std::vector<int> &arr);

template<typename T>
void MergeSort(std::vector<T> &arr, int first, int last);

#endif
