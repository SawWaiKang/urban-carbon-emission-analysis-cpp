// ============================================================================
// SORTING ALGORITHMS FOR SINGLY LINKED LIST
// ============================================================================
// Three sorting algorithms are implemented:
// 1. Bubble Sort - Simple but O(n²) time complexity
// 2. Quick Sort  - Efficient O(n log n) average, uses partitioning
// 3. Merge Sort  - Stable O(n log n), uses divide and conquer
//
// COMPARISON: LinkedList vs Array Sorting
// ┌──────────────┬────────────────────┬────────────────────┬─────────────┐
// │ Algorithm    │ LinkedList Program │ Array Program       │ Complexity  │
// ├──────────────┼────────────────────┼────────────────────┼─────────────┤
// │ Bubble Sort │ operator[] access  │ Direct swap         │ O(n²)       │
// │ Quick Sort  │ Temp array sort    │ In-place partition  │ O(n log n)  │
// │ Merge Sort  │ Temp array sort    │ In-place merge      │ O(n log n)  │
// └──────────────┴────────────────────┴────────────────────┴─────────────┘
//
// NOTE: For LinkedList, we use operator[] to access elements by index.
// This is NOT optimal for linked lists (pointer traversal would be better),
// but it works correctly for the assignment requirements.
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
// OUTPUT:  Two records exchange their data fields
// ----------------------------------------------------------------------------
void Sorting::swap(Record& a, Record& b) {
    Record temp = a;
    a = b;
    b = temp;
}


// ============================================================================
// BUBBLE SORT IMPLEMENTATION (LinkedList Version)
// ============================================================================
// How it works:
// - Uses operator[] to access elements by index (e.g., list[j], list[j+1])
// - Each access via operator[] traverses from head to that index (O(n))
// - Swaps data fields in-place within each node
// - Adds early exit optimization if no swaps occur
//
// TIME COMPLEXITY:  O(n²) - but with O(n) access overhead per comparison
// SPACE COMPLEXITY: O(1)  - in-place sorting
//
// CODE vs OUTPUT EXAMPLE:
// Input:  [Age:25] → [Age:18] → [Age:30]
// After bubbleSortByAge:
// Output: [Age:18] → [Age:25] → [Age:30]
// ┌────────────────────────────────────────────────────────────────────────┐
// │ CODE: if (list[j].age > list[j + 1].age) swap(list[j], list[j+1])   │
// │ Each list[j] traverses from head to index j (O(n) per access)      │
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

// Bubble Sort by Age
// Sorts records by age in ascending order using comparison-based sequential swapping
// Uses operator[] to access linked list elements during sorting
// TIME: O(n²) | SPACE: O(1) | STABILITY: Stable
long long Sorting::bubbleSortByAge(LinkedList& list) {
    auto start = chrono::high_resolution_clock::now();

    if (list.getSize() <= 1) {
        auto end = chrono::high_resolution_clock::now();
        return chrono::duration_cast<chrono::milliseconds>(end - start).count();
    }

    bool swapped;
    int n = list.getSize();
    
    for (int i = 0; i < n - 1; i++) {
        swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (list[j].age > list[j + 1].age) {
                swap(list[j], list[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;  
    }

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

// Bubble Sort by Daily Distance
// Sorts records by daily distance in ascending order using comparison-based sequential swapping
// Uses operator[] to access linked list elements during sorting
// TIME: O(n²) | SPACE: O(1) | STABILITY: Stable
long long Sorting::bubbleSortByDistance(LinkedList& list) {
    auto start = chrono::high_resolution_clock::now();

    if (list.getSize() <= 1) {
        auto end = chrono::high_resolution_clock::now();
        return chrono::duration_cast<chrono::milliseconds>(end - start).count();
    }

    bool swapped;
    int n = list.getSize();
    
    for (int i = 0; i < n - 1; i++) {
        swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (list[j].dailyDistance > list[j + 1].dailyDistance) {
                swap(list[j], list[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
    }

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

// Bubble Sort by Carbon Emission
// Sorts records by monthly carbon emission in ascending order using comparison-based sequential swapping
// Uses operator[] to access linked list elements during sorting
// TIME: O(n²) | SPACE: O(1) | STABILITY: Stable
long long Sorting::bubbleSortByEmission(LinkedList& list) {
    auto start = chrono::high_resolution_clock::now();

    if (list.getSize() <= 1) {
        auto end = chrono::high_resolution_clock::now();
        return chrono::duration_cast<chrono::milliseconds>(end - start).count();
    }

    bool swapped;
    int n = list.getSize();
    
    for (int i = 0; i < n - 1; i++) {
        swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (list[j].calculateMonthlyEmission() > list[j + 1].calculateMonthlyEmission()) {
                swap(list[j], list[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
    }

    auto end = chrono::high_resolution_clock::now();
    return chrono::duration_cast<chrono::milliseconds>(end - start).count();
}


// ============================================================================
// QUICK SORT IMPLEMENTATION (LinkedList Version)
// ============================================================================
// How it works:
// - Copies all linked list data to a temporary Record array
// - Performs quick sort on the array (standard array algorithm)
// - Copies sorted data back to linked list
//
// TIME COMPLEXITY:  O(n log n) average on the array, plus O(n) for copy
// SPACE COMPLEXITY: O(n) for temporary array
//
// CODE vs OUTPUT EXAMPLE:
// Input:  LinkedList with 5 nodes
// Step 1: Copy to temp array → [Rec1, Rec2, Rec3, Rec4, Rec5]
// Step 2: Quick sort the array
// Step 3: Copy back to linked list → Sorted nodes
// ┌────────────────────────────────────────────────────────────────────────┐
// │ CODE: Record* tempArr = new Record[n];                               │
// │       for(i=0; i<n; i++) tempArr[i] = list[i];                       │
// │       quickSortByAgeHelper(tempArr, 0, n-1);                          │
// │       for(i=0; i<n; i++) list[i] = tempArr[i];                       │
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
// Copies data to temporary array for efficient sorting, then copies back to list
// TIME: O(n log n) avg, O(n²) worst | SPACE: O(n) temporary + O(log n) recursion | STABILITY: Unstable
long long Sorting::quickSortByAge(LinkedList& list) {
    auto start = chrono::high_resolution_clock::now();

    int n = list.getSize();
    
    Record* tempArr = new Record[n];
    for (int i = 0; i < n; i++) {
        tempArr[i] = list[i];
    }

    quickSortByAgeHelper(tempArr, 0, n - 1);

    for (int i = 0; i < n; i++) {
        list[i] = tempArr[i];
    }
    
    delete[] tempArr;

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
// Copies data to temporary array for efficient sorting, then copies back to list
// TIME: O(n log n) avg, O(n²) worst | SPACE: O(n) temporary + O(log n) recursion | STABILITY: Unstable
long long Sorting::quickSortByDistance(LinkedList& list) {
    auto start = chrono::high_resolution_clock::now();

    int n = list.getSize();
    
    Record* tempArr = new Record[n];
    for (int i = 0; i < n; i++) {
        tempArr[i] = list[i];
    }

    quickSortByDistanceHelper(tempArr, 0, n - 1);

    for (int i = 0; i < n; i++) {
        list[i] = tempArr[i];
    }
    
    delete[] tempArr;

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
// Copies data to temporary array for efficient sorting, then copies back to list
// TIME: O(n log n) avg, O(n²) worst | SPACE: O(n) temporary + O(log n) recursion | STABILITY: Unstable
long long Sorting::quickSortByEmission(LinkedList& list) {
    auto start = chrono::high_resolution_clock::now();

    int n = list.getSize();
    
    Record* tempArr = new Record[n];
    for (int i = 0; i < n; i++) {
        tempArr[i] = list[i];
    }

    quickSortByEmissionHelper(tempArr, 0, n - 1);

    for (int i = 0; i < n; i++) {
        list[i] = tempArr[i];
    }
    
    delete[] tempArr;

    auto end = chrono::high_resolution_clock::now();
    return chrono::duration_cast<chrono::milliseconds>(end - start).count();
}


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
// Copies data to temporary array, performs merge sort, then copies back to list
// TIME: O(n log n) all cases | SPACE: O(n) temporary | STABILITY: Stable
long long Sorting::mergeSortByAge(LinkedList& list) {
    auto start = chrono::high_resolution_clock::now();

    int n = list.getSize();
    
    Record* tempArr = new Record[n];
    for (int i = 0; i < n; i++) {
        tempArr[i] = list[i];
    }

    mergeSortByAgeHelper(tempArr, 0, n - 1);

    for (int i = 0; i < n; i++) {
        list[i] = tempArr[i];
    }
    
    delete[] tempArr;

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
// Copies data to temporary array, performs merge sort, then copies back to list
// TIME: O(n log n) all cases | SPACE: O(n) temporary | STABILITY: Stable
long long Sorting::mergeSortByDistance(LinkedList& list) {
    auto start = chrono::high_resolution_clock::now();

    int n = list.getSize();
    
    Record* tempArr = new Record[n];
    for (int i = 0; i < n; i++) {
        tempArr[i] = list[i];
    }

    mergeSortByDistanceHelper(tempArr, 0, n - 1);

    for (int i = 0; i < n; i++) {
        list[i] = tempArr[i];
    }
    
    delete[] tempArr;

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
// Copies data to temporary array, performs merge sort, then copies back to list
// TIME: O(n log n) all cases | SPACE: O(n) temporary | STABILITY: Stable
long long Sorting::mergeSortByEmission(LinkedList& list) {
    auto start = chrono::high_resolution_clock::now();

    int n = list.getSize();
    
    Record* tempArr = new Record[n];
    for (int i = 0; i < n; i++) {
        tempArr[i] = list[i];
    }

    mergeSortByEmissionHelper(tempArr, 0, n - 1);

    for (int i = 0; i < n; i++) {
        list[i] = tempArr[i];
    }
    
    delete[] tempArr;

    auto end = chrono::high_resolution_clock::now();
    return chrono::duration_cast<chrono::milliseconds>(end - start).count();
}
