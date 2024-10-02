#include <iostream>
#include "RadixSort.h"

int main() {
    std::vector<int> arr = {1111, 711, 12, 401, 18, 360, 999, 365, 2024};

    RadixSort radixSort;
    radixSort.sort(arr);

    std::cout << "Sorted array: \n";
    for (int num : arr)
        std::cout << num << " ";
    std::cout << std::endl;

    return 0;
}

