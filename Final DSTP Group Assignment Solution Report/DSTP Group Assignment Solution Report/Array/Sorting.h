#ifndef SORTING_H
#define SORTING_H

#include "Array.h"
#include <chrono>
#include <iostream>
using namespace std;


class Sorting {
public:
    static long long bubbleSortByAge(DynamicArray& arr);
    static long long bubbleSortByDistance(DynamicArray& arr);
    static long long bubbleSortByEmission(DynamicArray& arr);

    static long long quickSortByAge(DynamicArray& arr);
    static long long quickSortByDistance(DynamicArray& arr);
    static long long quickSortByEmission(DynamicArray& arr);

    static long long mergeSortByAge(DynamicArray& arr);
    static long long mergeSortByDistance(DynamicArray& arr);
    static long long mergeSortByEmission(DynamicArray& arr);

private:
    static void bubbleSortByAgeHelper(Record* arr, int n);
    static void bubbleSortByDistanceHelper(Record* arr, int n);
    static void bubbleSortByEmissionHelper(Record* arr, int n);

    static int partitionByAge(Record* arr, int low, int high);
    static int partitionByDistance(Record* arr, int low, int high);
    static int partitionByEmission(Record* arr, int low, int high);

    static void quickSortByAgeHelper(Record* arr, int low, int high);
    static void quickSortByDistanceHelper(Record* arr, int low, int high);
    static void quickSortByEmissionHelper(Record* arr, int low, int high);

    static void mergeByAge(Record* arr, int left, int mid, int right);
    static void mergeByDistance(Record* arr, int left, int mid, int right);
    static void mergeByEmission(Record* arr, int left, int mid, int right);

    static void mergeSortByAgeHelper(Record* arr, int left, int right);
    static void mergeSortByDistanceHelper(Record* arr, int left, int right);
    static void mergeSortByEmissionHelper(Record* arr, int left, int right);

    static void swap(Record& a, Record& b);
};

#endif 
