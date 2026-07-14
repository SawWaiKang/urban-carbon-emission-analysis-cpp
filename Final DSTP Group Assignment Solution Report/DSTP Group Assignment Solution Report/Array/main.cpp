#include <iostream>
#include <string>
#include <chrono>
#include <iomanip>
#include <limits>
#include "Data.h"
#include "Array.h"
#include "Sorting.h"
#include "Searching.h"
#include "Analysis.h"
#include "FileIO.h"
using namespace std;


DynamicArray mainArray;
DynamicArray cityAArray;
DynamicArray cityBArray;
DynamicArray cityCArray;
long long lastOperationTime = 0;
int selectedCityMode = 0; 
string selectedCityName = ""; 


void displayMainMenu();
void displaySortingMenu(const string& datasetName);
void displaySearchingMenu(const string& datasetName);
void displayCarbonEmissionMenu();
void displayAgeGroupReport(DynamicArray& dataset, const string& datasetName);
void displayPerformanceAnalysisMenu();

void initializeDataSelection();
int selectDataset(const string& action);
DynamicArray* getDatasetByChoice(int choice);
string getDatasetName(int choice);

void displayAllRecords(DynamicArray& dataset, int datasetChoice);

void sortByAge(DynamicArray& dataset, const string& datasetName);
void sortByDistance(DynamicArray& dataset, const string& datasetName);
void sortByEmission(DynamicArray& dataset, const string& datasetName);

void searchByAgeGroup(DynamicArray& dataset, const string& datasetName);
void searchByTransportMode(DynamicArray& dataset, const string& datasetName);
void searchByDistance(DynamicArray& dataset, const string& datasetName);

void totalEmissionPerCity();
void emissionByTransportMode();
void compareEmissionByCity();

void mostPreferredTransport(DynamicArray& dataset, const string& datasetName);
void totalEmissionByAgeGroup(DynamicArray& dataset, const string& datasetName);
void averageEmissionPerResident(DynamicArray& dataset, const string& datasetName);

void performanceAnalysis();
int selectSearchAlgorithm();

void printSeparator();
void printHeader(const string& title);
void pressEnterToContinue();


int main() {
    int mainChoice;
    bool running = true;

    initializeDataSelection();

    while (running) {
        displayMainMenu();
        cout << "Enter your choice: ";
        cin >> mainChoice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "\nInvalid input! Please enter a number.\n";
            pressEnterToContinue();
            continue;
        }

        switch (mainChoice) {
            case 1: {
                int datasetChoice = selectDataset("DISPLAY RESIDENTS FROM");
                if (datasetChoice == 0) break;
                DynamicArray* dataset = getDatasetByChoice(datasetChoice);
                displayAllRecords(*dataset, datasetChoice);
                break;
            }
            case 2: {
                int datasetChoice = selectDataset("SORT FROM");
                if (datasetChoice == 0) break;
                DynamicArray* dataset = getDatasetByChoice(datasetChoice);
                string datasetName = getDatasetName(datasetChoice);
                bool sortRunning = true;
                while (sortRunning) {
                    displaySortingMenu(datasetName);
                    int sortChoice;
                    cout << "Enter your choice: ";
                    cin >> sortChoice;

                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(10000, '\n');
                        cout << "\nInvalid input!\n";
                        pressEnterToContinue();
                        continue;
                    }

                    switch (sortChoice) {
                        case 1:
                            sortByAge(*dataset, datasetName);
                            break;
                        case 2:
                            sortByDistance(*dataset, datasetName);
                            break;
                        case 3:
                            sortByEmission(*dataset, datasetName);
                            break;
                        case 4:
                            sortRunning = false;
                            break;
                        default:
                            cout << "\nInvalid choice! Please try again.\n";
                            pressEnterToContinue();
                    }
                }
                break;
            }
            case 3: {
                int datasetChoice = selectDataset("SEARCH FROM");
                if (datasetChoice == 0) break;
                DynamicArray* dataset = getDatasetByChoice(datasetChoice);
                string datasetName = getDatasetName(datasetChoice);
                bool searchRunning = true;
                while (searchRunning) {
                    displaySearchingMenu(datasetName);
                    int searchChoice;
                    cout << "Enter your choice: ";
                    cin >> searchChoice;

                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(10000, '\n');
                        cout << "\nInvalid input!\n";
                        pressEnterToContinue();
                        continue;
                    }

                    switch (searchChoice) {
                        case 1:
                            searchByAgeGroup(*dataset, datasetName);
                            break;
                        case 2:
                            searchByTransportMode(*dataset, datasetName);
                            break;
                        case 3:
                            searchByDistance(*dataset, datasetName);
                            break;
                        case 4:
                            searchRunning = false;
                            break;
                        default:
                            cout << "\nInvalid choice! Please try again.\n";
                            pressEnterToContinue();
                    }
                }
                break;
            }
            case 4: {
                bool carbonRunning = true;
                while (carbonRunning) {
                    displayCarbonEmissionMenu();
                    int carbonChoice;
                    cout << "Enter your choice: ";
                    cin >> carbonChoice;

                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(10000, '\n');
                        cout << "\nInvalid input!\n";
                        pressEnterToContinue();
                        continue;
                    }

                    switch (carbonChoice) {
                        case 1:
                            totalEmissionPerCity();
                            break;
                        case 2:
                            emissionByTransportMode();
                            break;
                        case 3:
                            compareEmissionByCity();
                            break;
                        case 4:
                            carbonRunning = false;
                            break;
                        default:
                            cout << "\nInvalid choice! Please try again.\n";
                            pressEnterToContinue();
                    }
                }
                break;
            }
            case 5: {
                int datasetChoice = selectDataset("ANALYZE AGE GROUPS FROM");
                if (datasetChoice == 0) break;
                DynamicArray* dataset = getDatasetByChoice(datasetChoice);
                string datasetName = getDatasetName(datasetChoice);
                displayAgeGroupReport(*dataset, datasetName);
                break;
            }
            case 6:
                performanceAnalysis();
                break;
            case 7:
                cout << "\n=============================================\n";
                cout << "Thank you for using Urban Carbon Emission Analysis System!\n";
                cout << "Goodbye!\n";
                cout << "=============================================\n";
                running = false;
                break;
            default:
                cout << "\nInvalid choice! Please enter a number between 1 and 7.\n";
                pressEnterToContinue();
        }
    }

    return 0;
}


void displayMainMenu() {
    system("cls");  
    string header = "URBAN CARBON EMISSION ANALYSIS SYSTEM (Array)";
    printHeader(header);
    cout << "1. Display Residents\n";
    cout << "2. Sorting Operations\n";
    cout << "3. Searching Operations\n";
    cout << "4. Carbon Emission Analysis\n";
    cout << "5. Age Group Analysis\n";
    cout << "6. Dataset Information\n";
    cout << "7. Exit\n";
    printSeparator();
}

void displaySortingMenu(const string& datasetName) {
    system("cls");
    printHeader("SORT FROM " + datasetName);
    cout << "1. Sort by Age\n";
    cout << "2. Sort by Daily Distance\n";
    cout << "3. Sort by Carbon Emission\n";
    cout << "4. Previous\n";
    printSeparator();
}

void displaySearchingMenu(const string& datasetName) {
    system("cls");
    printHeader("SEARCH FROM " + datasetName);
    cout << "1. Search by Age Group\n";
    cout << "2. Search by Transport Mode\n";
    cout << "3. Search by Distance > Value\n";
    cout << "4. Previous\n";
    printSeparator();
}

void displayCarbonEmissionMenu() {
    system("cls");
    printHeader("CARBON EMISSION ANALYSIS");
    cout << "1. Total Emission per City\n";
    cout << "2. Emission by Transport Mode\n";
    cout << "3. Compare Age group Emission\n";
    cout << "4. Back to Main Menu\n";
    printSeparator();
}

void displayAgeGroupReport(DynamicArray& dataset, const string& datasetName) {
    system("cls");
    printHeader("AGE GROUP ANALYSIS FROM " + datasetName);

    Analysis analysis;
    analysis.displayAgeGroupAnalysisSummary(dataset, datasetName);

    pressEnterToContinue();
}

void initializeDataSelection() {
    selectedCityName = "Array";
    selectedCityMode = 4;

    string filenames[] = {
        FileIO::getFilePath(1),
        FileIO::getFilePath(2),
        FileIO::getFilePath(3)
    };

    mainArray.clear();
    cityAArray.clear();
    cityBArray.clear();
    cityCArray.clear();

    bool loadedA = FileIO::loadFromCSV(filenames[0], cityAArray);
    bool loadedB = FileIO::loadFromCSV(filenames[1], cityBArray);
    bool loadedC = FileIO::loadFromCSV(filenames[2], cityCArray);

    for (int i = 0; i < cityAArray.getSize(); i++) {
        mainArray.append(cityAArray[i]);
    }
    for (int i = 0; i < cityBArray.getSize(); i++) {
        mainArray.append(cityBArray[i]);
    }
    for (int i = 0; i < cityCArray.getSize(); i++) {
        mainArray.append(cityCArray[i]);
    }

    if (!loadedA || !loadedB || !loadedC) {
        cout << "Warning: One or more datasets failed to load.\n";
        if (!loadedA) cout << "  - City A failed to load\n";
        if (!loadedB) cout << "  - City B failed to load\n";
        if (!loadedC) cout << "  - City C failed to load\n";
        cout << "Press Enter to continue to the main menu...";
        cin.ignore(10000, '\n');
        cin.get();
    }
}

int selectDataset(const string& action) {
    while (true) {
        system("cls");
        printHeader(action);
        cout << "1. City A (Metropolitan City)\n";
        cout << "2. City B (University Town)\n";
        cout << "3. City C (Suburban/Rural)\n";
        cout << "4. All Cities\n";
        cout << "5. Back to Main Menu\n";
        cout << "Enter your choice (1-5): ";

        int choice;
        cin >> choice;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "\nInvalid input! Please enter a number between 1 and 5.\n";
            pressEnterToContinue();
            continue;
        }

        if (choice >= 1 && choice <= 4) {
            return choice;
        } else if (choice == 5) {
            return 0;
        } else {
            cout << "\nInvalid choice! Please select 1-5.\n";
            pressEnterToContinue();
        }
    }
}

DynamicArray* getDatasetByChoice(int choice) {
    switch (choice) {
        case 1:
            return &cityAArray;
        case 2:
            return &cityBArray;
        case 3:
            return &cityCArray;
        default:
            return &mainArray;
    }
}

string getDatasetName(int choice) {
    switch (choice) {
        case 1:
            return "City A (Metropolitan City)";
        case 2:
            return "City B (University Town)";
        case 3:
            return "City C (Suburban/Rural)";
        default:
            return "All Cities";
    }
}


void displayAllRecords(DynamicArray& dataset, int datasetChoice) {
    system("cls");
    printHeader("DISPLAY RESIDENTS");
    
    if (dataset.getSize() == 0) {
        cout << "No records available for the selected dataset.\n";
        pressEnterToContinue();
        return;
    }

    cout << left << setw(10) << "ID" 
         << setw(8) << "Age" 
         << setw(15) << "Transport" 
         << setw(15) << "Dist(km)" 
         << setw(15) << "CO2 Factor" 
         << setw(15) << "Days/Mo" 
         << setw(15) << "Monthly CO2\n";
    printSeparator();

    if (datasetChoice == 4) {
        if (cityAArray.getSize() > 0) {
            cout << "\n--- CITY A (Metropolitan City) ---\n";
            for (int i = 0; i < cityAArray.getSize(); i++) {
                Record& r = cityAArray[i];
                double monthlyCO2 = r.carbonEmissionFactor * r.dailyDistance * r.averageDaysPerMonth;
                cout << left << setw(10) << ("A-" + to_string(r.residentID)) 
                     << setw(8) << r.age 
                     << setw(15) << r.transportMode 
                     << setw(15) << fixed << setprecision(2) << r.dailyDistance 
                     << setw(15) << fixed << setprecision(2) << r.carbonEmissionFactor 
                     << setw(15) << r.averageDaysPerMonth 
                     << setw(15) << fixed << setprecision(2) << monthlyCO2 << "\n";
            }
        }
        if (cityBArray.getSize() > 0) {
            cout << "\n--- CITY B (University Town) ---\n";
            for (int i = 0; i < cityBArray.getSize(); i++) {
                Record& r = cityBArray[i];
                double monthlyCO2 = r.carbonEmissionFactor * r.dailyDistance * r.averageDaysPerMonth;
                cout << left << setw(10) << ("B-" + to_string(r.residentID)) 
                     << setw(8) << r.age 
                     << setw(15) << r.transportMode 
                     << setw(15) << fixed << setprecision(2) << r.dailyDistance 
                     << setw(15) << fixed << setprecision(2) << r.carbonEmissionFactor 
                     << setw(15) << r.averageDaysPerMonth 
                     << setw(15) << fixed << setprecision(2) << monthlyCO2 << "\n";
            }
        }
        if (cityCArray.getSize() > 0) {
            cout << "\n--- CITY C (Suburban/Rural) ---\n";
            for (int i = 0; i < cityCArray.getSize(); i++) {
                Record& r = cityCArray[i];
                double monthlyCO2 = r.carbonEmissionFactor * r.dailyDistance * r.averageDaysPerMonth;
                cout << left << setw(10) << ("C-" + to_string(r.residentID)) 
                     << setw(8) << r.age 
                     << setw(15) << r.transportMode 
                     << setw(15) << fixed << setprecision(2) << r.dailyDistance 
                     << setw(15) << fixed << setprecision(2) << r.carbonEmissionFactor 
                     << setw(15) << r.averageDaysPerMonth 
                     << setw(15) << fixed << setprecision(2) << monthlyCO2 << "\n";
            }
        }
    } else {
        char cityLetter = (datasetChoice == 1) ? 'A' : (datasetChoice == 2) ? 'B' : 'C';
        for (int i = 0; i < dataset.getSize(); i++) {
            Record& r = dataset[i];
            double monthlyCO2 = r.carbonEmissionFactor * r.dailyDistance * r.averageDaysPerMonth;
            cout << left << setw(10) << (string(1, cityLetter) + "-" + to_string(r.residentID)) 
                 << setw(8) << r.age 
                 << setw(15) << r.transportMode 
                 << setw(15) << fixed << setprecision(2) << r.dailyDistance 
                 << setw(15) << fixed << setprecision(2) << r.carbonEmissionFactor 
                 << setw(15) << r.averageDaysPerMonth 
                 << setw(15) << fixed << setprecision(2) << monthlyCO2 << "\n";
        }
    }

    pressEnterToContinue();
}


void sortByAge(DynamicArray& dataset, const string& datasetName) {
    system("cls");
    printHeader("SORT BY AGE FROM " + datasetName);
    
    if (dataset.getSize() == 0) {
        cout << "No records available for the selected dataset.\n";
        pressEnterToContinue();
        return;
    }

    cout << "Select sorting algorithm:\n";
    cout << "1. Bubble Sort\n";
    cout << "2. Quick Sort\n";
    cout << "3. Merge Sort\n";
    cout << "Enter choice (1-3): ";

    int choice;
    cin >> choice;

    if (cin.fail()) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid input!\n";
        pressEnterToContinue();
        return;
    }

    DynamicArray tempArray;
    tempArray.copyFrom(dataset);

    long long executionTime = 0;

    switch (choice) {
        case 1:
            cout << "\nSorting by Age using Bubble Sort...\n";
            executionTime = Sorting::bubbleSortByAge(tempArray);
            break;
        case 2:
            cout << "\nSorting by Age using Quick Sort...\n";
            executionTime = Sorting::quickSortByAge(tempArray);
            break;
        case 3:
            cout << "\nSorting by Age using Merge Sort...\n";
            executionTime = Sorting::mergeSortByAge(tempArray);
            break;
        default:
            cout << "Invalid choice!\n";
            pressEnterToContinue();
            return;
    }

    cout << "Execution Time: " << executionTime << " ms\n";
    cout << "Memory Used: " << tempArray.getMemoryUsed() / 1024.0 << " KB\n\n";

    cout << "Display sorted results? (Y/N): ";
    char displayChoice;
    cin >> displayChoice;

    if (displayChoice == 'Y' || displayChoice == 'y') {
        tempArray.display();
    }

    lastOperationTime = executionTime;
    pressEnterToContinue();
}

void sortByDistance(DynamicArray& dataset, const string& datasetName) {
    system("cls");
    printHeader("SORT BY DAILY DISTANCE FROM " + datasetName);
    
    if (dataset.getSize() == 0) {
        cout << "No records available for the selected dataset.\n";
        pressEnterToContinue();
        return;
    }

    cout << "Select sorting algorithm:\n";
    cout << "1. Bubble Sort\n";
    cout << "2. Quick Sort\n";
    cout << "3. Merge Sort\n";
    cout << "Enter choice (1-3): ";

    int choice;
    cin >> choice;

    if (cin.fail()) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid input!\n";
        pressEnterToContinue();
        return;
    }

    DynamicArray tempArray;
    tempArray.copyFrom(dataset);

    long long executionTime = 0;

    switch (choice) {
        case 1:
            cout << "\nSorting by Daily Distance using Bubble Sort...\n";
            executionTime = Sorting::bubbleSortByDistance(tempArray);
            break;
        case 2:
            cout << "\nSorting by Daily Distance using Quick Sort...\n";
            executionTime = Sorting::quickSortByDistance(tempArray);
            break;
        case 3:
            cout << "\nSorting by Daily Distance using Merge Sort...\n";
            executionTime = Sorting::mergeSortByDistance(tempArray);
            break;
        default:
            cout << "Invalid choice!\n";
            pressEnterToContinue();
            return;
    }

    cout << "Execution Time: " << executionTime << " ms\n";
    cout << "Memory Used: " << tempArray.getMemoryUsed() / 1024.0 << " KB\n\n";

    cout << "Display sorted results? (Y/N): ";
    char displayChoice;
    cin >> displayChoice;

    if (displayChoice == 'Y' || displayChoice == 'y') {
        tempArray.display();
    }

    lastOperationTime = executionTime;
    pressEnterToContinue();
}

void sortByEmission(DynamicArray& dataset, const string& datasetName) {
    system("cls");
    printHeader("SORT BY CARBON EMISSION FROM " + datasetName);
    
    if (dataset.getSize() == 0) {
        cout << "No records available for the selected dataset.\n";
        pressEnterToContinue();
        return;
    }

    cout << "Select sorting algorithm:\n";
    cout << "1. Bubble Sort\n";
    cout << "2. Quick Sort\n";
    cout << "3. Merge Sort\n";
    cout << "Enter choice (1-3): ";

    int choice;
    cin >> choice;

    if (cin.fail()) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid input!\n";
        pressEnterToContinue();
        return;
    }

    DynamicArray tempArray;
    tempArray.copyFrom(dataset);

    long long executionTime = 0;

    switch (choice) {
        case 1:
            cout << "\nSorting by Carbon Emission using Bubble Sort...\n";
            executionTime = Sorting::bubbleSortByEmission(tempArray);
            break;
        case 2:
            cout << "\nSorting by Carbon Emission using Quick Sort...\n";
            executionTime = Sorting::quickSortByEmission(tempArray);
            break;
        case 3:
            cout << "\nSorting by Carbon Emission using Merge Sort...\n";
            executionTime = Sorting::mergeSortByEmission(tempArray);
            break;
        default:
            cout << "Invalid choice!\n";
            pressEnterToContinue();
            return;
    }

    cout << "Execution Time: " << executionTime << " ms\n";
    cout << "Memory Used: " << tempArray.getMemoryUsed() / 1024.0 << " KB\n\n";

    cout << "Display sorted results? (Y/N): ";
    char displayChoice;
    cin >> displayChoice;

    if (displayChoice == 'Y' || displayChoice == 'y') {
        tempArray.display();
    }

    lastOperationTime = executionTime;
    pressEnterToContinue();
}


void searchByAgeGroup(DynamicArray& dataset, const string& datasetName) {
    system("cls");
    printHeader("SEARCH BY AGE GROUP FROM " + datasetName);
    
    if (dataset.getSize() == 0) {
        cout << "No records available for the selected dataset.\n";
        pressEnterToContinue();
        return;
    }

    cout << "Age Groups:\n";
    cout << "1. 6-17 years\n";
    cout << "2. 18-25 years\n";
    cout << "3. 26-45 years\n";
    cout << "4. 46-60 years\n";
    cout << "5. 61-100 years\n";
    cout << "Select age group: ";
    int choice;
    cin >> choice;

    if (cin.fail()) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "\nInvalid input!\n";
        pressEnterToContinue();
        return;
    }

    string ageGroups[] = {"6-17", "18-25", "26-45", "46-60", "61-100"};
    if (choice < 1 || choice > 5) {
        cout << "Invalid choice!\n";
        pressEnterToContinue();
        return;
    }

    int algorithmChoice = selectSearchAlgorithm();
    if (algorithmChoice == 0) {
        cout << "Invalid choice!\n";
        pressEnterToContinue();
        return;
    }

    DynamicArray results;
    long long searchTime = 0;
    if (algorithmChoice == 1) {
        searchTime = Searching::searchByAgeGroup(dataset, ageGroups[choice - 1], results);
    } else {
        searchTime = Searching::binarySearchByAgeGroup(dataset, ageGroups[choice - 1], results);
    }

    cout << "\nSearch Results for Age Group: " << ageGroups[choice - 1] << "\n";
    cout << "Search Method: " << (algorithmChoice == 1 ? "Linear Search" : "Binary Search") << "\n";
    cout << "Records Found: " << results.getSize() << "\n";
    cout << "Search Time: " << searchTime << " ms\n\n";

    if (results.getSize() > 0) {
        results.display();
    }

    lastOperationTime = searchTime;
    pressEnterToContinue();
}

void searchByTransportMode(DynamicArray& dataset, const string& datasetName) {
    system("cls");
    printHeader("SEARCH BY TRANSPORT MODE FROM " + datasetName);
    
    if (dataset.getSize() == 0) {
        cout << "No records available for the selected dataset.\n";
        pressEnterToContinue();
        return;
    }

    cout << "Select transport mode:\n";
    cout << "1. Car\n";
    cout << "2. Bus\n";
    cout << "3. Bicycle\n";
    cout << "4. Walking\n";
    cout << "5. School Bus\n";
    cout << "6. Carpool\n";
    cout << "Select transport mode: ";
    int choice;
    cin >> choice;

    if (cin.fail()) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "\nInvalid input!\n";
        pressEnterToContinue();
        return;
    }

    string modes[] = {"Car", "Bus", "Bicycle", "Walking", "School Bus", "Carpool"};
    if (choice < 1 || choice > 6) {
        cout << "Invalid choice!\n";
        pressEnterToContinue();
        return;
    }

    int algorithmChoice = selectSearchAlgorithm();
    if (algorithmChoice == 0) {
        cout << "Invalid choice!\n";
        pressEnterToContinue();
        return;
    }

    DynamicArray results;
    long long searchTime = 0;
    if (algorithmChoice == 1) {
        searchTime = Searching::linearSearchByTransport(dataset, modes[choice - 1], results);
    } else {
        searchTime = Searching::binarySearchByTransport(dataset, modes[choice - 1], results);
    }

    cout << "\nSearch Results for Transport Mode: " << modes[choice - 1] << "\n";
    cout << "Search Method: " << (algorithmChoice == 1 ? "Linear Search" : "Binary Search") << "\n";
    cout << "Records Found: " << results.getSize() << "\n";
    cout << "Search Time: " << searchTime << " ms\n\n";

    if (results.getSize() > 0) {
        results.display();
    }

    lastOperationTime = searchTime;
    pressEnterToContinue();
}

void searchByDistance(DynamicArray& dataset, const string& datasetName) {
    system("cls");
    printHeader("SEARCH BY DISTANCE FROM " + datasetName);
    
    if (dataset.getSize() == 0) {
        cout << "No records available for the selected dataset.\n";
        pressEnterToContinue();
        return;
    }

    cout << "Enter distance value (km): ";
    double distance;
    cin >> distance;

    if (cin.fail()) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "\nInvalid input!\n";
        pressEnterToContinue();
        return;
    }

    int algorithmChoice = selectSearchAlgorithm();
    if (algorithmChoice == 0) {
        cout << "Invalid choice!\n";
        pressEnterToContinue();
        return;
    }

    DynamicArray results;
    long long searchTime = 0;
    if (algorithmChoice == 1) {
        searchTime = Searching::linearSearchByDistance(dataset, distance, results);
    } else {
        searchTime = Searching::binarySearchByDistanceGreaterThan(dataset, distance, results);
    }

    cout << "\nSearch Results for Distance > " << distance << " km\n";
    cout << "Search Method: " << (algorithmChoice == 1 ? "Linear Search" : "Binary Search") << "\n";
    cout << "Records Found: " << results.getSize() << "\n";
    cout << "Search Time: " << searchTime << " ms\n\n";

    if (results.getSize() > 0) {
        results.display();
    }

    lastOperationTime = searchTime;
    pressEnterToContinue();
}


void totalEmissionPerCity() {
    system("cls");
    printHeader("TOTAL EMISSION PER CITY");
    
    if (mainArray.getSize() == 0) {
        cout << "No records loaded. Please load a dataset first.\n";
        pressEnterToContinue();
        return;
    }

    cout << "\n[Total Emissions per Dataset]\n";
    cout << string(60, '-') << "\n";
    cout << left << setw(35) << "Dataset" << setw(15) << "Records" << setw(15) << "Total Emission (kg CO2)\n";
    cout << string(60, '-') << "\n";
    
    double emissionA = Analysis::calculateTotalEmission(cityAArray);
    double emissionB = Analysis::calculateTotalEmission(cityBArray);
    double emissionC = Analysis::calculateTotalEmission(cityCArray);
    
    cout << left << setw(35) << "City A (Metropolitan)" << setw(15) << cityAArray.getSize() << setw(15) << fixed << setprecision(2) << emissionA << "\n";
    cout << left << setw(35) << "City B (University Town)" << setw(15) << cityBArray.getSize() << setw(15) << fixed << setprecision(2) << emissionB << "\n";
    cout << left << setw(35) << "City C (Suburban/Rural)" << setw(15) << cityCArray.getSize() << setw(15) << fixed << setprecision(2) << emissionC << "\n";
    cout << string(60, '-') << "\n";
    
    pressEnterToContinue();
}

void emissionByTransportMode() {
    system("cls");
    printHeader("EMISSION BY TRANSPORT MODE");
    
    if (mainArray.getSize() == 0) {
        cout << "No records available.\n";
        pressEnterToContinue();
        return;
    }

    cout << "\n[Emissions per Mode of Transport by Dataset]\n";
    cout << string(90, '-') << "\n";
    cout << left << setw(20) << "Mode" << setw(20) << "City A (kg CO2)" << setw(20) << "City B (kg CO2)" << setw(20) << "City C (kg CO2)\n";
    cout << string(90, '-') << "\n";
    
    string modes[] = {"Car", "Bus", "Bicycle", "Walking", "School Bus", "Carpool"};
    int modesSize = 6;
    for (int m = 0; m < modesSize; m++) {
        const string& mode = modes[m];
        double emissionA = Analysis::calculateEmissionByTransportMode(cityAArray, mode);
        double emissionB = Analysis::calculateEmissionByTransportMode(cityBArray, mode);
        double emissionC = Analysis::calculateEmissionByTransportMode(cityCArray, mode);
        cout << left << setw(20) << mode 
             << setw(20) << fixed << setprecision(2) << emissionA 
             << setw(20) << fixed << setprecision(2) << emissionB 
             << setw(20) << fixed << setprecision(2) << emissionC << "\n";
    }
    cout << string(90, '-') << "\n";
    
    pressEnterToContinue();
}

void compareEmissionByCity() {
        system("cls");
        printHeader("COMPARE AGE GROUP EMISSION BY CITY");
        string ageGroups[] = {"6-17", "18-25", "26-45", "46-60", "61-100"};
        cout << left << setw(15) << "Age Group"
            << setw(20) << "City A (kg CO2)"
            << setw(20) << "City B (kg CO2)"
            << setw(20) << "City C (kg CO2)" << "\n";
        cout << string(75, '-') << "\n";
        for (int i = 0; i < 5; i++) {
           const string& ag = ageGroups[i];
           double emissionA = Analysis::getTotalEmissionByAgeGroup(cityAArray, ag);
           double emissionB = Analysis::getTotalEmissionByAgeGroup(cityBArray, ag);
           double emissionC = Analysis::getTotalEmissionByAgeGroup(cityCArray, ag);
           cout << left << setw(15) << ag
               << setw(20) << fixed << setprecision(2) << emissionA
               << setw(20) << fixed << setprecision(2) << emissionB
               << setw(20) << fixed << setprecision(2) << emissionC << "\n";
        }
        cout << string(75, '-') << "\n";
        pressEnterToContinue();
}


void mostPreferredTransport(DynamicArray& dataset, const string& datasetName) {
    system("cls");
    printHeader("MOST PREFERRED TRANSPORT BY AGE GROUP FROM " + datasetName);
    
    if (dataset.getSize() == 0) {
        cout << "No records available for the selected dataset.\n";
        pressEnterToContinue();
        return;
    }

    Analysis::displayMostPreferredTransport(dataset);
    
    pressEnterToContinue();
}

void totalEmissionByAgeGroup(DynamicArray& dataset, const string& datasetName) {
    system("cls");
    printHeader("TOTAL EMISSION BY AGE GROUP FROM " + datasetName);
    
    if (dataset.getSize() == 0) {
        cout << "No records available for the selected dataset.\n";
        pressEnterToContinue();
        return;
    }

    Analysis::displayEmissionByAgeGroup(dataset);
    
    pressEnterToContinue();
}

void averageEmissionPerResident(DynamicArray& dataset, const string& datasetName) {
    system("cls");
    printHeader("AVERAGE EMISSION PER RESIDENT BY AGE GROUP FROM " + datasetName);
    
    if (dataset.getSize() == 0) {
        cout << "No records available for the selected dataset.\n";
        pressEnterToContinue();
        return;
    }

    Analysis::displayAverageEmissionPerResident(dataset);
    
    pressEnterToContinue();
}


void performanceAnalysis() {
    system("cls");
    printHeader("DATASET INFORMATION");
    if (mainArray.getSize() == 0) {
        cout << "No records loaded. Please load a dataset first.\n";
        pressEnterToContinue();
        return;
    }
    cout << "Dataset Information:\n";
    cout << "- Total Records: " << mainArray.getSize() << "\n";
    cout << "- Memory Used: " << fixed << setprecision(2) << mainArray.getMemoryUsed() / 1024.0 << " KB\n\n";
    pressEnterToContinue();
}

int selectSearchAlgorithm() {
    cout << "\nSelect search algorithm:\n";
    cout << "1. Linear Search\n";
    cout << "2. Binary Search\n";
    cout << "Enter choice (1-2): ";
    int choice;
    cin >> choice;

    if (cin.fail()) {
        cin.clear();
        cin.ignore(10000, '\n');
        return 0;
    }
    if (choice < 1 || choice > 2) {
        return 0;
    }

    return choice;
}

void printSeparator() {
    cout << "=============================================\n";
}

void printHeader(const string& title) {
    printSeparator();
    cout << title << "\n";
    printSeparator();
}

void pressEnterToContinue() {
    cout << "\nPress Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}
