# Sorting Algorithms
Algorithms used to rearrange a given vector of elements in ascending order.
###Insertion Sort

###CountingSort
It is a sorting technique based on keys between a specific range. It is given the min and max value of the vector and then works by counting the number of objects having distinct key values. After calculates the position of each object in the output sequence. Counting sort can only be implemented on integers.

###QuickSort
QuickSort is a divide and conquer algorithm. It picks an element as pivot and partitions the given array around the picked pivot, here we pick the last element as pivot.

###MergeSort
Merge Sort is a divide and conquer algorithm. It divides input array in two halves, calls itself for the two halves and then merges the two sorted halves.

###Examples
```
------------Counting Sort-------------
Unsorted: = 1 4 3 5 6 2 1 2 
Sorted:   = 1 1 2 2 3 4 5 6 

------------Insertion Sort------------
Unsorted: = 1 2.14 4.3 2.33 5.67 
Sorted:   = 1 2.14 2.33 4.3 5.67 

------------QuickSort-----------------
Unsorted: = 5 6 7 2 -1 2 1 2 
Sorted:   = -1 1 2 2 2 5 6 7 

------------Merge Sort----------------
Unsorted: = 124 26 47 12 -12 42 51 12 
Sorted:   = -12 12 12 26 42 47 51 124 
```
