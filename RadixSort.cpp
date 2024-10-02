#include "RadixSort.h"
#include <vector>
#include <algorithm>

// A utility function to get the maximum value in arr[]
int RadixSort::getMax(const std::vector<int>& arr) {
    return *std::max_element(arr.begin(), arr.end());
}

/*function to do counting sort of arr[] according to the digit represented by exp
uses "count" array to store the count of each digit 0-9
"output" array stores sorted numbers for this digit*/
void RadixSort::countingSort(std::vector<int>& arr, int exp) {
    int n = arr.size();
    std::vector<int> output(n); // output array
    int i, count[10] = {0};

    // Store count of occurrences in count[]
    for (i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;

    // Change count[i] so that count[i] now contains actual
    // position of this digit in output[]
    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];

    // Build the output array
    for (i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }

    // Copy the output array to arr[], so that arr[] now
    // contains sorted numbers according to current digit
    for (i = 0; i < n; i++)
        arr[i] = output[i];
}

// The main function to that sorts arr[] of size n using
// Radix Sort
void RadixSort::sort(std::vector<int>& arr) {
    // Find the maximum number to know number of digits
    int m = getMax(arr);

    // counting sort for every digit. instead
    // of passing digit number, exp is passed. exp is 10^i
    // i is current digit number
    for (int exp = 1; m / exp > 0; exp *= 10)
        countingSort(arr, exp);
}

