// ============================================================================
// SORTING ALGORITHMS FOR DYNAMIC ARRAY
// ============================================================================
// Three sorting algorithms are implemented:
// 1. Bubble Sort - Simple but O(n²) time complexity
// 2. Quick Sort  - Efficient O(n log n) average, uses partitioning
// 3. Merge Sort  - Stable O(n log n), uses divide and conquer
//
// COMPARISON: Array vs LinkedList Sorting
// ┌──────────────┬────────────────────┬────────────────────┬─────────────┐
// │ Algorithm    │ Array Program      │ LinkedList Program  │ Complexity  │
// ├──────────────┼────────────────────┼────────────────────┼─────────────┤
// │ Bubble Sort │ Direct swap        │ operator[] access   │ O(n²)       │
// │ Quick Sort  │ In-place partition │ Temp array sort    │ O(n log n)  │
// │ Merge Sort  │ In-place merge     │ Temp array sort    │ O(n log n)  │
// └──────────────┴────────────────────┴────────────────────┴─────────────┘
// ============================================================================

#include "Sorting.h"
#include <iostream>
#include <cstring>
using namespace std;


// ----------------------------------------------------------------------------
// swap(): Utility function to swap two Record objects
// - Uses temporary variable to hold one record during swap
//
// CODE:    Record temp = a; a = b; b = temp;
// OUTPUT:  Two records exchange positions in the array
// ----------------------------------------------------------------------------
void Sorting::swap(Record& a, Record& b) {
    Record temp = a;
    a = b;
    b = temp;
}


// ============================================================================
// BUBBLE SORT IMPLEMENTATION
// ============================================================================
// How it works:
// - Compares adjacent elements and swaps if they're in wrong order
// - Repeats until no more swaps needed (array is sorted)
// - Largest elements "bubble" to the end each pass
//
// TIME COMPLEXITY:  O(n²) - worst, average, best case
// SPACE COMPLEXITY: O(1)  - in-place sorting
//
// CODE vs OUTPUT EXAMPLE:
// Before: [Age: 25, Age: 18, Age: 30] → After: [Age: 18, Age: 25, Age: 30]
// ┌────────────────────────────────────────────────────────────────────────┐
// │ Pass 1: Compare 25 & 18  → swap → [18, 25, 30]                       │
// │ Pass 1: Compare 25 & 30  → no swap → [18, 25, 30]                    │
// │ Pass 2: Compare 18 & 25  → no swap → [18, 25, 30] (sorted)          │
// └────────────────────────────────────────────────────────────────────────┘
// ============================================================================

void Sorting::bubbleSortByAgeHelper(Record* arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j].age > arr[j + 1].age) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

long long Sorting::bubbleSortByAge(DynamicArray& arr) {
    auto start = chrono::high_resolution_clock::now();
    
    bubbleSortByAgeHelper(arr.getData(), arr.getSize());
    
    auto end = chrono::high_resolution_clock::now();
    return chrono::duration_cast<chrono::milliseconds>(end - start).count();
}


void Sorting::bubbleSortByDistanceHelper(Record* arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j].dailyDistance > arr[j + 1].dailyDistance) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

long long Sorting::bubbleSortByDistance(DynamicArray& arr) {
    auto start = chrono::high_resolution_clock::now();
    
    bubbleSortByDistanceHelper(arr.getData(), arr.getSize());
    
    auto end = chrono::high_resolution_clock::now();
    return chrono::duration_cast<chrono::milliseconds>(end - start).count();
}


void Sorting::bubbleSortByEmissionHelper(Record* arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j].calculateMonthlyEmission() > arr[j + 1].calculateMonthlyEmission()) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// Bubble Sort by Distance
// Sorts records by daily distance in ascending order
// TIME: O(n²) | SPACE: O(1) | STABILITY: Stable
long long Sorting::bubbleSortByDistance(DynamicArray& arr) {
    auto start = chrono::high_resolution_clock::now();
    
    bubbleSortByDistanceHelper(arr.getData(), arr.getSize());
    
    auto end = chrono::high_resolution_clock::now();
    return chrono::duration_cast<chrono::milliseconds>(end - start).count();
}

// Bubble Sort by Carbon Emission
// Sorts records by monthly carbon emission (calculateMonthlyEmission()) in ascending order
// TIME: O(n²) | SPACE: O(1) | STABILITY: Stable
long long Sorting::bubbleSortByEmission(DynamicArray& arr) {
    auto start = chrono::high_resolution_clock::now();
    
    bubbleSortByEmissionHelper(arr.getData(), arr.getSize());
    
    auto end = chrono::high_resolution_clock::now();
    return chrono::duration_cast<chrono::milliseconds>(end - start).count();
}


// ============================================================================
// QUICK SORT IMPLEMENTATION
// ============================================================================
// How it works:
// - Selects a pivot element (last element in our implementation)
// - Partitions array: elements < pivot on left, elements > pivot on right
// - Recursively sorts left and right partitions
//
// TIME COMPLEXITY:  O(n log n) average, O(n²) worst case
// SPACE COMPLEXITY: O(log n) for recursion stack
//
// CODE vs OUTPUT EXAMPLE:
// Input:  [30, 10, 50, 20, 40]  pivot = 40
// Output: [30, 10, 20] [40] [50]
//         ↓          ↓      ↓
//        <40        =40    >40
// ┌────────────────────────────────────────────────────────────────────────┐
// │ partition(): All elements < 40 go left, > 40 go right                 │
// │ Result: [30, 10, 20, 40, 50] - 40 is in correct sorted position      │
// └────────────────────────────────────────────────────────────────────────┘
// ============================================================================

int Sorting::partitionByAge(Record* arr, int low, int high) {
    Record pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j].age < pivot.age) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void Sorting::quickSortByAgeHelper(Record* arr, int low, int high) {
    if (low < high) {
        int pi = partitionByAge(arr, low, high);
        quickSortByAgeHelper(arr, low, pi - 1);
        quickSortByAgeHelper(arr, pi + 1, high);
    }
}

// Quick Sort by Age
// Sorts records by age in ascending order using divide-and-conquer with partitioning
// TIME: O(n log n) avg, O(n²) worst | SPACE: O(log n) recursion | STABILITY: Unstable
long long Sorting::quickSortByAge(DynamicArray& arr) {
    auto start = chrono::high_resolution_clock::now();
    
    quickSortByAgeHelper(arr.getData(), 0, arr.getSize() - 1);
    
    auto end = chrono::high_resolution_clock::now();
    return chrono::duration_cast<chrono::milliseconds>(end - start).count();
}


int Sorting::partitionByDistance(Record* arr, int low, int high) {
    Record pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j].dailyDistance < pivot.dailyDistance) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void Sorting::quickSortByDistanceHelper(Record* arr, int low, int high) {
    if (low < high) {
        int pi = partitionByDistance(arr, low, high);
        quickSortByDistanceHelper(arr, low, pi - 1);
        quickSortByDistanceHelper(arr, pi + 1, high);
    }
}

// Quick Sort by Daily Distance
// Sorts records by daily distance in ascending order using divide-and-conquer with partitioning
// TIME: O(n log n) avg, O(n²) worst | SPACE: O(log n) recursion | STABILITY: Unstable
long long Sorting::quickSortByDistance(DynamicArray& arr) {
    auto start = chrono::high_resolution_clock::now();
    
    quickSortByDistanceHelper(arr.getData(), 0, arr.getSize() - 1);
    
    auto end = chrono::high_resolution_clock::now();
    return chrono::duration_cast<chrono::milliseconds>(end - start).count();
}


int Sorting::partitionByEmission(Record* arr, int low, int high) {
    Record pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j].calculateMonthlyEmission() < pivot.calculateMonthlyEmission()) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void Sorting::quickSortByEmissionHelper(Record* arr, int low, int high) {
    if (low < high) {
        int pi = partitionByEmission(arr, low, high);
        quickSortByEmissionHelper(arr, low, pi - 1);
        quickSortByEmissionHelper(arr, pi + 1, high);
    }
}

// Quick Sort by Carbon Emission
// Sorts records by monthly carbon emission in ascending order using divide-and-conquer with partitioning
// TIME: O(n log n) avg, O(n²) worst | SPACE: O(log n) recursion | STABILITY: Unstable
long long Sorting::quickSortByEmission(DynamicArray& arr) {
    auto start = chrono::high_resolution_clock::now();
    
    quickSortByEmissionHelper(arr.getData(), 0, arr.getSize() - 1);
    
    auto end = chrono::high_resolution_clock::now();
    return chrono::duration_cast<chrono::milliseconds>(end - start).count();
}


// ============================================================================
// MERGE SORT IMPLEMENTATION
// ============================================================================
// How it works:
// - Divides array into halves recursively until single elements
// - Merges sorted halves back together in correct order
// - Guaranteed O(n log n) performance
//
// TIME COMPLEXITY:  O(n log n) - all cases
// SPACE COMPLEXITY: O(n) - requires temporary arrays for merging
// STABILITY:        Stable sort - preserves order of equal elements
// ============================================================================

void Sorting::mergeByAge(Record* arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    Record* leftArr = new Record[n1];
    Record* rightArr = new Record[n2];

    for (int i = 0; i < n1; i++)
        leftArr[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        rightArr[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (leftArr[i].age <= rightArr[j].age) {
            arr[k++] = leftArr[i++];
        } else {
            arr[k++] = rightArr[j++];
        }
    }

    while (i < n1) {
        arr[k++] = leftArr[i++];
    }

    while (j < n2) {
        arr[k++] = rightArr[j++];
    }

    delete[] leftArr;
    delete[] rightArr;
}

void Sorting::mergeSortByAgeHelper(Record* arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSortByAgeHelper(arr, left, mid);
        mergeSortByAgeHelper(arr, mid + 1, right);
        mergeByAge(arr, left, mid, right);
    }
}

// Merge Sort by Age
// Sorts records by age in ascending order using divide-and-conquer with stable merging
// TIME: O(n log n) all cases | SPACE: O(n) temporary | STABILITY: Stable
long long Sorting::mergeSortByAge(DynamicArray& arr) {
    auto start = chrono::high_resolution_clock::now();
    
    mergeSortByAgeHelper(arr.getData(), 0, arr.getSize() - 1);
    
    auto end = chrono::high_resolution_clock::now();
    return chrono::duration_cast<chrono::milliseconds>(end - start).count();
}


void Sorting::mergeByDistance(Record* arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    Record* leftArr = new Record[n1];
    Record* rightArr = new Record[n2];

    for (int i = 0; i < n1; i++)
        leftArr[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        rightArr[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (leftArr[i].dailyDistance <= rightArr[j].dailyDistance) {
            arr[k++] = leftArr[i++];
        } else {
            arr[k++] = rightArr[j++];
        }
    }

    while (i < n1) {
        arr[k++] = leftArr[i++];
    }

    while (j < n2) {
        arr[k++] = rightArr[j++];
    }

    delete[] leftArr;
    delete[] rightArr;
}

void Sorting::mergeSortByDistanceHelper(Record* arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSortByDistanceHelper(arr, left, mid);
        mergeSortByDistanceHelper(arr, mid + 1, right);
        mergeByDistance(arr, left, mid, right);
    }
}

// Merge Sort by Daily Distance
// Sorts records by daily distance in ascending order using divide-and-conquer with stable merging
// TIME: O(n log n) all cases | SPACE: O(n) temporary | STABILITY: Stable
long long Sorting::mergeSortByDistance(DynamicArray& arr) {
    auto start = chrono::high_resolution_clock::now();
    
    mergeSortByDistanceHelper(arr.getData(), 0, arr.getSize() - 1);
    
    auto end = chrono::high_resolution_clock::now();
    return chrono::duration_cast<chrono::milliseconds>(end - start).count();
}


void Sorting::mergeByEmission(Record* arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    Record* leftArr = new Record[n1];
    Record* rightArr = new Record[n2];

    for (int i = 0; i < n1; i++)
        leftArr[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        rightArr[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (leftArr[i].calculateMonthlyEmission() <= rightArr[j].calculateMonthlyEmission()) {
            arr[k++] = leftArr[i++];
        } else {
            arr[k++] = rightArr[j++];
        }
    }

    while (i < n1) {
        arr[k++] = leftArr[i++];
    }

    while (j < n2) {
        arr[k++] = rightArr[j++];
    }

    delete[] leftArr;
    delete[] rightArr;
}

void Sorting::mergeSortByEmissionHelper(Record* arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSortByEmissionHelper(arr, left, mid);
        mergeSortByEmissionHelper(arr, mid + 1, right);
        mergeByEmission(arr, left, mid, right);
    }
}

// Merge Sort by Carbon Emission
// Sorts records by monthly carbon emission in ascending order using divide-and-conquer with stable merging
// TIME: O(n log n) all cases | SPACE: O(n) temporary | STABILITY: Stable
long long Sorting::mergeSortByEmission(DynamicArray& arr) {
    auto start = chrono::high_resolution_clock::now();
    
    mergeSortByEmissionHelper(arr.getData(), 0, arr.getSize() - 1);
    
    auto end = chrono::high_resolution_clock::now();
    return chrono::duration_cast<chrono::milliseconds>(end - start).count();
}
