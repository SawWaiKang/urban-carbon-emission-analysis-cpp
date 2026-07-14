#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Data.h"
#include <iostream>
#include <chrono>
using namespace std;


struct Node {
    Record data;
    Node* next;
    Node(const Record& record) : data(record), next(nullptr) {}
};

class LinkedList {
private:
    Node* head;
    Node* tail;
    int size;
    long long memoryUsed;

public:
    LinkedList();

    ~LinkedList();

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
    void searchByAgeGroup(const string& ageGroup, LinkedList& results) const;
    void searchByTransportMode(const string& mode, LinkedList& results) const;
    void searchByDistance(double distance, LinkedList& results) const;

    void copyFrom(const LinkedList& other);

    void printTable() const;
};

#endif 