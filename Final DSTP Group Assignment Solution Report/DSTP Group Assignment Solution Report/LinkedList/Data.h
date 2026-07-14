#ifndef DATA_H
#define DATA_H

#include <string>
using namespace std;


struct Record {
    int residentID;
    int age;
    string transportMode;
    double dailyDistance;
    double carbonEmissionFactor;
    int averageDaysPerMonth;

    Record() : residentID(0), age(0), transportMode(""), 
               dailyDistance(0.0), carbonEmissionFactor(0.0), 
               averageDaysPerMonth(0) {}

    Record(int id, int a, string transport, double distance, 
           double emission, int days)
        : residentID(id), age(a), transportMode(transport),
          dailyDistance(distance), carbonEmissionFactor(emission),
          averageDaysPerMonth(days) {}

    double calculateMonthlyEmission() const {
        return dailyDistance * carbonEmissionFactor * averageDaysPerMonth;
    }


    string getAgeGroup() const {
        if (age >= 6 && age <= 17) return "6-17";
        else if (age >= 18 && age <= 25) return "18-25";
        else if (age >= 26 && age <= 45) return "26-45";
        else if (age >= 46 && age <= 60) return "46-60";
        else if (age >= 61 && age <= 100) return "61-100";
        return "Unknown";
    }
};

#endif 
