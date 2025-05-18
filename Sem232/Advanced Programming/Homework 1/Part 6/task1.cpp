#include <iostream>
#include <iomanip>
using namespace std;

float sumTriple (float num1, float num2, float num3) 
{
    return num1 + num2 + num3;
}

float mulTriple (float num1, float num2, float num3) 
{
    return num1 * num2 * num3;
}

float aveTriple(float num1, float num2, float num3) 
{
    return (num1 + num2 + num3) / 3.0;
}

int main () 
{
    float num1, num2, num3;
    cout << "Task 1: Calculate sum, multiplication, and average of three numbers." << endl;

    while (true) 
    {
        cout << "Enter three numbers (or -1 to quit): ";
        cin >> num1;

        if (num1 == -1)
            break;

        cin >> num2 >> num3;

        cout << "Sum: " << sumTriple(num1, num2, num3) << endl;
        cout << "Multiplication: " << mulTriple(num1, num2, num3) << endl;
        cout << fixed << setprecision(2);
        cout << "Average: " << aveTriple(num1, num2, num3) << endl;
    }

    return 0;
}
