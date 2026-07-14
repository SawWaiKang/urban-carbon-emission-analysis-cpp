#include "Analysis.h"
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;


// Returns total emission for a given age group and transport mode
double Analysis::getTotalEmissionByAgeGroupAndMode(const LinkedList& list, const string& ageGroup, const string& mode) {
    double total = 0.0;
    int size = list.getSize();
    for (int i = 0; i < size; i++) {
        if (list[i].getAgeGroup() == ageGroup && list[i].transportMode == mode) {
            total += list[i].calculateMonthlyEmission();
        }
    }
    return total;
}


double Analysis::calculateTotalEmission(const LinkedList& list) {
    double total = 0.0;
    int size = list.getSize();

    for (int i = 0; i < size; i++) {
        total += list[i].calculateMonthlyEmission();
    }

    return total;
}

double Analysis::calculateTotalEmissionByCity(const LinkedList& list, const string& city) {
    
    return calculateTotalEmission(list);
}

double Analysis::calculateEmissionByTransportMode(const LinkedList& list, const string& mode) {
    double total = 0.0;
    int size = list.getSize();

    for (int i = 0; i < size; i++) {
        if (list[i].transportMode == mode) {
            total += list[i].calculateMonthlyEmission();
        }
    }

    return total;
}


void Analysis::displayEmissionByTransportMode(const LinkedList& list) {
    cout << "\n" << setw(20) << "Transport Mode" << setw(25) << "Total Emission (kg CO2)\n";
    cout << string(45, '-') << "\n";

    string modes[] = {"Car", "Bus", "Bicycle", "Walking", "School Bus", "Carpool"};

    for (const string& mode : modes) {
        double emission = calculateEmissionByTransportMode(list, mode);
        cout << setw(20) << mode << setw(25) << fixed << setprecision(2) << emission << "\n";
    }
    cout << "\n";
}

int Analysis::countTransportByAgeGroup(const LinkedList& list, const string& ageGroup, const string& mode) {
    int count = 0;
    int size = list.getSize();

    for (int i = 0; i < size; i++) {
        if (list[i].getAgeGroup() == ageGroup && list[i].transportMode == mode) {
            count++;
        }
    }

    return count;
}

void Analysis::displayEmissionByAgeGroup(const LinkedList& list) {
    string ageGroups[] = {"6-17", "18-25", "26-45", "46-60", "61-100"};

    cout << "\n" << setw(15) << "Age Group" << setw(25) << "Total Emission (kg CO2)\n";
    cout << string(40, '-') << "\n";

    for (const string& ag : ageGroups) {
        double emission = getTotalEmissionByAgeGroup(list, ag);
        if (emission > 0) {
            cout << setw(15) << ag << setw(25) << fixed << setprecision(2) << emission << "\n";
        }
    }
    cout << "\n";
}

void Analysis::displayAverageEmissionPerResident(const LinkedList& list) {
    string ageGroups[] = {"6-17", "18-25", "26-45", "46-60", "61-100"};

    cout << "\n" << setw(15) << "Age Group" << setw(35) << "Avg Emission per Resident (kg CO2)\n";
    cout << string(50, '-') << "\n";

    for (const string& ag : ageGroups) {
        int count = countResidentsByAgeGroup(list, ag);
        if (count > 0) {
            double avg = getAveragePollutionByAgeGroup(list, ag);
            cout << setw(15) << ag << setw(35) << fixed << setprecision(2) << avg << "\n";
        }
    }
    cout << "\n";
}

void Analysis::displayMostPreferredTransport(const LinkedList& list) {
    string ageGroups[] = {"6-17", "18-25", "26-45", "46-60", "61-100"};

    cout << "\n" << setw(15) << "Age Group" << setw(25) << "Preferred Transport\n";
    cout << string(40, '-') << "\n";

    for (const string& ag : ageGroups) {
        int count = countResidentsByAgeGroup(list, ag);
        if (count > 0) {
            string preferred = getMostPreferredTransportByAgeGroup(list, ag);
            cout << setw(15) << ag << setw(25) << preferred << "\n";
        }
    }
    cout << "\n";
}

void Analysis::displayComparisonByCity(const LinkedList& cityA, const LinkedList& cityB, const LinkedList& cityC) {
    cout << "\n" << setw(15) << "City" << setw(25) << "Total Emission (kg CO2)" << setw(20) << "Avg Emission\n";
    cout << string(60, '-') << "\n";

    LinkedList cities[3] = {cityA, cityB, cityC};
    string cityNames[] = {"City A", "City B", "City C"};

    for (int i = 0; i < 3; i++) {
        double totalEmission = calculateTotalEmission(cities[i]);
        double avgEmission = cities[i].getSize() > 0 ? totalEmission / cities[i].getSize() : 0;

        cout << setw(15) << cityNames[i]
             << setw(25) << fixed << setprecision(2) << totalEmission
             << setw(20) << fixed << setprecision(2) << avgEmission << "\n";
    }
    cout << "\n";
}


int Analysis::countResidentsByAgeGroup(const LinkedList& list, const string& ageGroup) {
    int count = 0;
    int size = list.getSize();

    for (int i = 0; i < size; i++) {
        if (list[i].getAgeGroup() == ageGroup) {
            count++;
        }
    }

    return count;
}

string Analysis::getMostPreferredTransportByAgeGroup(const LinkedList& list, const string& ageGroup) {
    string modes[] = {"Car", "Bus", "Bicycle", "Walking", "School Bus", "Carpool"};
    int maxCount = 0;
    string mostPreferred = "None";

    for (const string& mode : modes) {
        int count = countTransportByAgeGroup(list, ageGroup, mode);
        if (count > maxCount) {
            maxCount = count;
            mostPreferred = mode;
        }
    }

    return mostPreferred;
}

double Analysis::getAveragePollutionByAgeGroup(const LinkedList& list, const string& ageGroup) {
    int count = countResidentsByAgeGroup(list, ageGroup);
    if (count == 0) return 0.0;

    double total = getTotalEmissionByAgeGroup(list, ageGroup);
    return total / count;
}

double Analysis::getTotalEmissionByAgeGroup(const LinkedList& list, const string& ageGroup) {
    double total = 0.0;
    int size = list.getSize();

    for (int i = 0; i < size; i++) {
        if (list[i].getAgeGroup() == ageGroup) {
            total += list[i].calculateMonthlyEmission();
        }
    }

    return total;
}


void Analysis::analyzeDataset(const LinkedList& list, const string& cityName) {
    cout << "\n" << string(60, '=') << "\n";
    cout << "COMPREHENSIVE ANALYSIS - " << cityName << "\n";
    cout << string(60, '=') << "\n";

    cout << "\nTotal Records: " << list.getSize() << "\n";
    cout << "Total Emission: " << fixed << setprecision(2) << calculateTotalEmission(list) << " kg CO2\n";

    cout << "\n--- EMISSION BY TRANSPORT MODE ---\n";
    displayEmissionByTransportMode(list);

    cout << "\n--- EMISSION BY AGE GROUP ---\n";
    displayEmissionByAgeGroup(list);

    cout << "\n--- AVERAGE EMISSION PER RESIDENT (BY AGE GROUP) ---\n";
    displayAverageEmissionPerResident(list);

    cout << "\n--- MOST PREFERRED TRANSPORT (BY AGE GROUP) ---\n";
    displayMostPreferredTransport(list);

    cout << string(60, '=') << "\n\n";
}

void Analysis::displayAgeGroupAnalysisSummary(const LinkedList& list, const string& cityName) {
    string ageGroups[] = {"6-17", "18-25", "26-45", "46-60", "61-100"};
    string ageLabels[] = {
        "Children",
        "Young Adults",
        "Working Adults - Early Career",
        "Working Adults - Late Career",
        "Senior Citizens"
    };
    string modes[] = {"Car", "Bus", "Bicycle", "Walking", "School Bus", "Carpool"};

    string mostEmissionAgeGroup = "-";
    double maxEmission = 0.0;
    string mostPreferredTransport = "-";
    string mostPreferredTransportGroup = "-";
    int mostPreferredTransportCount = 0;

    for (int i = 0; i < 5; i++) {
        const string& ag = ageGroups[i];
        int totalResidents = countResidentsByAgeGroup(list, ag);
        if (totalResidents == 0) continue;

        cout << "Age Group: " << ag << " (" << ageLabels[i] << ")\n";
        cout << "------------------------------------------------------------\n";
        cout << left << setw(20) << "Mode of Transport" << setw(10) << "Count" << setw(25) << "Total Emission (kg CO2)" << "Avg per Resident\n";
        cout << "------------------------------------------------------------\n";

        int maxCount = 0;
        string preferred = "-";
        double totalEmission = 0.0;
        for (int m = 0; m < 6; m++) {
            const string& mode = modes[m];
            int count = countTransportByAgeGroup(list, ag, mode);
            double emission = getTotalEmissionByAgeGroupAndMode(list, ag, mode);
            double avg = count > 0 ? emission / count : 0.0;
            cout << left << setw(20) << mode
                 << setw(10) << count
                 << setw(25) << fixed << setprecision(2) << emission
                 << fixed << setprecision(2) << avg << "\n";
            if (count > maxCount) {
                maxCount = count;
                preferred = mode;
            }
            totalEmission += emission;
        }
        double averagePerResident = totalResidents > 0 ? totalEmission / totalResidents : 0.0;
        cout << "------------------------------------------------------------\n";
        cout << "Most Preferred Transport : " << preferred << " (" << maxCount << " residents)\n";
        cout << "Total Emission            : " << fixed << setprecision(2) << totalEmission << " kg CO2\n";
        cout << "Average Emission/Resident : " << fixed << setprecision(2) << averagePerResident << " kg CO2\n\n";

        if (totalEmission > maxEmission) {
            maxEmission = totalEmission;
            mostEmissionAgeGroup = ag;
        }
        if (maxCount > mostPreferredTransportCount) {
            mostPreferredTransportCount = maxCount;
            mostPreferredTransport = preferred;
            mostPreferredTransportGroup = ag;
        }
    }

    cout << "Summary:\n";
    cout << "Most Emission: " << mostEmissionAgeGroup << "\n";
    cout << "Most Preferred Transport: " << mostPreferredTransport << " (" << mostPreferredTransportGroup << ")\n";

    cout << "\nRecommendations for City Planners:\n";
    if (cityName.find("City A") != string::npos) {
        cout << "- Focus on reducing car emissions for age group 26-45.\n";
        cout << "- Promote public transport and walking for working adults.\n";
        cout << "- Develop cycling infrastructure for younger residents.\n";
        cout << "- Encourage carpooling for high-emission groups.\n";
    } else if (cityName.find("City B") != string::npos) {
        cout << "- Increase bus routes for age group 18-25.\n";
        cout << "- Provide incentives for using bicycles in urban areas.\n";
        cout << "- Enhance pedestrian pathways for age group 46-60.\n";
        cout << "- Promote electric vehicles for age group 26-45.\n";
    } else if (cityName.find("City C") != string::npos) {
        cout << "- Focus on reducing emissions from school buses.\n";
        cout << "- Encourage walking and cycling for all age groups.\n";
        cout << "- Develop carpooling programs for age group 18-25.\n";
        cout << "- Implement stricter emission regulations for cars.\n";
    } else if (cityName.find("All Cities") != string::npos) {
        cout << "- Implement city-specific emission reduction strategies.\n";
        cout << "- Share best practices among cities for sustainable transport.\n";
        cout << "- Invest in green public transport infrastructure.\n";
        cout << "- Educate residents on the benefits of sustainable transport.\n";
    }

    cout << "\n";
}
