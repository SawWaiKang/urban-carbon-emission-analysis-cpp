#ifndef ARRAY_H
#define ARRAY_H

#include "Data.h"
#include <iostream>
#include <chrono>
using namespace std;


class DynamicArray {
private:
    Record* data;
    int capacity;
    int size;
    long long memoryUsed;

    void resize();

public:
    DynamicArray(int initialCapacity = 100);

    ~DynamicArray();

    void append(const Record& record);
    void display() const;
    void clear();

    int getSize() const;
    long long getMemoryUsed() const;
    Record* getData();
    const Record* getData() const;
    Record& operator[](int index);
    const Record& operator[](int index) const;

    int linearSearch(const string& field, const string& value);
    int linearSearchDouble(const string& field, double value, const string& condition = "=");
    void searchByAgeGroup(const string& ageGroup, DynamicArray& results) const;
    void searchByTransportMode(const string& mode, DynamicArray& results) const;
    void searchByDistance(double distance, DynamicArray& results) const;

    void copyFrom(const DynamicArray& other);

    void printTable() const;
};

#endif
