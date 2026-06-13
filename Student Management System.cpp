#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>

using namespace std;

// Class to represent a Student
class Student {
private:
    int rollNumber;
    char name[50];
    char course[50];
    float gpa;

public:
    // Function to take input from user
    void getData() {
        cout << "\nEnter Roll Number: ";
        cin >> rollNumber;
        cin.ignore(); // Clear input buffer
        cout << "Enter Name: ";
        cin.getline(name, 50);
        cout << "Enter Course: ";
        cin.getline(course, 50);
        cout << "Enter GPA: ";
        cin >> gpa;
    }

    // Function to display student details in a row
    void showData() const {
        cout << left << setw(12) << rollNumber 
             << setw(20) << name 
             << setw(20) << course 
             << setw(8) << fixed << setprecision(2) << gpa << endl;
    }

    // Getter for Roll Number (used for searching and modifying)
    int getRollNumber() const {
        return rollNumber;
    }
    
    // Function to modify student details
    void modifyData() {
        cout << "\n--- Updating Record for Roll Number " << rollNumber << " ---\n";
        cin.ignore();
        cout << "Enter New Name: ";
        cin.getline(name, 50);
        cout << "Enter New Course: ";
        cin.getline(course, 50);
        cout << "Enter New GPA: ";
        cin >> gpa;
    }
};

// Function Declarations for File Operations
void addStudentRecord();
void displayAllRecords();
void searchStudentRecord();
void updateStudentRecord();
void deleteStudentRecord();
void displayHeader();

int main() {
    int choice;

    do {
        cout << "\n=========================================";
        cout << "\n       STUDENT MANAGEMENT SYSTEM         ";
        cout << "\n=========================================";
        cout << "\n1. Add Student Record";
        cout << "\n2. Display All Student Records";
        cout << "\n3. Search Student Record";
        cout << "\n4. Update Student Record";
        cout << "\n5. Delete Student Record";
        cout << "\n6. Exit";
        cout << "\n=========================================";
        cout << "\nEnter your choice (1-6): ";
        cin >> choice;

        switch (choice) {
            case 1:
                addStudentRecord();
                break;
            case 2:
                displayAllRecords();
                break;
            case 3:
                searchStudentRecord();
                break;
            case 4:
                updateStudentRecord();
                break;
            case 5:
                deleteStudentRecord();
                break;
            case 6:
                cout << "\nExiting program. Goodbye!\n";
                break;
            default:
                cout << "\nInvalid choice! Please try again.\n";
        }
    } while (choice != 6);

    return 0;
}

// Helper function to print table header
void displayHeader() {
    cout << "\n------------------------------------------------------------\n";
    cout << left << setw(12) << "Roll No" 
         << setw(20) << "Name" 
         << setw(20) << "Course" 
         << setw(8) << "GPA" << endl;
    cout << "------------------------------------------------------------\n";
}

// 1. Function to add a record to the binary file
void addStudentRecord() {
    Student stud;
    ofstream outFile("students.dat", ios::binary | ios::app);

    if (!outFile) {
        cout << "\nError opening file!" << endl;
        return;
    }

    stud.getData();
    // Write the entire object block to file
    outFile.write(reinterpret_cast<char*>(&stud), sizeof(Student));
    
    outFile.close();
    cout << "\nRecord added successfully!\n";
}

// 2. Function to read and display all records
void displayAllRecords() {
    Student stud;
    ifstream inFile("students.dat", ios::binary);

    if (!inFile) {
        cout << "\nNo records found (File does not exist yet).\n";
        return;
    }

    displayHeader();
    while (inFile.read(reinterpret_cast<char*>(&stud), sizeof(Student))) {
        stud.showData();
    }
    cout << "------------------------------------------------------------\n";
    inFile.close();
}

// 3. Function to search for a specific record using Roll Number
void searchStudentRecord() {
    Student stud;
    ifstream inFile("students.dat", ios::binary);
    int targetRoll;
    bool found = false;

    if (!inFile) {
        cout << "\nNo records found.\n";
        return;
    }

    cout << "\nEnter Roll Number to search: ";
    cin >> targetRoll;

    while (inFile.read(reinterpret_cast<char*>(&stud), sizeof(Student))) {
        if (stud.getRollNumber() == targetRoll) {
            displayHeader();
            stud.showData();
            cout << "------------------------------------------------------------\n";
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "\nRecord with Roll Number " << targetRoll << " not found.\n";
    }
    inFile.close();
}

// 4. Function to modify an existing record
void updateStudentRecord() {
    Student stud;
    fstream file("students.dat", ios::binary | ios::in | ios::out);
    int targetRoll;
    bool found = false;

    if (!file) {
        cout << "\nNo records found.\n";
        return;
    }

    cout << "\nEnter Roll Number to update: ";
    cin >> targetRoll;

    while (file.read(reinterpret_cast<char*>(&stud), sizeof(Student))) {
        if (stud.getRollNumber() == targetRoll) {
            stud.modifyData();
            
            // Move write pointer back to the beginning of this specific record
            int pos = static_cast<int>(file.tellg()) - sizeof(Student);
            file.seekp(pos);
            
            file.write(reinterpret_cast<char*>(&stud), sizeof(Student));
            cout << "\nRecord updated successfully!\n";
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "\nRecord with Roll Number " << targetRoll << " not found.\n";
    }
    file.close();
}

// 5. Function to delete a record
void deleteStudentRecord() {
    Student stud;
    ifstream inFile("students.dat", ios::binary);
    ofstream outFile("temp.dat", ios::binary); // Temporary file to hold non-deleted data
    int targetRoll;
    bool found = false;

    if (!inFile) {
        cout << "\nNo records found.\n";
        return;
    }

    cout << "\nEnter Roll Number to delete: ";
    cin >> targetRoll;

    while (inFile.read(reinterpret_cast<char*>(&stud), sizeof(Student))) {
        if (stud.getRollNumber() == targetRoll) {
            found = true; // Skip writing this record to the temp file
        } else {
            outFile.write(reinterpret_cast<char*>(&stud), sizeof(Student));
        }
    }

    inFile.close();
    outFile.close();

    // Replace the old file with the new file
    remove("students.dat");
    rename("temp.dat", "students.dat");

    if (found) {
        cout << "\nRecord deleted successfully!\n";
    } else {
        cout << "\nRecord with Roll Number " << targetRoll << " not found.\n";
    }
}
