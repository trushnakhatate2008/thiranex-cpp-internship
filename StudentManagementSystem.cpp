#include <iostream>
#include <fstream>
#include <string>
using namespace std;
struct Student {
    int rollNo;
    string name;
    int age;
    string course;
};
void addStudent() {
    Student s;
    ofstream file("students.txt", ios::app);
    cout << "\nEnter Roll Number: ";
    cin >> s.rollNo;
    cin.ignore();
    cout << "Enter Name: ";
    getline(cin, s.name);
    cout << "Enter Age: ";
    cin >> s.age;
    cin.ignore();
    cout << "Enter Course: ";
    getline(cin, s.course);
    file << s.rollNo << "|" << s.name << "|" 
         << s.age << "|" << s.course << endl;
    file.close();
    cout << "\nStudent added successfully!\n";
}
void displayStudents() {
    Student s;
    string line;
    ifstream file("students.txt");
    if (!file) {
        cout << "\nNo student records found.\n";
        return;
    }
    while (getline(file, line)) {
        size_t pos1 = line.find('|');
        size_t pos2 = line.find('|', pos1 + 1);
        size_t pos3 = line.find('|', pos2 + 1);
        if (pos1 == string::npos || pos2 == string::npos || pos3 == string::npos)
            continue;
        s.rollNo = stoi(line.substr(0, pos1));
        s.name = line.substr(pos1 + 1, pos2 - pos1 - 1);
        s.age = stoi(line.substr(pos2 + 1, pos3 - pos2 - 1));
        s.course = line.substr(pos3 + 1);
        cout << "\nRoll Number : " << s.rollNo;
        cout << "\nName        : " << s.name;
        cout << "\nAge         : " << s.age;
        cout << "\nCourse      : " << s.course;
    }
    file.close();
    cout << endl;
}
void updateStudent() {
    int rollNo;
    cout << "\nEnter Roll Number to update: ";
    cin >> rollNo;
    ifstream file("students.txt");
    ofstream temp("temp.txt");
    Student s;
    string line;
    bool found = false;
    while (getline(file, line)) {
        size_t pos1 = line.find('|');
        size_t pos2 = line.find('|', pos1 + 1);
        size_t pos3 = line.find('|', pos2 + 1);
        if (pos1 == string::npos || pos2 == string::npos || pos3 == string::npos)
            continue;
        s.rollNo = stoi(line.substr(0, pos1));
        s.name = line.substr(pos1 + 1, pos2 - pos1 - 1);
        s.age = stoi(line.substr(pos2 + 1, pos3 - pos2 - 1));
        s.course = line.substr(pos3 + 1);
        if (s.rollNo == rollNo) {
            cin.ignore();
            cout << "Enter New Name: ";
            getline(cin, s.name);
            cout << "Enter New Age: ";
            cin >> s.age;
            cin.ignore();
            cout << "Enter New Course: ";
            getline(cin, s.course);
            found = true;
        }
        temp << s.rollNo << "|" << s.name << "|"
             << s.age << "|" << s.course << endl;
    file.close();
    temp.close();
    remove("students.txt");
    rename("temp.txt", "students.txt");
    if (found)
        cout << "\nStudent updated successfully!\n";
    else
        cout << "\nStudent not found.\n";
}
void deleteStudent() {
    int rollNo;
    cout << "\nEnter Roll Number to delete: ";
    cin >> rollNo;
    ifstream file("students.txt");
    ofstream temp("temp.txt");
    Student s;
    string line;
    bool found = false;
    while (getline(file, line)) {
        size_t pos1 = line.find('|');
        size_t pos2 = line.find('|', pos1 + 1);
        size_t pos3 = line.find('|', pos2 + 1);
        if (pos1 == string::npos || pos2 == string::npos || pos3 == string::npos)
            continue;
        s.rollNo = stoi(line.substr(0, pos1));
        s.name = line.substr(pos1 + 1, pos2 - pos1 - 1);
        s.age = stoi(line.substr(pos2 + 1, pos3 - pos2 - 1));
        s.course = line.substr(pos3 + 1);
        if (s.rollNo == rollNo) {
            found = true;
            continue;
        }
        temp << s.rollNo << "|" << s.name << "|"
             << s.age << "|" << s.course << endl;
    }
    file.close();
    temp.close();
    remove("students.txt");
    rename("temp.txt", "students.txt");
    if (found)
        cout << "\nStudent deleted successfully!\n";
    else
        cout << "\nStudent not found.\n";
}
int main() {
    int choice;
    do {
        cout << "\n\n========== STUDENT MANAGEMENT SYSTEM ==========";
        cout << "\n1. Add Student";
        cout << "\n2. Display Students";
        cout << "\n3. Update Student";
        cout << "\n4. Delete Student";
        cout << "\n5. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                displayStudents();
                break;
            case 3:
                updateStudent();
                break;
            case 4:
                deleteStudent();
                break;
            case 5:
                cout << "\nExiting program...\n";
                break;
            default:
                cout << "\nInvalid choice. Please try again.\n";
        }
    } while (choice != 5);
    return 0;
}
