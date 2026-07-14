// ============================================================================
// SEARCHING ALGORITHMS FOR DYNAMIC ARRAY
// ============================================================================
// Two searching algorithms are implemented:
// 1. Linear Search  - O(n) time, checks every element
// 2. Binary Search  - O(log n) time, requires sorted data
//
// COMPARISON: Array vs LinkedList Searching
// ┌──────────────┬────────────────────┬────────────────────┬─────────────┐
// │ Algorithm    │ Array Program      │ LinkedList Program  │ Complexity  │
// ├──────────────┼────────────────────┼────────────────────┼─────────────┤
// │ Linear Search│ Direct index loop │ operator[] access  │ O(n)        │
// │ Binary Search│ Standard binary   │ Temp array search  │ O(log n)    │
// └──────────────┴────────────────────┴────────────────────┴─────────────┘
// ============================================================================

#include "Searching.h"
#include <iostream>
using namespace std;


// ============================================================================
// LINEAR SEARCH IMPLEMENTATION
// ============================================================================
// How it works:
// - Iterates through array from index 0 to n-1
// - Checks each element for matching condition
// - Adds matching records to results array
//
// TIME COMPLEXITY:  O(n) - must check every element in worst case
// SPACE COMPLEXITY: O(k) where k = number of matching results
//
// CODE vs OUTPUT EXAMPLE:
// Input:  [Car, Bus, Car, Bicycle, Car]
// Search: Transport = "Car"
// Output: Results array with 3 records (indices 0, 2, 4)
// ┌────────────────────────────────────────────────────────────────────────┐
// │ CODE: for (int i = 0; i < size; i++)                                  │
// │       if (data[i].transportMode == mode) results.append(data[i]);     │
// │ OUTPUT: All records where transportMode matches "Car"               │
// └────────────────────────────────────────────────────────────────────────┘
// ============================================================================

long long Searching::linearSearchByTransport(const DynamicArray& arr, const string& mode, DynamicArray& results) {
    auto start = chrono::high_resolution_clock::now();
    
    results.clear();
    const Record* data = arr.getData();
    int size = arr.getSize();

    for (int i = 0; i < size; i++) {
        if (data[i].transportMode == mode) {
            results.append(data[i]);
        }
    }

    auto end = chrono::high_resolution_clock::now();
    return chrono::duration_cast<chrono::milliseconds>(end - start).count();
}


void Searching::linearSearchDistanceHelper(const Record* arr, int n, double distance, DynamicArray& results) {
    results.clear();
    for (int i = 0; i < n; i++) {
        if (arr[i].dailyDistance > distance) {
            results.append(arr[i]);
        }
    }
}

// Linear Search by Daily Distance (Distance > Value)
// Finds all records where dailyDistance is GREATER THAN the specified value
// Iterates through entire array checking each record's distance against threshold
// TIME: O(n) | SPACE: O(k) where k = matching results
long long Searching::linearSearchByDistance(const DynamicArray& arr, double distance, DynamicArray& results) {
    auto start = chrono::high_resolution_clock::now();
    
    linearSearchDistanceHelper(arr.getData(), arr.getSize(), distance, results);

    auto end = chrono::high_resolution_clock::now();
    return chrono::duration_cast<chrono::milliseconds>(end - start).count();
}


// ============================================================================
// BINARY SEARCH IMPLEMENTATION
// ============================================================================
// How it works:
// - Requires data to be SORTED first
// - Divides sorted array in half each iteration
// - Compares target with middle element
// - If target < middle, search left half; else search right half
// - Repeats until found or subarray is empty
//
// TIME COMPLEXITY:  O(log n) - halves search space each iteration
// SPACE COMPLEXITY: O(k) where k = number of matching results
// REQUIREMENT:     Data MUST be sorted before binary search
//
// CODE vs OUTPUT EXAMPLE:
// Input:  Sorted array by age: [18, 25, 30, 35, 40]
// Search: Age = 30
// Step 1: mid = 2 (value 30) → FOUND at index 2
// ┌────────────────────────────────────────────────────────────────────────┐
// │ CODE: while (left <= right) { mid = (left+right)/2; ... }             │
// │ OUTPUT: Returns index of first match, or -1 if not found             │
// └────────────────────────────────────────────────────────────────────────┘
// ============================================================================

// Binary Search by Age
// Finds all records matching a specific age value
// Iterates through array to collect all records with exact age match
// Note: Called 'binary' for consistency with interface, but performs linear search on results
// TIME: O(n) | SPACE: O(k) where k = records with matching age
long long Searching::binarySearchByAge(const DynamicArray& arr, int targetAge, DynamicArray& results) {
    auto start = chrono::high_resolution_clock::now();
    
    results.clear();
    const Record* data = arr.getData();
    int size = arr.getSize();

    for (int i = 0; i < size; i++) {
        if (data[i].age == targetAge) {
            results.append(data[i]);
        }
    }

    auto end = chrono::high_resolution_clock::now();
    return chrono::duration_cast<chrono::milliseconds>(end - start).count();
}


// Search by Age Group
// Finds all records belonging to a specific age group (6-17, 18-25, 26-45, 46-60, 61-100)
// Uses DynamicArray's built-in searchByAgeGroup method for consistency
// TIME: O(n) | SPACE: O(k) where k = records in age group
long long Searching::searchByAgeGroup(const DynamicArray& arr, const string& ageGroup, DynamicArray& results) {
    auto start = chrono::high_resolution_clock::now();
    
    arr.searchByAgeGroup(ageGroup, results);

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
// Sorts data by transport mode first, then uses binary search to find range of matching records
// TIME: O(n log n) sorting + O(log n) search = O(n log n) | SPACE: O(n) temporary
long long Searching::binarySearchByTransport(const DynamicArray& arr, const string& mode, DynamicArray& results) {
    auto start = chrono::high_resolution_clock::now();

    results.clear();
    int size = arr.getSize();
    if (size == 0) {
        return 0;
    }

    Record* tempArr = new Record[size];
    for (int i = 0; i < size; i++) {
        tempArr[i] = arr.getData()[i];
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
// Sorts data by distance first, then uses lower_bound to find starting point and collects all greater values
// TIME: O(n log n) sorting + O(log n) search + O(k) collection = O(n log n) | SPACE: O(n) temporary
long long Searching::binarySearchByDistanceGreaterThan(const DynamicArray& arr, double distance, DynamicArray& results) {
    auto start = chrono::high_resolution_clock::now();

    results.clear();
    int size = arr.getSize();
    if (size == 0) {
        return 0;
    }

    Record* tempArr = new Record[size];
    for (int i = 0; i < size; i++) {
        tempArr[i] = arr.getData()[i];
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
long long Searching::binarySearchByAgeGroup(const DynamicArray& arr, const string& ageGroup, DynamicArray& results) {
    auto start = chrono::high_resolution_clock::now();

    results.clear();
    int size = arr.getSize();
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
        tempArr[i] = arr.getData()[i];
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
