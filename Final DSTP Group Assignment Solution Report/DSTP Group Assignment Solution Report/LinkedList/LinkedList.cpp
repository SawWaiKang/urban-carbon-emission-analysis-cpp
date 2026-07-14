// ============================================================================
// SINGLY LINKED LIST IMPLEMENTATION (Node-Based)
// ============================================================================
// This linked list uses individual nodes connected by pointers.
// Each node contains data and a pointer to the next node.
// Memory is non-contiguous (each node is a separate heap allocation).
//
// COMPARISON: LinkedList vs Dynamic Array
// ┌─────────────────────┬──────────────────────────┬──────────────────────────┐
// │ Feature             │ Singly LinkedList        │ Dynamic Array            │
// ├─────────────────────┼──────────────────────────┼──────────────────────────┤
// │ Memory              │ Non-contiguous nodes     │ Contiguous block         │
// │ Access Time         │ O(n) sequential access   │ O(1) random access      │
// │ Insert at end      │ O(1)                     │ O(1) amortized           │
// │ Search             │ O(n) linear              │ O(n) linear, O(log n)   │
// │ Memory overhead    │ High (next pointer)      │ Low (just data pointer) │
// └─────────────────────┴──────────────────────────┴──────────────────────────┘
// ============================================================================

#include "LinkedList.h"
#include <iomanip>
#include <stdexcept>



// ----------------------------------------------------------------------------
// Constructor: Initializes empty linked list
// - head and tail set to nullptr (no nodes yet)
// - size = 0 (empty)
//
// CODE:    LinkedList() : head(nullptr), tail(nullptr), size(0)
// OUTPUT:  Creates empty list with no nodes (head/tail = nullptr)
// ----------------------------------------------------------------------------
LinkedList::LinkedList() : head(nullptr), tail(nullptr), size(0), memoryUsed(0) {}

// ----------------------------------------------------------------------------
// Destructor: Releases all nodes to prevent memory leaks
// - Calls clear() to delete each node one by one
//
// CODE:    ~LinkedList() { clear(); }
// OUTPUT:  When program ends, all nodes are deleted
// ----------------------------------------------------------------------------
LinkedList::~LinkedList() {
    clear();
}

// ----------------------------------------------------------------------------
// append(): Adds new record to end of linked list
// - Creates NEW node on heap (separate allocation for each record)
// - Links current tail to new node via ->next pointer
// - Updates tail to point to new node
// - Each append = one new Node allocation
//
// CODE:    Node* newNode = new Node(record); tail->next = newNode;
// OUTPUT:  New node added, linked to previous tail via ->next pointer
// ----------------------------------------------------------------------------
void LinkedList::append(const Record& record) {
    Node* newNode = new Node(record);

    if (head == nullptr) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        tail = newNode;
    }

    size++;
    memoryUsed += sizeof(Node);
}

void LinkedList::display() const {
    if (size == 0) {
        cout << "No records to display." << endl;
        return;
    }

    cout << "\n=== CARBON EMISSION RECORDS ===" << endl;
    cout << left << setw(5) << "ID"
         << setw(5) << "Age"
         << setw(12) << "Transport"
         << setw(10) << "Distance"
         << setw(12) << "Emission"
         << setw(15) << "Monthly CO2"
         << setw(10) << "Age Group" << endl;
    cout << string(75, '-') << endl;

    Node* current = head;
    while (current != nullptr) {
        cout << left << setw(5) << current->data.residentID
             << setw(5) << current->data.age
             << setw(12) << current->data.transportMode
             << fixed << setprecision(2)
             << setw(10) << current->data.dailyDistance
             << setw(12) << current->data.carbonEmissionFactor
             << setw(15) << current->data.calculateMonthlyEmission()
             << setw(10) << current->data.getAgeGroup() << endl;
        current = current->next;
    }
    cout << endl;
}

void LinkedList::clear() {
    Node* current = head;
    while (current != nullptr) {
        Node* temp = current;
        current = current->next;
        delete temp;
    }
    head = tail = nullptr;
    size = 0;
    memoryUsed = 0;
}

int LinkedList::getSize() const {
    return size;
}


long long LinkedList::getMemoryUsed() const {
    return memoryUsed;
}

Record* LinkedList::getData() {
    return nullptr;  
}

const Record* LinkedList::getData() const {
    return nullptr;  
}

Record& LinkedList::operator[](int index) {
    if (index < 0 || index >= size) {
        throw out_of_range("Index out of range");
    }

    Node* current = head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    return current->data;
}

const Record& LinkedList::operator[](int index) const {
    if (index < 0 || index >= size) {
        throw out_of_range("Index out of range");
    }

    Node* current = head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    return current->data;
}

int LinkedList::linearSearch(const string& field, const string& value) {
    int count = 0;
    Node* current = head;

    while (current != nullptr) {
        bool match = false;
        if (field == "transport") {
            match = (current->data.transportMode == value);
        } else if (field == "ageGroup") {
            match = (current->data.getAgeGroup() == value);
        }
        if (match) count++;
        current = current->next;
    }
    return count;
}

int LinkedList::linearSearchDouble(const string& field, double value, const string& condition) {
    int count = 0;
    Node* current = head;

    while (current != nullptr) {
        bool match = false;
        if (field == "distance") {
            if (condition == "=") match = (current->data.dailyDistance == value);
            else if (condition == ">") match = (current->data.dailyDistance > value);
            else if (condition == "<") match = (current->data.dailyDistance < value);
            else if (condition == ">=") match = (current->data.dailyDistance >= value);
            else if (condition == "<=") match = (current->data.dailyDistance <= value);
        } else if (field == "emission") {
            if (condition == "=") match = (current->data.carbonEmissionFactor == value);
            else if (condition == ">") match = (current->data.carbonEmissionFactor > value);
            else if (condition == "<") match = (current->data.carbonEmissionFactor < value);
            else if (condition == ">=") match = (current->data.carbonEmissionFactor >= value);
            else if (condition == "<=") match = (current->data.carbonEmissionFactor <= value);
        }
        if (match) count++;
        current = current->next;
    }
    return count;
}

void LinkedList::searchByAgeGroup(const string& ageGroup, LinkedList& results) const {
    results.clear();
    Node* current = head;

    while (current != nullptr) {
        if (current->data.getAgeGroup() == ageGroup) {
            results.append(current->data);
        }
        current = current->next;
    }
}

void LinkedList::searchByTransportMode(const string& mode, LinkedList& results) const {
    results.clear();
    Node* current = head;

    while (current != nullptr) {
        if (current->data.transportMode == mode) {
            results.append(current->data);
        }
        current = current->next;
    }
}

void LinkedList::searchByDistance(double distance, LinkedList& results) const {
    results.clear();
    Node* current = head;

    while (current != nullptr) {
        if (current->data.dailyDistance >= distance) {
            results.append(current->data);
        }
        current = current->next;
    }
}

void LinkedList::copyFrom(const LinkedList& other) {
    clear();
    Node* current = other.head;

    while (current != nullptr) {
        append(current->data);
        current = current->next;
    }
}

void LinkedList::printTable() const {
    display();
}