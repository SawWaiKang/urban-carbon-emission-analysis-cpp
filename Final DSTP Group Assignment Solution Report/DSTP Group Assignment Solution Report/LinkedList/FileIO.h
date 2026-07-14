#ifndef FILEIO_H
#define FILEIO_H

#include "LinkedList.h"
#include <string>
using namespace std;


class FileIO {
public:
    static bool loadFromCSV(const string& filename, LinkedList& list);

    static string getFilePath(int cityChoice);

private:
    static Record parseCSVLine(const string& line);

    static int parseInteger(const string& str);

    static double parseDouble(const string& str);
};

#endif 
