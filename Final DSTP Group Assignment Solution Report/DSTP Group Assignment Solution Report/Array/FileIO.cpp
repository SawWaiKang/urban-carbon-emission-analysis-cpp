#include "FileIO.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <cctype>
using namespace std;


string FileIO::getFilePath(int cityChoice) {
    switch (cityChoice) {
        case 1:
            return "../dataset1-cityA.csv";
        case 2:
            return "../dataset2-cityB.csv";
        case 3:
            return "../dataset3-cityC.csv";
        default:
            return "";
    }
}


int FileIO::parseInteger(const string& str) {
    try {
        return stoi(str);
    } catch (...) {
        return 0;
    }
}

double FileIO::parseDouble(const string& str) {
    try {
        return stod(str);
    } catch (...) {
        return 0.0;
    }
}

Record FileIO::parseCSVLine(const string& line) {
    stringstream ss(line);
    string field;
    string fields[6];  
    int fieldCount = 0;

    while (getline(ss, field, ',') && fieldCount < 6) {
        size_t start = field.find_first_not_of(" \t\r\n");
        size_t end = field.find_last_not_of(" \t\r\n");
        if (start != string::npos) {
            field = field.substr(start, (end - start + 1));
        }
        fields[fieldCount++] = field;
    }

    if (fieldCount >= 6) {
        Record rec;
        
        string idStr = fields[0];
        int numericId = 0;
        for (char c : idStr) {
            if (isdigit(c)) {
                numericId = numericId * 10 + (c - '0');
            }
        }
        rec.residentID = numericId;
        
        rec.age = parseInteger(fields[1]);
        rec.transportMode = fields[2];
        rec.dailyDistance = parseDouble(fields[3]);
        rec.carbonEmissionFactor = parseDouble(fields[4]);
        rec.averageDaysPerMonth = parseInteger(fields[5]);
        return rec;
    }

    return Record();  
}


bool FileIO::loadFromCSV(const string& filename, DynamicArray& arr) {
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Error: Cannot open file " << filename << "\n";
        return false;
    }

    string line;
    int recordCount = 0;

    getline(file, line);

    while (getline(file, line)) {
        if (line.empty()) continue;

        Record rec = parseCSVLine(line);

        if (rec.residentID > 0) {
            arr.append(rec);
            recordCount++;
        }
    }

    file.close();

    cout << "Successfully loaded " << recordCount << " records from " << filename << "\n";
    return recordCount > 0;
}
