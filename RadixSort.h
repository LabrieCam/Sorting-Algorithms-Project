#ifndef RADIXSORT_H
#define RADIXSORT_H

#include <vector>

class RadixSort {
public:
    void sort(std::vector<int>& arr);

private:
    int getMax(const std::vector<int>& arr);
    void countingSort(std::vector<int>& arr, int exp);
};

#endif 
