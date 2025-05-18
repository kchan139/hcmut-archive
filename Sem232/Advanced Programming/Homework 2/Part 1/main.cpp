#include <iostream>
#include <string>
using namespace std;

const int MAX_STUDENTS = 100;

string students[MAX_STUDENTS];
int numStudents = 0;

void addStudent () 
{
    string name;
    cout << "Enter the name of the new student: ";
    cin >> name;

    if (numStudents >= MAX_STUDENTS) 
    {
        cout << "Cannot add more students. The list is full." << endl;
        return;
    }

    students[numStudents++] = name;
    cout << "Student '" << name << "' added successfully." << endl;
}

void displayStudents () 
{
    cout << "List of Students:" << endl;
    for (int i = 0; i < numStudents; ++i)
        cout << i + 1 << ". " << students[i] << endl;
}

void removeStudent () 
{
    string name;
    cout << "Enter the name of the student to remove: ";
    cin >> name;

    int index = -1;
    for (int i = 0; i < numStudents; ++i) 
    {
        if (students[i] == name) 
        {
            index = i;
            break;
        }
    }

    if (index != -1) 
    {
        for (int i = index; i < numStudents - 1; ++i)
            students[i] = students[i + 1];
            
        numStudents--;
        cout << "Student '" << name << "' removed successfully." << endl;
    }
    else cout << "Student '" << name << "' not found in the list." << endl;
}

int main () 
{
    int choice;

    while (true) 
    {
        cout << "\nStudent Management System" << endl;
        cout << "1. Add Student"              << endl;
        cout << "2. Display Students"         << endl;
        cout << "3. Remove Student"           << endl;
        cout << "4. Exit"                     << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) 
        {
            case 1:
                addStudent ();
                break;
                
            case 2:
                displayStudents ();
                break;

            case 3:
                removeStudent ();
                break;

            case 4:
                cout << "Exiting program." << endl;
                return 0;

            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}
