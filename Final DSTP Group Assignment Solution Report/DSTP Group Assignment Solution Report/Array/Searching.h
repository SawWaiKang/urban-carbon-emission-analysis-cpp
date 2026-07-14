#ifndef SEARCHING_H
#define SEARCHING_H

#include "Array.h"
#include <chrono>
#include <iostream>
using namespace std;


class Searching {
public:
    static long long linearSearchByTransport(const DynamicArray& arr, const string& mode, DynamicArray& results);
    static long long linearSearchByDistance(const DynamicArray& arr, double distance, DynamicArray& results);

    static long long binarySearchByAge(const DynamicArray& arr, int targetAge, DynamicArray& results);
    static long long binarySearchByDistance(const DynamicArray& arr, double targetDistance, DynamicArray& results);
    static long long binarySearchByTransport(const DynamicArray& arr, const string& mode, DynamicArray& results);
    static long long binarySearchByDistanceGreaterThan(const DynamicArray& arr, double distance, DynamicArray& results);
    static long long binarySearchByAgeGroup(const DynamicArray& arr, const string& ageGroup, DynamicArray& results);

    static long long searchByAgeGroup(const DynamicArray& arr, const string& ageGroup, DynamicArray& results);

private:
    static void linearSearchDistanceHelper(const Record* arr, int n, double distance, DynamicArray& results);
};

#endif 
