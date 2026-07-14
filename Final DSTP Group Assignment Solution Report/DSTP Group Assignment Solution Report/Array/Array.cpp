// ============================================================================
// DYNAMIC ARRAY IMPLEMENTATION (Pointer-Based, Resizable)
// ============================================================================
// This array uses a pointer to heap-allocated memory that can be resized.
// Unlike static arrays, this grows automatically when capacity is reached.
//
// COMPARISON: Array vs LinkedList
// ┌─────────────────────┬──────────────────────────┬──────────────────────────┐
// │ Feature             │ Dynamic Array            │ Singly LinkedList        │
// ├─────────────────────┼──────────────────────────┼──────────────────────────┤
// │ Memory              │ Contiguous block         │ Non-contiguous nodes     │
// │ Access Time         │ O(1) random access       │ O(n) sequential access  │
// │ Insert at end      │ O(1) amortized           │ O(1)                     │
// │ Search             │ O(n) linear, O(log n)    │ O(n) linear              │
// │ Memory overhead    │ Low (just data pointer)  │ High (next pointer)     │
// └─────────────────────┴──────────────────────────┴──────────────────────────┘
// ============================================================================

#include "Array.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>
using namespace std;


// ----------------------------------------------------------------------------
// Constructor: Initializes dynamic array with given capacity
// - Allocates contiguous memory block on heap using 'new'
// - Sets initial size to 0
//
// CODE:    data = new Record[capacity];
// OUTPUT:  Allocates memory for storing records contiguously
// ----------------------------------------------------------------------------
DynamicArray::DynamicArray(int initialCapacity)
    : capacity(initialCapacity), size(0) {
    data = new Record[capacity];  // Allocate heap memory for capacity records
    memoryUsed = capacity * sizeof(Record);
}

// ----------------------------------------------------------------------------
// Destructor: Releases heap memory to prevent memory leaks
// - Uses delete[] to free the contiguous memory block
//
// CODE:    delete[] data;
// OUTPUT:  Frees all allocated memory when program ends
// ----------------------------------------------------------------------------
DynamicArray::~DynamicArray() {
    if (data != nullptr) {
        delete[] data;
        data = nullptr;
    }
}


// ----------------------------------------------------------------------------
// resize(): Doubles the array capacity when full
// - Creates new larger array (2x size)
// - Copies all existing data to new array
// - Deletes old array to free memory
// - This is automatic and transparent to the user
//
// CODE:    Record* newData = new Record[newCapacity];
// OUTPUT:  When capacity reached, array automatically grows
// ----------------------------------------------------------------------------
void DynamicArray::resize() {
    int newCapacity = capacity * 2;
    Record* newData = new Record[newCapacity];

    for (int i = 0; i < size; i++) {
        newData[i] = data[i];
    }

    delete[] data;
    data = newData;
    capacity = newCapacity;
    memoryUsed = capacity * sizeof(Record);
}


// ----------------------------------------------------------------------------
// append(): Adds new record to end of array
// - Checks if array is full; if so, calls resize()
// - Stores record at data[size] position
// - Increments size counter
//
// CODE:    data[size] = record; size++;
// OUTPUT:  New record added at next available index
// ----------------------------------------------------------------------------
void DynamicArray::append(const Record& record) {
    if (size >= capacity) {
        resize();
    }
    data[size] = record;
    size++;
}

void DynamicArray::display() const {
    cout << "Total Records: " << size << " / Capacity: " << capacity << "\n";
    printTable();
}

void DynamicArray::clear() {
    size = 0;
}


int DynamicArray::getSize() const {
    return size;
}

long long DynamicArray::getMemoryUsed() const {
    return memoryUsed;
}

Record* DynamicArray::getData() {
    return data;
}

const Record* DynamicArray::getData() const {
    return data;
}

Record& DynamicArray::operator[](int index) {
    return data[index];
}

const Record& DynamicArray::operator[](int index) const {
    return data[index];
}


int DynamicArray::linearSearch(const string& field, const string& value) {
    for (int i = 0; i < size; i++) {
        if (field == "transportMode" && data[i].transportMode == value) {
            return i;
        }
    }
    return -1;  
}

int DynamicArray::linearSearchDouble(const string& field, double value, const string& condition) {
    for (int i = 0; i < size; i++) {
        bool match = false;
        if (field == "dailyDistance") {
            if (condition == ">" && data[i].dailyDistance > value) match = true;
            else if (condition == "<" && data[i].dailyDistance < value) match = true;
            else if (condition == "=" && data[i].dailyDistance == value) match = true;
        } else if (field == "carbonEmission") {
            if (condition == ">" && data[i].calculateMonthlyEmission() > value) match = true;
            else if (condition == "<" && data[i].calculateMonthlyEmission() < value) match = true;
            else if (condition == "=" && data[i].calculateMonthlyEmission() == value) match = true;
        }
        if (match) return i;
    }
    return -1;
}

void DynamicArray::searchByAgeGroup(const string& ageGroup, DynamicArray& results) const {
    results.clear();
    for (int i = 0; i < size; i++) {
        if (data[i].getAgeGroup() == ageGroup) {
            results.append(data[i]);
        }
    }
}

void DynamicArray::searchByTransportMode(const string& mode, DynamicArray& results) const {
    results.clear();
    for (int i = 0; i < size; i++) {
        if (data[i].transportMode == mode) {
            results.append(data[i]);
        }
    }
}

void DynamicArray::searchByDistance(double distance, DynamicArray& results) const {
    results.clear();
    for (int i = 0; i < size; i++) {
        if (data[i].dailyDistance > distance) {
            results.append(data[i]);
        }
    }
}


void DynamicArray::copyFrom(const DynamicArray& other) {
    if (capacity < other.size) {
        delete[] data;
        capacity = other.size * 1.5;
        data = new Record[capacity];
    }

    for (int i = 0; i < other.size; i++) {
        data[i] = other.data[i];
    }
    size = other.size;
    memoryUsed = capacity * sizeof(Record);
}


void DynamicArray::printTable() const {
    if (size == 0) {
        cout << "No records to display.\n";
        return;
    }

    cout << "\n";
    cout << setw(12) << "ID"
         << setw(6) << "Age"
         << setw(20) << "Transport"
         << setw(12) << "Distance"
         << setw(15) << "Emission"
         << setw(15) << "Monthly Emission"
         << setw(12) << "Age Group\n";
    cout << string(92, '-') << "\n";

    for (int i = 0; i < size; i++) {
        cout << setw(12) << data[i].residentID
             << setw(6) << data[i].age
             << setw(20) << data[i].transportMode
             << setw(12) << fixed << setprecision(2) << data[i].dailyDistance
             << setw(15) << fixed << setprecision(3) << data[i].carbonEmissionFactor
             << setw(15) << fixed << setprecision(2) << data[i].calculateMonthlyEmission()
             << setw(12) << data[i].getAgeGroup() << "\n";
    }
    cout << string(92, '-') << "\n";
}


