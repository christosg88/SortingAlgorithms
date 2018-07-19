#pragma once
#include <iostream>
#include <vector>

template<typename T>
void insertionSort(std::vector<T> &arr);

template<typename T>
void quickSort(std::vector<T> &arr, int start, int end);

void countingSort(std::vector<int> &arr, int min_val, int max_val);

template<typename T>
void MergeSort(std::vector<T> &arr, int start, int end);
