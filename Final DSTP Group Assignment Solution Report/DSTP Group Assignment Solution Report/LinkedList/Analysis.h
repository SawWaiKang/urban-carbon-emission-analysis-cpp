#ifndef ANALYSIS_H
#define ANALYSIS_H

#include "LinkedList.h"
#include <string>
#include <iostream>
using namespace std;


class Analysis {
public:
    static double calculateTotalEmission(const LinkedList& list);
    static double calculateTotalEmissionByCity(const LinkedList& list, const string& city);
    static double calculateEmissionByTransportMode(const LinkedList& list, const string& mode);

    static void displayEmissionByTransportMode(const LinkedList& list);
    static void displayEmissionByAgeGroup(const LinkedList& list);
    static void displayAverageEmissionPerResident(const LinkedList& list);
    static void displayMostPreferredTransport(const LinkedList& list);
    static void displayComparisonByCity(const LinkedList& cityA, const LinkedList& cityB, const LinkedList& cityC);
    static void displayAgeGroupAnalysisSummary(const LinkedList& list, const string& cityName);

    static int countResidentsByAgeGroup(const LinkedList& list, const string& ageGroup);
    static string getMostPreferredTransportByAgeGroup(const LinkedList& list, const string& ageGroup);
    static double getAveragePollutionByAgeGroup(const LinkedList& list, const string& ageGroup);
    static double getTotalEmissionByAgeGroup(const LinkedList& list, const string& ageGroup);
    static double getTotalEmissionByAgeGroupAndMode(const LinkedList& list, const std::string& ageGroup, const std::string& mode);

    static void analyzeDataset(const LinkedList& list, const string& cityName);

private:
    static int countTransportByAgeGroup(const LinkedList& list, const string& ageGroup, const string& mode);
};

#endif
