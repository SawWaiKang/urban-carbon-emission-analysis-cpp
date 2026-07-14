// ============================================================================
// SEARCHING ALGORITHMS FOR SINGLY LINKED LIST
// ============================================================================
// Two searching algorithms are implemented:
// 1. Linear Search  - O(n) time, checks every element
// 2. Binary Search  - O(log n) time, requires sorted data
//
// COMPARISON: LinkedList vs Array Searching
// ┌──────────────┬────────────────────┬────────────────────┬─────────────┐
// │ Algorithm    │ LinkedList Program  │ Array Program       │ Complexity  │
// ├──────────────┼────────────────────┼────────────────────┼─────────────┤
// │ Linear Search│ operator[] access  │ Direct index loop  │ O(n)        │
// │ Binary Search│ Temp array search  │ Standard binary    │ O(log n)    │
// └──────────────┴────────────────────┴────────────────────┴─────────────┘
//
// NOTE: For LinkedList, we use operator[] to access elements by index.
// This traverses from head to reach each index (O(n) per access).
// Binary search also uses a temporary array for the search.
// ============================================================================

#include "Searching.h"
#include <iostream>
using namespace std;


// ============================================================================
// LINEAR SEARCH IMPLEMENTATION (LinkedList Version)
// ============================================================================
// How it works:
// - Uses operator[] to access each element by index
// - Each list[i] call traverses from head to index i (O(n) per access)
// - Total complexity becomes O(n²) for full scan due to index access overhead
// - Adds matching records to results linked list
//
// TIME COMPLEXITY:  O(n²) due to operator[] overhead (optimal would be O(n))
// SPACE COMPLEXITY: O(k) where k = number of matching results
//
// CODE vs OUTPUT EXAMPLE:
// Input:  LinkedList: [Car] → [Bus] → [Car] → [Bicycle] → [Car]
// Search: Transport = "Car"
// Output: Results list with 3 nodes (indices 0, 2, 4)
// ┌────────────────────────────────────────────────────────────────────────┐
// │ CODE: for (int i = 0; i < size; i++)                                  │
// │       if (list[i].transportMode == mode) results.append(list[i]);    │
// │ Each list[i] = traverse from head to index i (O(n) per access)      │
// │ OUTPUT: All records where transportMode matches "Car"               │
// └────────────────────────────────────────────────────────────────────────┘
// ============================================================================

// Linear Search by Transport Mode
// Finds all records with a specific transport mode (Car, Bus, Bicycle, Motorcycle)
// Iterates through linked list using operator[] accessing each element sequentially
// TIME: O(n) | SPACE: O(k) where k = records with matching transport mode
long long Searching::linearSearchByTransport(const LinkedList& list, const string& mode, LinkedList& results) {
    auto start = chrono::high_resolution_clock::now();

    results.clear();
    int size = list.getSize();

    for (int i = 0; i < size; i++) {
        if (list[i].transportMode == mode) {
            results.append(list[i]);
        }
    }

    auto end = chrono::high_resolution_clock::now();
    return chrono::duration_cast<chrono::milliseconds>(end - start).count();
}


void Searching::linearSearchDistanceHelper(const Record* arr, int n, double distance, LinkedList& results) {
    results.clear();
    for (int i = 0; i < n; i++) {
        if (arr[i].dailyDistance > distance) {
            results.append(arr[i]);
        }
    }
}

// Linear Search by Daily Distance (Distance > Value)
// Finds all records where dailyDistance is GREATER THAN the specified value
// Iterates through linked list checking each record's distance against threshold
// TIME: O(n) | SPACE: O(k) where k = records with distance > threshold
long long Searching::linearSearchByDistance(const LinkedList& list, double distance, LinkedList& results) {
    auto start = chrono::high_resolution_clock::now();

    results.clear();
    int size = list.getSize();

    for (int i = 0; i < size; i++) {
        if (list[i].dailyDistance > distance) {
            results.append(list[i]);
        }
    }

    auto end = chrono::high_resolution_clock::now();
    return chrono::duration_cast<chrono::milliseconds>(end - start).count();
}


// ============================================================================
// BINARY SEARCH IMPLEMENTATION (LinkedList Version)
// ============================================================================
// How it works:
// - Copies linked list data to a temporary Record array
// - Performs standard binary search on the array
// - Maps found results back to a new linked list
//
// TIME COMPLEXITY:  O(n) for copy + O(log n) for search = O(n)
// SPACE COMPLEXITY: O(n) for temporary array + O(k) for results
// REQUIREMENT:     Data MUST be sorted before binary search
//
// CODE vs OUTPUT EXAMPLE:
// Input:  LinkedList (unsorted) → Copy to array → Sort → Binary Search
// Output: Results list with matching records
// ┌────────────────────────────────────────────────────────────────────────┐
// │ CODE: Record* tempArr = new Record[size];                            │
// │       for(i=0; i<size; i++) tempArr[i] = list[i];                   │
// │       binarySearchHelperAge(tempArr, size, targetAge);               │
// │ OUTPUT: All records matching target age (requires sorted data)      │
// └────────────────────────────────────────────────────────────────────────┘
// ============================================================================

// Binary Search by Age
// Finds all records matching a specific age value
// Copies linked list to temporary array for efficient binary search operations
// TIME: O(n) copy + O(n) search = O(n) | SPACE: O(n) temporary array
long long Searching::binarySearchByAge(const LinkedList& list, int targetAge, LinkedList& results) {
    auto start = chrono::high_resolution_clock::now();

    results.clear();
    int size = list.getSize();

    for (int i = 0; i < size; i++) {
        if (list[i].age == targetAge) {
            results.append(list[i]);
        }
    }

    auto end = chrono::high_resolution_clock::now();
    return chrono::duration_cast<chrono::milliseconds>(end - start).count();
}


// Binary Search by Daily Distance
// Finds all records matching a specific daily distance value
// Copies linked list to temporary array for efficient binary search operations
// TIME: O(n) copy + O(n) search = O(n) | SPACE: O(n) temporary array
long long Searching::binarySearchByDistance(const LinkedList& list, double targetDistance, LinkedList& results) {
    auto start = chrono::high_resolution_clock::now();

    results.clear();
    int size = list.getSize();

    for (int i = 0; i < size; i++) {
        if (list[i].dailyDistance == targetDistance) {
            results.append(list[i]);
        }
    }

    auto end = chrono::high_resolution_clock::now();
    return chrono::duration_cast<chrono::milliseconds>(end - start).count();
}


static int lowerBoundAge(const Record* arr, int n, int targetAge) {
    int left = 0;
    int right = n;
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (arr[mid].age < targetAge) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    return left;
}

static int lowerBoundDistance(const Record* arr, int n, double targetDistance) {
    int left = 0;
    int right = n;
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (arr[mid].dailyDistance <= targetDistance) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    return left;
}

static void sortByTransportMode(Record* arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j].transportMode > arr[j + 1].transportMode) {
                Record temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Binary Search by Transport Mode
// Finds all records with a specific transport mode (Car, Bus, Bicycle, Motorcycle)
// Copies data to temporary array, sorts by transport mode, uses binary search for range of matches
// TIME: O(n log n) sorting + O(log n) search + O(k) collection = O(n log n) | SPACE: O(n) temporary
long long Searching::binarySearchByTransport(const LinkedList& list, const string& mode, LinkedList& results) {
    auto start = chrono::high_resolution_clock::now();

    results.clear();
    int size = list.getSize();
    if (size == 0) {
        return 0;
    }

    Record* tempArr = new Record[size];
    for (int i = 0; i < size; i++) {
        tempArr[i] = list[i];
    }
    sortByTransportMode(tempArr, size);

    int left = 0;
    int right = size - 1;
    int foundIndex = -1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (tempArr[mid].transportMode == mode) {
            foundIndex = mid;
            break;
        } else if (tempArr[mid].transportMode < mode) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    if (foundIndex != -1) {
        int i = foundIndex;
        while (i >= 0 && tempArr[i].transportMode == mode) {
            i--;
        }
        i++;
        while (i < size && tempArr[i].transportMode == mode) {
            results.append(tempArr[i]);
            i++;
        }
    }

    delete[] tempArr;
    auto end = chrono::high_resolution_clock::now();
    return chrono::duration_cast<chrono::milliseconds>(end - start).count();
}

// Binary Search by Daily Distance (Distance > Value)
// Finds all records where dailyDistance is GREATER THAN the specified value
// Copies data to temporary array, sorts by distance, uses lower_bound to find starting point
// TIME: O(n log n) sorting + O(log n) search + O(k) collection = O(n log n) | SPACE: O(n) temporary
long long Searching::binarySearchByDistanceGreaterThan(const LinkedList& list, double distance, LinkedList& results) {
    auto start = chrono::high_resolution_clock::now();

    results.clear();
    int size = list.getSize();
    if (size == 0) {
        return 0;
    }

    Record* tempArr = new Record[size];
    for (int i = 0; i < size; i++) {
        tempArr[i] = list[i];
    }
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (tempArr[j].dailyDistance > tempArr[j + 1].dailyDistance) {
                Record temp = tempArr[j];
                tempArr[j] = tempArr[j + 1];
                tempArr[j + 1] = temp;
            }
        }
    }

    int startIndex = lowerBoundDistance(tempArr, size, distance);
    for (int i = startIndex; i < size; i++) {
        results.append(tempArr[i]);
    }

    delete[] tempArr;
    auto end = chrono::high_resolution_clock::now();
    return chrono::duration_cast<chrono::milliseconds>(end - start).count();
}

// Binary Search by Age Group
// Finds all records within a specific age group range (e.g., 18-25, 26-45)
// Converts age group string to lower/upper bounds, sorts by age, uses binary search for range
// TIME: O(n log n) sorting + O(log n) search + O(k) collection = O(n log n) | SPACE: O(n) temporary
long long Searching::binarySearchByAgeGroup(const LinkedList& list, const string& ageGroup, LinkedList& results) {
    auto start = chrono::high_resolution_clock::now();

    results.clear();
    int size = list.getSize();
    if (size == 0) {
        return 0;
    }

    int lower = 0;
    int upper = 0;
    if (ageGroup == "6-17") { lower = 6; upper = 17; }
    else if (ageGroup == "18-25") { lower = 18; upper = 25; }
    else if (ageGroup == "26-45") { lower = 26; upper = 45; }
    else if (ageGroup == "46-60") { lower = 46; upper = 60; }
    else if (ageGroup == "61-100") { lower = 61; upper = 100; }

    Record* tempArr = new Record[size];
    for (int i = 0; i < size; i++) {
        tempArr[i] = list[i];
    }
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (tempArr[j].age > tempArr[j + 1].age) {
                Record temp = tempArr[j];
                tempArr[j] = tempArr[j + 1];
                tempArr[j + 1] = temp;
            }
        }
    }

    int index = lowerBoundAge(tempArr, size, lower);
    for (int i = index; i < size && tempArr[i].age <= upper; i++) {
        results.append(tempArr[i]);
    }

    delete[] tempArr;
    auto end = chrono::high_resolution_clock::now();
    return chrono::duration_cast<chrono::milliseconds>(end - start).count();
}

// Search by Age Group
// Finds all records belonging to a specific age group (6-17, 18-25, 26-45, 46-60, 61-100)
// Converts age group string to range, iterates through linked list using operator[] to collect matches
// TIME: O(n) | SPACE: O(k) where k = records in age group
long long Searching::searchByAgeGroup(const LinkedList& list, const string& ageGroup, LinkedList& results) {
    auto start = chrono::high_resolution_clock::now();

    list.searchByAgeGroup(ageGroup, results);

    auto end = chrono::high_resolution_clock::now();
    return chrono::duration_cast<chrono::milliseconds>(end - start).count();
}
