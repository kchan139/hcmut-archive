#include <iostream>
using namespace std;

int main () 
{
    const int numStudents = 10;
    int scores[numStudents];
    int totalScore = 0;

    for (int i = 0; i < numStudents; ++i) 
    {
        cout << "Enter score for student " << i + 1 << ": ";
        cin >> scores[i];
        totalScore += scores[i];
    }

    double averageScore = static_cast<double>(totalScore) / numStudents;
    cout << "Average score: " << averageScore << endl;

    return 0;
}
