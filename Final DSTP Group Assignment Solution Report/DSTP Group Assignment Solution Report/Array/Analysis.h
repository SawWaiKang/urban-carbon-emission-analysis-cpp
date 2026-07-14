#ifndef ANALYSIS_H
#define ANALYSIS_H

#include "Array.h"
#include <string>
#include <iostream>
using namespace std;


class Analysis {
public:
    static double calculateTotalEmission(const DynamicArray& arr);
    static double calculateTotalEmissionByCity(const DynamicArray& arr, const string& city);
    static double calculateEmissionByTransportMode(const DynamicArray& arr, const string& mode);

    static void displayEmissionByTransportMode(const DynamicArray& arr);
    static void displayEmissionByAgeGroup(const DynamicArray& arr);
    static void displayAverageEmissionPerResident(const DynamicArray& arr);
    static void displayMostPreferredTransport(const DynamicArray& arr);
    static void displayComparisonByCity(const DynamicArray& cityA, const DynamicArray& cityB, const DynamicArray& cityC);

    static int countResidentsByAgeGroup(const DynamicArray& arr, const string& ageGroup);
    static string getMostPreferredTransportByAgeGroup(const DynamicArray& arr, const string& ageGroup);
    static double getAveragePollutionByAgeGroup(const DynamicArray& arr, const string& ageGroup);
    static double getTotalEmissionByAgeGroup(const DynamicArray& arr, const string& ageGroup);
    static double getTotalEmissionByAgeGroupAndMode(const DynamicArray& arr, const std::string& ageGroup, const std::string& mode);

    static void analyzeDataset(const DynamicArray& arr, const string& cityName);
    static void displayAgeGroupAnalysisSummary(const DynamicArray& arr, const string& cityName);

private:
    static int countTransportByAgeGroup(const DynamicArray& arr, const string& ageGroup, const string& mode);
};

#endif 
