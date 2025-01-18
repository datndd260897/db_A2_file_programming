/*
Skeleton code for storage management
*/

#include <string>
#include <ios>
#include <fstream>
#include <vector>
#include <string>
#include <string.h>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <cmath>
#include "classes.h"
#include "constants.h"
using namespace std;

int main(int argc, char* argv[]) {
    // Initialize the Storage Manager Class with the Binary .dat file name we want to create
    StorageManager manager(DATA_FILE);

    // Assuming the Employee.CSV file is in the same directory, 
    // we want to read from the Employee.csv and write into the new data_file
    manager.createFromFile(CSV_FILE);

    // Searching for Employee IDs Using [manager.findAndPrintEmployee(id)]
    /***TO_DO***/
    int searchId;

    while (true) {
        cout << "Enter Employee ID to search (Input 0 to exit): ";
        cin >> searchId;
        if (!searchId) break;
        manager.findAndPrintEmployee(searchId);
    }


    return 0;
}