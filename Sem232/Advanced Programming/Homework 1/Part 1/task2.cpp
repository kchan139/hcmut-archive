// SIMPLE CALCULATOR TO CALCULATE & DISPLAY THE
// SUMMATION, SUBTRACTION, DIVISION, MODULUS AND
// MULTIPLICATION OF 2 NUMBERS

#include <iostream>
using namespace std;

int main ()
{
    cout << "Enter two integers: ";

    int a, b;
    cin >> a >> b;

    cout << "Summation: "      << a + b << endl;
    cout << "Subtraction: "    << a - b << endl;
    cout << "Multiplication: " << a * b << endl;
    cout << "Division: "; (b) ? 
        cout << float(a) / b << endl : cout << "Undefined!" << endl;
    cout << "Modulus: "        << a % b << endl;

    return 0;
}