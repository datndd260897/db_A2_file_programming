// Include necessary standard library headers
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;  // Include the standard namespace

class Employee {
public:
    int id, manager_id;  // Employee ID and their manager's ID
    char name[201];      // Fixed length array to store employee name, last 1 character added for null ('\0') character 
    char bio[501];       // Fixed length array to store employee biography

    // Default constructor
    Employee() {}

    // Constructor with parameters to initialize an Employee object
    // Will contain a single row of the Employee.csv file 
    Employee(int id, const string& name, const string& bio, int manager_id)
        : id(id), manager_id(manager_id) {
        strncpy(this->name, name.c_str(), 200);  // Copy the name, ensure it fits in the array
        this->name[200] = '\0';  // Null terminate the string
        strncpy(this->bio, bio.c_str(), 500);  // Copy the biography, ensure it fits in the array
        this->bio[500] = '\0';  // Null terminate the string
    }

    // Function to write the Employee object to a binary output stream, i.e., EmployeeRelation.dat file
    void write_into_data_file(ostream& out) const {
        out.write(reinterpret_cast<const char*>(&id), sizeof(id));  // Write the integer ID
        out.write(name, sizeof(name));  // Write the fixed length name
        out.write(reinterpret_cast<const char*>(&manager_id), sizeof(manager_id));  // Write the integer manager_id
        out.write(bio, sizeof(bio));  // Write the fixed length bio
        /***TO_DO***/ // do the same thing for bio and manager-id

    }

    // Read data from a binary input stream, i.e., EmployeeRelation.dat file to populate an Employee object
    void read_from_data_file(istream& in) {
        in.read(reinterpret_cast<char*>(&id), sizeof(id));  // Read the integer ID
        in.read(name, sizeof(name));  // Read the fixed length name
        in.read(reinterpret_cast<char*>(&manager_id), sizeof(manager_id));  // Read the integer Manager_id
        in.read(bio, sizeof(bio));  // Read the fixed length bio
        /***TO_DO***/ // do the same thing for bio and manager-id

    }

    // Print the Employee object to standard output
    void print() const {
        cout << "ID: " << id << ", Name: " << name << ", Bio: " << bio << ", Manager ID: " << manager_id << endl;
    }
};

class StorageManager {
private:
    string filename;  // Name of the file (EmployeeRelation.dat) where we will store the Employee records 
    fstream data_file; // fstream to handle both input and output binary file operations

public:
    // Constructor that opens a data file for binary input/output; truncates any existing data file
    StorageManager(const string& filename) : filename(filename) {
        data_file.open(filename, ios::binary | ios::out | ios::in | ios::trunc);
        if (!data_file.is_open()) {  // Check if the data_file was successfully opened
            cerr << "Failed to open data_file: " << filename << endl;
            exit(EXIT_FAILURE);  // Exit if the data_file cannot be opened
        }
    }

    // Destructor closes the data file if it is still open
    ~StorageManager() {
        if (data_file.is_open()) {
            data_file.close();
        }
    }

    // Reads data from a CSV file and writes it to a binary data file as Employee objects
    void createFromFile(const string& csvFilename) {
        ifstream csvFile(csvFilename);  // Open the Employee.csv file for reading
        cout << "called createFromFile with filename " + csvFilename<<endl;
        if (!csvFile.is_open()) {
            cerr << "Failed to open CSV file: " << csvFilename << endl;
            return;
        }

        string line, name, bio;
        int id, manager_id;

        // Read each line from the CSV file, parse it, and create Employee objects
        while (getline(csvFile, line, ',')) { // Parse id, name, bio and manager-id, to create the Employee object below
            id = atoi(line.c_str());                     // Converts the id Value to integer
            getline(csvFile,name, ',');       // Gets name
            getline(csvFile,bio, ',');        // Gets the bio
            getline(csvFile,line);                 //Get the next value save it line
            manager_id= atoi(line.c_str());             // Converts the manager id to integer
            Employee emp(id, name, bio, manager_id);  //create Employee objects

            emp.write_into_data_file(data_file); // Write the Employee object, i.e., the row you read to the .dat data_file
        }
        csvFile.close();  // Close the CSV file
    }

    // Find Employee by ID and print in console. Use emp.read_from_data_file to read the data file
    void findAndPrintEmployee(int searchId) {
        data_file.clear();
        data_file.seekg(0, ios::beg);
        Employee emp;
        bool found = false;
        while (data_file) {
            emp.read_from_data_file(data_file);

            if (data_file.eof()) break;  // Break the loop if the end of the file is reached

            if (emp.id == searchId) {
                // If the ID matches the search ID, print the employee details
                // Print not found message if no match
                emp.print();
                found = true;
                break;
            }
        }

        if (!found) {
            cout << "Employee with ID " << searchId << " not found." << endl;
        }
    }

};