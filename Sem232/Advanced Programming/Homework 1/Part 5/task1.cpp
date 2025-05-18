#include <iostream>
#include <string>

using namespace std;

const int MAX_STUDENTS = 100;

int main () 
{
    string names[MAX_STUDENTS];
    int scores[MAX_STUDENTS];

    string status[MAX_STUDENTS];
    int numStudents = 0;

    cout << "Task 1: Enter students' names and scores. Enter '-1' to stop." << endl;
    
    
    while (numStudents < MAX_STUDENTS) 
    {
        cout << "Enter student name: ";
        cin >> names[numStudents];

        if (names[numStudents] == "-1") break;

        cout << "Enter student score: ";
        cin >> scores[numStudents];

        status[numStudents] = (scores[numStudents] >= 50) ? 
            "Passed" : "Failed";

        numStudents++;
    }

    cout << "\nStudents' Information:" << endl;
    cout << "-----------------------------" << endl;
    cout << "Name\tScore\tStatus" << endl;
    cout << "-----------------------------" << endl;
    for (int i = 0; i < numStudents; i++)
        cout << names[i] << "\t" << scores[i] << "\t" << status[i] << endl;
        
    cout << endl;

    return 0;
}
