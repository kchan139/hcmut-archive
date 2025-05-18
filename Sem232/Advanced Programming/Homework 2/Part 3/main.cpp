#include <iostream>
#include <string>
using namespace std;

class Student 
{
    public:
        string name;
        int score;

        Student (const string & name, int score) : name (name), score (score) {}
        ~Student () {}
};

Student ** students = new Student*[100];
int studentCount = 0;

void addStudent () 
{
    if (studentCount >= 100) 
    {
        cout << "\nUnable to add student. Student list is full.\n";
        return;
    }

    string name;
    int score;
    cout << "\nEnter the name of the student: ";
    getline (cin, name);

    cout << "Enter the score of the student: ";
    cin >> score;
    cin.ignore ();
    students[studentCount] = new Student (name, score);
    studentCount++;

    cout << "\nStudent added successfully.\n";
}

void displayStudents () 
{
    cout << "\nList of students and scores:\n";
    for (int i = 0; i < studentCount; i++)
        cout << i + 1 << ". " << students[i]->name << " - " << students[i]->score << endl;
}

void displayBestStudents() 
{
    int highestScore = 0;
    for (int i = 0; i < studentCount; i++)
        if (students[i]->score > highestScore)
            highestScore = students[i]->score;

    cout << "\nBest student(s) with score of " << highestScore << ":\n";

    for (int i = 0; i < studentCount; i++)
        if (students[i]->score == highestScore)
            cout << students[i]->name << endl;
}

void removeStudent() 
{
    string name;
    cout << "\nEnter the name of the student to remove: ";
    getline(cin, name);

    for (int i = 0; i < studentCount; i++) 
    {
        if (students[i]->name == name)
        {
            delete students[i];
            for (int j = i; j < studentCount - 1; j++)
                students[j] = students[j + 1];
                
            studentCount--;
            cout << "\nStudent: "  << name << " removed successfully.\n";
            return;
        }
    }
    cout << "\nStudent not found.\n";
}

int main () 
{
    int choice;
    while (true) 
    {
        cout << "\n-----------------------------\n";
        cout << "Student Management Program\n";
        cout << "-----------------------------\n";
        cout << "1. Add student\n";
        cout << "2. Display students\n";
        cout << "3. Display best students\n";
        cout << "4. Remove student\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore ();

        switch (choice) 
        {
            case 1:
                addStudent();
                break;

            case 2:
                displayStudents();
                break;

            case 3:
                displayBestStudents();
                break;

            case 4:
                removeStudent();
                break;

            case 5:
                for (int i = 0; i < studentCount; i++)
                    delete students[i];
            
                delete [] students;
                return 0;
                
            default:
                cout << "Invalid choice." << endl;
        }
    }
    return 0;
}