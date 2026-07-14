#ifndef SORTING_H
#define SORTING_H

#include "LinkedList.h"
#include <chrono>
#include <iostream>
using namespace std;


class Sorting {
public:
    static long long bubbleSortByAge(LinkedList& arr);
    static long long bubbleSortByDistance(LinkedList& arr);
    static long long bubbleSortByEmission(LinkedList& arr);

    static long long quickSortByAge(LinkedList& arr);
    static long long quickSortByDistance(LinkedList& arr);
    static long long quickSortByEmission(LinkedList& arr);

    static long long mergeSortByAge(LinkedList& arr);
    static long long mergeSortByDistance(LinkedList& arr);
    static long long mergeSortByEmission(LinkedList& arr);

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
