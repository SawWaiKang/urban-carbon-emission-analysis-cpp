#ifndef SEARCHING_H
#define SEARCHING_H

#include "LinkedList.h"
#include <chrono>
#include <iostream>
using namespace std;


class Searching {
public:
    static long long linearSearchByTransport(const LinkedList& list, const string& mode, LinkedList& results);
    static long long linearSearchByDistance(const LinkedList& list, double distance, LinkedList& results);

    static long long binarySearchByAge(const LinkedList& list, int targetAge, LinkedList& results);
    static long long binarySearchByDistance(const LinkedList& list, double targetDistance, LinkedList& results);
    static long long binarySearchByTransport(const LinkedList& list, const string& mode, LinkedList& results);
    static long long binarySearchByDistanceGreaterThan(const LinkedList& list, double distance, LinkedList& results);
    static long long binarySearchByAgeGroup(const LinkedList& list, const string& ageGroup, LinkedList& results);

    static long long searchByAgeGroup(const LinkedList& list, const string& ageGroup, LinkedList& results);

private:
    static void linearSearchDistanceHelper(const Record* arr, int n, double distance, LinkedList& results);
};

#endif 
