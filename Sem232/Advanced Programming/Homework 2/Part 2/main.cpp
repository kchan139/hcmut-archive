#include <iostream>
#include <string>
using namespace std;

void addStudent (string *& names, int *& scores, int & numStudents) 
{
    string name;
    int score;

    cout << "Enter the name of the new student: ";
    cin >> name;
    cout << "Enter the score of the student: ";
    cin >> score;

    string * newNames = new string[numStudents + 1];
    int * newScores = new int[numStudents + 1];

    for (int i = 0; i < numStudents; ++i) 
    {
        newNames[i] = names[i];
        newScores[i] = scores[i];
    }

    newNames[numStudents] = name;
    newScores[numStudents] = score;
    numStudents++;

    delete [] names;
    delete [] scores;
    names = newNames;
    scores = newScores;

    cout << "Student '" << name << "' added successfully." << endl;
}

void displayStudents (string * names, int * scores, int numStudents) 
{
    cout << "List of Students and Their Scores:" << endl;
    for (int i = 0; i < numStudents; ++i)
        cout << "Name: " << names[i] << ", Score: " << scores[i] << endl;
}

void displayBestStudent (string * names, int * scores, int numStudents) 
{
    int maxScore = -1;

    for (int i = 0; i < numStudents; ++i)
        if (scores[i] > maxScore)
            maxScore = scores[i];

    cout << "Best Student(s) and Their Score(s):" << endl;

    for (int i = 0; i < numStudents; ++i)
        if (scores[i] == maxScore)
            cout << "Name: " << names[i] << ", Score: " << scores[i] << endl;
}

int main() 
{
    string * names = nullptr;
    int * scores = nullptr;
    int numStudents = 0;
    int choice;

    while (true) 
    {
        cout << "\nStudent Management System" << endl;
        cout << "1. Add Student" << endl;
        cout << "2. Display Students" << endl;
        cout << "3. Display Best Student" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) 
        {
            case 1:
                addStudent (names, scores, numStudents);
                break;

            case 2:
                if (numStudents == 0)
                    cout << "No students added yet." << endl;
                else
                    displayStudents (names, scores, numStudents);
                break;

            case 3:
                if (numStudents == 0)
                    cout << "No students added yet." << endl;
                else
                    displayBestStudent (names, scores, numStudents);
                break;

            case 4:
                cout << "Exiting program." << endl;
                delete [] names;
                delete [] scores;
                return 0;

            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}
