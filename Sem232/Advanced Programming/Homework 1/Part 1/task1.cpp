// SIMPLE PROGRAM TO CALCULATE & DISPLAY 
// THE AVERAGE OF 3 INTEGERS

#include <iostream>
using namespace std;

int main ()
{
    cout << "Enter 3 integers: ";

    int a, b, c;
    cin >> a >> b >> c;

    cout << "Average: " << (a + b + c) / 3.0;

    return 0;
}