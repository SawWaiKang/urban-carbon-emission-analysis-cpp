#ifndef FILEIO_H
#define FILEIO_H

#include "Array.h"
#include <string>
using namespace std;


class FileIO {
public:
    static bool loadFromCSV(const string& filename, DynamicArray& arr);

    static string getFilePath(int cityChoice);

private:
    static Record parseCSVLine(const string& line);

    static int parseInteger(const string& str);

    static double parseDouble(const string& str);
};

#endif 
