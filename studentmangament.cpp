#include <iostream>
#include <fstream>
using namespace std;

class Student {
public:
    int id;
    char name[50];
    float marks;

    void input() {
        cout << "Enter ID: ";
        cin >> id;
        cout << "Enter Name: ";
        cin.ignore();
        cin.getline(name, 50);
        cout << "Enter Marks: ";
        cin >> marks;
    }

    void display() {
        cout << "ID: " << id << " | Name: " << name << " | Marks: " << marks << endl;
    }
};

// Add Student
void addStudent() {
    ofstream file("students.dat", ios::binary | ios::app);
    Student s;
    s.input();
    file.write((char*)&s, sizeof(s));
    file.close();
    cout << "Student added successfully!\n";
}

// View Students
void viewStudents() {
    ifstream file("students.dat", ios::binary);
    Student s;

    cout << "\n--- Student Records ---\n";
    while (file.read((char*)&s, sizeof(s))) {
        s.display();
    }
    file.close();
}

// Search Student
void searchStudent() {
    ifstream file("students.dat", ios::binary);
    Student s;
    int id;
    bool found = false;

    cout << "Enter ID to search: ";
    cin >> id;

    while (file.read((char*)&s, sizeof(s))) {
        if (s.id == id) {
            cout << "Record Found:\n";
            s.display();
            found = true;
            break;
        }
    }

    if (!found)
        cout << "Student not found!\n";

    file.close();
}

// Update Student
void updateStudent() {
    fstream file("students.dat", ios::binary | ios::in | ios::out);
    Student s;
    int id;
    bool found = false;

    cout << "Enter ID to update: ";
    cin >> id;

    while (file.read((char*)&s, sizeof(s))) {
        if (s.id == id) {
            cout << "Enter new details:\n";
            s.input();

            file.seekp(-sizeof(s), ios::cur);
            file.write((char*)&s, sizeof(s));

            cout << "Record updated successfully!\n";
            found = true;
            break;
        }
    }

    if (!found)
        cout << "Student not found!\n";

    file.close();
}

// Delete Student
void deleteStudent() {
    ifstream file("students.dat", ios::binary);
    ofstream temp("temp.dat", ios::binary);
    Student s;
    int id;
    bool found = false;

    cout << "Enter ID to delete: ";
    cin >> id;

    while (file.read((char*)&s, sizeof(s))) {
        if (s.id != id) {
            temp.write((char*)&s, sizeof(s));
        } else {
            found = true;
        }
    }

    file.close();
    temp.close();

    remove("students.dat");
    rename("temp.dat", "students.dat");

    if (found)
        cout << "Record deleted successfully!\n";
    else
        cout << "Student not found!\n";
}

// Main Menu
int main() {
    int choice;

    while (true) {
        cout << "\n===== Student Management System =====\n";
        cout << "1. Add Student\n";
        cout << "2. View Students\n";
        cout << "3. Search Student\n";
        cout << "4. Update Student\n";
        cout << "5. Delete Student\n";
        cout << "6. Exit\n";

        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addStudent(); break;
            case 2: viewStudents(); break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
            case 6: return 0;
            default: cout << "Invalid choice!\n";
        }
    }

    return 0;
}